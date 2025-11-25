#include "GLShaderProgram.hpp"
#include <iostream>

/**
 * @brief construct a new GLShaderProgram object
 * 
 */
GLShaderProgram::GLShaderProgram(): m_program(0) {}


/**
 * @brief festroy the GLShaderProgram object
 * 
 */
GLShaderProgram::~GLShaderProgram()
{
    glDeleteProgram(m_program);
}

/**
 * @brief copies data from one shaderProgram to another
 * 
 * @param other the object to copy from
 */
GLShaderProgram::GLShaderProgram(const GLShaderProgram& other): m_program(other.m_program), m_uniformCache(other.m_uniformCache) {}

/**
 * @brief copy assign opperator that copies data from one shaderProgram to another
 * 
 * @param other the object to copy form
 * @return a shaderProgram with the data from other 
 */
GLShaderProgram& GLShaderProgram::operator=(const GLShaderProgram& other)
{
    if (this != &other)
    {
        m_program = other.m_program;
        m_uniformCache = other.m_uniformCache;
    }
    return *this;
}

/**
 * @brief moves data from one object to itself and takes ownership of the data
 * 
 * @param other the object with data to take ownership over
 */
GLShaderProgram::GLShaderProgram(GLShaderProgram&& other): m_program(other.m_program), m_uniformCache(other.m_uniformCache)
{
    other.m_program = 0;
    other.m_uniformCache.clear();
}

/**
 * @brief moves data from one object to itself and takes ownership of the data
 * 
 * @param other the object with data to take ownership over
 * @return a program with the data from other
 */
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

/**
 * @brief creates the shader program
 * 
 * @return true if program creation is successfull
 * @return false if program creation failed
 */
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

/**
 * @brief sets the shader program as the one in use
 * 
 */
void GLShaderProgram::bind()
{
    glUseProgram(m_program);
}

/**
 * @brief releases the shader program as the one in use
 * 
 */
void GLShaderProgram::unbind()
{
    glUseProgram(0);
}

/**
 * @brief get the program id
 * 
 * @return the program id
 */
GLuint GLShaderProgram::getProgram() const
{
    return m_program;
}

/**
 * @brief attaches the shader files to the shader program
 * 
 * @param shader a vector with shaders that will be added to the shader program
 */
void GLShaderProgram::attachShader(std::vector<GLShaderFile>& shaders)
{
    if (shaders.empty())
        return;
    
    for (GLShaderFile& shader : shaders)
        glAttachShader(m_program, shader.getId());
}

/**
 * @brief links the attached shader files into a complete shader program
 * 
 * @return true if linking is successfull
 * @return false on link check errors
 */
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

/**
 * @brief get the uniform location identified by the name given
 * 
 * @param name the name of the uniform as stated in the shader source
 * @return the location id or -1 if not found
 */
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

/**
 * @brief checks if during shader program linker there were error
 * 
 * @return true if no errors are found
 * @return false if linking errors are found
 */
bool GLShaderProgram::checkCompileErrors()
{
    GLint success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    char buffer[512];
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, nullptr, buffer);
        std::cerr << "PROGRAM_LINKING_ERROR\n" << buffer << std::endl;
        return false;
    }
    return true;
}