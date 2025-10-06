#ifndef GLDEBUG_HPP
# define GLDEBUG_HPP

# include "externalLib/glad/include/glad/glad.h"

class GLDebug
{
    public:
        static void enable();
        static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};

#endif