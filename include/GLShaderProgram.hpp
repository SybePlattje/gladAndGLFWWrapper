#ifndef GLSHADERPROGRAM_HPP
# define GLSHADERPROGRAM_HPP

# include <string>
# include <glad/glad.h>
# include <type_traits>
# include <unordered_map>
# include <vector>
# include "GLStructs.hpp"
# include "GLShaderFile.hpp"

class GLShaderProgram
{
    public:
        GLShaderProgram();
        ~GLShaderProgram();

        GLShaderProgram(const GLShaderProgram& other);
        GLShaderProgram& operator=(const GLShaderProgram& other);

        GLShaderProgram(GLShaderProgram&& other);
        GLShaderProgram& operator=(GLShaderProgram&& other);

        bool setup();
        void bind();
        void unbind();
        GLuint getProgram() const;
        void attachShader(std::vector<GLShaderFile>& shader);
        bool linkProgram();

        /**
         * @param name the name of the uniform
         * @param value the  values the uniform will get
         * @brief while being checked on type we try to set the value of the uniform
         * @warning static_assert will check if passed values are support
         */
        template<typename T>
        bool setUniform(const std::string& name, const T& value)
        {
            GLint location = getUniformLocation(name);
            if (location == -1)
                return false;

            if constexpr (std::is_same_v<T, int>)
                glUniform1i(location, value);
            else if constexpr (std::is_save_v<T, unsigned int>)
                glUniform1ui(location, value);
            else if constexpr (std::is_same_v<T , float>)
                glUniform1f(location, value);
            else if constexpr (is_vec2<T>::value)
                glUniform2f(location, value.x, value.y);
            else if constexpr (is_vec3<T>::value)
                glUniform3f(location, value.x, value.y, value.z);
            else if constexpr (is_vec4<T>::value)
                glUniform4f(location, value.x, value.y, value.z, value.w);
            else if constexpr (is_mat4<T>::value)
                glUniformMatrix4fv(location, 1, GL_TRUE, &value.m[0][0]);
            else if constexpr (is_quat<T>::value)
                glUniform4f(location, value.x, value.y, value.z, value.w);
            else
                static_assert(always_false<T>::value, "Unsupported uniform type");
            return true;
        }
    private:
        GLuint m_program;
        std::unordered_map<std::string, GLint> m_uniformCache;

        GLint getUniformLocation(const std::string& name);
        bool checkCompileErrors();
};

#endif