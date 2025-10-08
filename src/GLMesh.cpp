#include "GLMesh.hpp"
#include <iostream>
#include <stdexcept>

GLMesh::GLMesh():
m_vertexArrayObject(0),
m_vertexBufferObject(0),
m_elementBufferObject(0),
m_vertexCount(0),
m_indexCount(0),
m_hasElementBufferObject(false)
{}

GLMesh::GLMesh(GLMesh&& other):
m_vertexArrayObject(other.m_vertexArrayObject),
m_vertexBufferObject(other.m_vertexBufferObject),
m_elementBufferObject(other.m_elementBufferObject),
m_hasElementBufferObject(other.m_hasElementBufferObject)
{
    other.m_vertexArrayObject = 0;
    other.m_vertexBufferObject = 0;
    other.m_elementBufferObject = 0;
    other.m_hasElementBufferObject = false;
}

GLMesh::~GLMesh()
{
    cleanup();
}

GLMesh& GLMesh::operator=(GLMesh&& other)
{
    if (this != &other)
    {
        cleanup();

        m_vertexArrayObject = other.m_vertexArrayObject;
        m_vertexBufferObject = other.m_vertexBufferObject;
        m_elementBufferObject = other.m_elementBufferObject;
        m_hasElementBufferObject = other.m_hasElementBufferObject;

        other.m_vertexArrayObject = 0;
        other.m_vertexBufferObject = 0;
        other.m_elementBufferObject = 0;
        other.m_hasElementBufferObject = false;
    }

    return *this;
}

bool GLMesh::setup(const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    int stride,
    const std::vector<int>& attributeSizes)
{
    if (vertices.empty())
    {
        std::cerr << "vertices vector is empty" << std::endl;
        return false;
    }

    cleanup();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    if (0 == m_vertexArrayObject || 0 == m_vertexBufferObject)
    {
        std::cerr << "Error: failed to create vertex array object or vertex buffer object" << std::endl;
        return false;
    }

    glBindVertexArray(m_vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    m_hasElementBufferObject = !indices.empty();
    if (m_hasElementBufferObject)
    {
        glGenBuffers(1, &m_elementBufferObject);
        if (0 == m_elementBufferObject)
        {
            std::cerr << "failed to generate element buffer object" << std::endl;
            return false;
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        m_indexCount = static_cast<GLsizei>(indices.size());
        m_hasElementBufferObject = true;
    }
    else
        m_indexCount = 0;

    int offset = 0;
    for (size_t i = 0; attributeSizes.size() >= i; ++i)
    {
        glEnableVertexAttribArray(static_cast<GLuint>(i));
        glVertexAttribPointer(static_cast<GLuint>(i),
        attributeSizes[i],
        GL_FLOAT,
        GL_FALSE,
        stride * sizeof(float),
    reinterpret_cast<void*>(offset * sizeof(float)));
    offset += attributeSizes[i];
    }
    
    glEnableVertexAttribArray(0);

    m_vertexCount = static_cast<GLsizei>(vertices.size());

    glBindVertexArray(0);

    return true;
}

void GLMesh::bind() const
{
    glBindVertexArray(m_vertexArrayObject);
}

void GLMesh::unbind() const
{
    glBindVertexArray(0);
}

void GLMesh::draw(GLenum mode) const
{
    bind();

    if (m_hasElementBufferObject)
        glDrawElements(mode, m_indexCount, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(mode, 0, m_vertexCount);

    unbind();
}

GLuint GLMesh::getVertextArrayObject() const
{
    return m_vertexArrayObject;
}

GLuint GLMesh::getVertextBufferObject() const
{
    return m_vertexBufferObject;
}

GLuint GLMesh::getElementBufferObject() const
{
    return m_elementBufferObject;
}

void GLMesh::cleanup()
{
    if (m_elementBufferObject)
    {
        glDeleteBuffers(1, &m_elementBufferObject);
        m_elementBufferObject = 0;
    }
    if (m_vertexBufferObject)
    {
        glDeleteBuffers(1, &m_vertexBufferObject);
        m_vertexBufferObject = 0;
    }
    if (m_vertexArrayObject)
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
        m_vertexArrayObject = 0;
    }
    m_vertexCount = 0;
    m_indexCount = 0;
    m_hasElementBufferObject = false;
}