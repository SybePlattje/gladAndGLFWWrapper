#include "GLShaderFile.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

GLShaderFile::GLShaderFile(): m_id(0), m_type(0), m_source() {}

GLShaderFile::GLShaderFile(GLenum type): m_id(0), m_type(type), m_source() {}

GLShaderFile::~GLShaderFile()
{
    glDeleteShader(m_id);
}

GLShaderFile::GLShaderFile(GLShaderFile&& other):
m_id(other.m_id),
m_type(other.m_type),
m_source(other.m_source)
{
    other.m_id = 0;
    other.m_type = 0;
    other.m_source.clear();
}

GLShaderFile& GLShaderFile::operator=(GLShaderFile&& other)
{
    glDeleteShader(m_id);
    if (this != &other)
    {
        m_id = other.m_id;
        m_type = other.m_type;
        m_source = other.m_source;

        other.m_id = 0;
        other.m_type = 0;
        other.m_source.clear();
    }
    return *this;
}

bool GLShaderFile::setup(const std::string& filePath, GLenum type)
{
    m_type = type;

    if (!readShaderFile(filePath))
        return false;

    if (!compileShader())
        return false;

    if (m_id == 0)
    {
        std::cerr << "failed to create shader" << std::endl;
        return false;
    }
    return true;
}

GLuint GLShaderFile::getId() const
{
    return m_id;
}

GLenum GLShaderFile::getType() const
{
    return m_type;
}

std::string GLShaderFile::getSource() const
{
    return m_source;
}

bool GLShaderFile::compileShader()
{
    const char* src = m_source.data();
    m_id = glCreateShader(m_type);
    
    glShaderSource(m_id, 1, &src, nullptr);
    glCompileShader(m_id);

    if (!checkShaderErrors())
        return false;
    return true;
}

bool GLShaderFile::checkShaderErrors()
{
    GLint success = 0;
    char buffer[512];

    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, nullptr, buffer);
        std::cerr << "❌ SHADER_COMPILATION_ERROR of type: " << shaderTypeToString() << "\n" << buffer << std::endl;
        return false;
    }
    return true;
}

bool GLShaderFile::readShaderFile(const std::string& path)
{
    std::ifstream fstream(path, std::ios::binary | std::ios::ate);
    if (!fstream)
    {
        std::cerr << "file not found: " << path << std::endl;
        return false;
    }
    
    std::streamsize size = fstream.tellg();
    fstream.seekg(0, std::ios::beg);

    std::vector<char> buffer(size + 1, {'\0'});
    if (!fstream.read(buffer.data(), size))
    {
        fstream.close();
        std::cerr << "reading file failed: " << path << std::endl;
        return false;
    }

    m_source = buffer.data();

    fstream.close();
    return true;
}

std::string GLShaderFile::shaderTypeToString()
{
     switch (m_type)
    {
        case GL_VERTEX_SHADER:
            return "VERTEX";
        case GL_FRAGMENT_SHADER:
            return "FRAGMENT";
        case GL_GEOMETRY_SHADER:
            return "GEOMETRY";
        case GL_COMPUTE_SHADER:
            return "COMPUTE";
        case GL_TESS_CONTROL_SHADER:
            return "TESS_CONTROL";
        case GL_TESS_EVALUATION_SHADER:
            return "TESS_EVALUATION";
        default:
            return "UNKNOWN";
    }
}