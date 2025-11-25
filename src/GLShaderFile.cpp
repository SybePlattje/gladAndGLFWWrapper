#include "GLShaderFile.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

/**
 * @brief Construct a new GLShaderFile object
 * 
 */
GLShaderFile::GLShaderFile(): m_id(0), m_type(0), m_source() {}

/**
 * @brief Construct a new GLShaderFile object
 * 
 * @param type what kind of shader it is
 */
GLShaderFile::GLShaderFile(GLenum type): m_id(0), m_type(type), m_source() {}

/**
 * @brief Destroy the GLShaderFile object
 * 
 */
GLShaderFile::~GLShaderFile()
{
    glDeleteShader(m_id);
}

/**
 * @brief moves data from one GLShaderFile object to another and takes onership of the data
 * 
 * @param other the object of which we will take ownership
 */
GLShaderFile::GLShaderFile(GLShaderFile&& other):
m_id(other.m_id),
m_type(other.m_type),
m_source(other.m_source)
{
    other.m_id = 0;
    other.m_type = 0;
    other.m_source.clear();
}

/**
 * @brief moves data from one GLShaderFile object to another and takes onership of the data
 * 
 * @param other the object of which we will take ownership
 * @return a GLShaderFile object with the data from the object given and its data
 */
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

/**
 * @brief initializes the values for the shader file
 * 
 * @param filePath the path to the file
 * @param type what type of shader it will be
 * @return true if setup succeeds
 * @return false if reading the file or compiling shader fails
 */
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

/**
 * @brief gives the id of the shaderFile
 * 
 * @return the id of the shader
 */
GLuint GLShaderFile::getId() const
{
    return m_id;
}

/**
 * @brief gives the shader type
 * 
 * @return the shader type
 */
GLenum GLShaderFile::getType() const
{
    return m_type;
}

/**
 * @brief gives the data from the file itself
 * 
 * @return the source code from the shader
 */
std::string GLShaderFile::getSource() const
{
    return m_source;
}

/**
 * @brief creates the shader basesd on the shader type, sets its source and compilse it
 * 
 * @return true if shader compiling is successfull
 * @return false if there are compile errors
 */
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

/**
 * @brief checks it there are errors when the shader was compiled
 * 
 * @return true if no errors are found
 * @return false if the shader has comile errors
 */
bool GLShaderFile::checkShaderErrors()
{
    GLint success = 0;
    char buffer[512];

    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, nullptr, buffer);
        std::cerr << "SHADER_COMPILATION_ERROR of type: " << shaderTypeToString() << "\n" << buffer << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief reads the source data from the file and stores it for later use
 * 
 * @param path the path to the location of the shader file
 * @return true if all data from the shader file could be read
 * @return false  if the file could not be found, or on read errors
 */
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

/**
 * @brief converts the GLenum shader type to string
 * 
 * @return the string veriant of the shader type
 */
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