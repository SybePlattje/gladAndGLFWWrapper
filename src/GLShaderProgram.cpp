#include "GLShaderProgram.hpp"
#include <iostream>

GLShaderProgram::GLShaderProgram(): m_program(0) {}

GLShaderProgram::~GLShaderProgram()
{
    glDeleteProgram(m_program);
}

GLShaderProgram::GLShaderProgram(const GLShaderProgram& other): m_program(other.m_program), m_uniformCache(other.m_uniformCache) {}

GLShaderProgram& GLShaderProgram::operator=(const GLShaderProgram& other)
{
    if (this != &other)
    {
        m_program = other.m_program;
        m_uniformCache = other.m_uniformCache;
    }
    return *this;
}

GLShaderProgram::GLShaderProgram(GLShaderProgram&& other): m_program(other.m_program), m_uniformCache(other.m_uniformCache)
{
    other.m_program = 0;
    other.m_uniformCache.clear();
}

GLShaderProgram& GLShaderProgram::operator=(GLShaderProgram&& other)
{
    if (this != &other)
    {
        m_program = other.m_program;
        m_uniformCache = other.m_uniformCache;

        other.m_program = 0;
        other.m_uniformCache.clear();
    }
    return *this;
}

bool GLShaderProgram::setup()
{
    m_program = glCreateProgram();
    if (m_program == 0)
    {
        std::cerr << "failed to create shader program" << std::endl;
        return false;
    }
    return true;
}

void GLShaderProgram::bind()
{
    glUseProgram(m_program);
}

void GLShaderProgram::unbind()
{
    glUseProgram(0);
}

GLuint GLShaderProgram::getProgram() const
{
    return m_program;
}

void GLShaderProgram::attachShader(std::vector<GLShaderFile>& shaders)
{
    if (shaders.empty())
        return;
    
    for (GLShaderFile& shader : shaders)
        glAttachShader(m_program, shader.getId());
}

bool GLShaderProgram::linkProgram()
{
    glLinkProgram(m_program);
    if (!checkCompileErrors())
    {
        std::cerr << "failed to link shader to program" << std::endl;
        return false;
    }

    return true;
}

GLint GLShaderProgram::getUniformLocation(const std::string& name)
{
    if (m_uniformCache.find(name) != m_uniformCache.end())
        return m_uniformCache[name];
    
    GLint location = glGetUniformLocation(m_program, name.data());
    if (location == -1)
    {
        std::cerr << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
        return -1;
    }

    m_uniformCache.emplace(name, location);
    return location;
}

bool GLShaderProgram::checkCompileErrors()
{
    GLint success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    char buffer[512];
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, nullptr, buffer);
        std::cerr << "❌ PROGRAM_LINKING_ERROR\n" << buffer << std::endl;
        return false;
    }
    return true;
}