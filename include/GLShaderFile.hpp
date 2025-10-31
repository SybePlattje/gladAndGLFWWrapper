#ifndef GLSHADERFILE_HPP
# define GLSHADERFILE_HPP

# include <string>
# include <glad/glad.h>

class GLShaderFile
{
    public:
        GLShaderFile();
        GLShaderFile(GLenum type);
        ~GLShaderFile();

        GLShaderFile(const GLShaderFile& other) = delete;
        GLShaderFile& operator=(const GLShaderFile& other) = delete;

        GLShaderFile(GLShaderFile&& other);
        GLShaderFile& operator=(GLShaderFile&& other);

        bool setup(const std::string& filePath, GLenum type);
        GLuint getId() const;
        GLenum getType() const;
        std::string getSource() const;
    private:
        GLuint m_id;
        GLenum m_type;
        std::string m_source;
        
        bool compileShader();
        bool checkShaderErrors();
        bool readShaderFile(const std::string& filePath);
        std::string shaderTypeToString();
};

#endif