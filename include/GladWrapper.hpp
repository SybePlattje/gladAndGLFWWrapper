#ifndef GLADWRAPPER_HPP
# define GLADWRAPPER_HPP

#include "externalLib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

class GladWrapper
{
    public:
        static bool sGWGLWFInnit();
        static bool sGWCreateWindow(GLFWwindow* window, int width, int height, const std::string& name);
        static bool sGWCreateFullscreenWindow(GLFWwindow* window, const std::string& name);
        static void sGWCleanupGLFW();
        static void sGWCleanupWindow(GLFWwindow* window);
        static bool sGWInnit();
};

#endif