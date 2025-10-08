#ifndef GLMESH_HPP
# define GLMESH_HPP

# include <vector>
# include <glad/glad.h>

class GLMesh
{
    public:
        GLMesh();
        GLMesh(const GLMesh& ohter) = delete;
        GLMesh(GLMesh&& other);
        ~GLMesh();

        GLMesh& operator=(const GLMesh& other) = delete;
        GLMesh& operator=(GLMesh&& other);

        bool setup(const std::vector<float>& vertices,
            const std::vector<unsigned int>& indices = {},
            int stride = 3,
            const std::vector<int>& attributeSize = {3});
        void bind() const;
        void unbind() const;
        void draw(GLenum mode = GL_TRIANGLES) const;

        GLuint getVertextArrayObject() const;
        GLuint getVertextBufferObject() const;
        GLuint getElementBufferObject() const;
    private:
        GLuint m_vertexArrayObject;
        GLuint m_vertexBufferObject;
        GLuint m_elementBufferObject;
        GLsizei m_vertexCount;
        GLsizei m_indexCount;
        bool m_hasElementBufferObject;

        void cleanup();
};

#endif