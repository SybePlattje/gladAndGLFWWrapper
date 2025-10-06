#ifndef GLCONTEXT_HPP
# define GLCONTEXT_HPP

# include <GLFW/glfw3.h>

class GLContext
{
    public:
        GLContext(int major = 4, int minor = 1);
        ~GLContext();

        static bool initGlad();
        static void pollEvents();
        static double getTime();
        static GLFWerrorfun setErrorCallback(GLFWerrorfun callback);
        static void terminate();
    private:
        bool initGlfw();
        void sanitizeVersions(int& major, int& minor);
};

#endif