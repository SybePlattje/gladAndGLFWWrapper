#include "externalLib/glad/include/glad/glad.h"
#include "GLContext.hpp"
#include <stdexcept>
#include <iostream>

GLContext::GLContext(int major, int minor)
{
    if (initGlfw())
        throw std::runtime_error("Failed to initialze glfw");

    sanitizeVersions(major, minor);

    glfwWindowHint(GLFW_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_VERSION_MINOR, minor);
}

GLContext::~GLContext()
{
    terminate();
}

void GLContext::terminate()
{
    glfwTerminate();
}

bool GLContext::initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[GLAD] Failed to initialize OpenGL context!" << std::endl;
        return false;
    }
    #ifdef DEBUG
        std::cout << "[GLAD] OpenGL loaded: " 
            << glGetString(GL_VENDOR) << " | "
            << glGetString(GL_RENDERER) << " | "
            << glGetString(GL_VERSION) << std::endl;
    #endif
    return true;
}

bool GLContext::initGlfw()
{
    if (glfwInit())
        return true;

    const char* errorDescription = nullptr;
    glfwGetError(&errorDescription);
    if (errorDescription)
        std::cerr << "[GLFW] Initialization failed: " << errorDescription << std::endl;
    else
        std::cerr << "[GLFW] Initialization failed: Unknown error" << std::endl;

    return false;
}

void GLContext::pollEvents()
{
    glfwPollEvents();
}

double GLContext::getTime()
{
    return glfwGetTime();
}

GLFWerrorfun GLContext::setErrorCallback(GLFWerrorfun callback)
{
    return glfwSetErrorCallback(callback);
}

void GLContext::sanitizeVersions(int& major, int& minor)
{
    int glfwMajor, glfwMinor, glfwRev;
    glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);

    if (3 > major || (3 == major && 3 > minor))
    {
        major = 3;
        minor = 3;
    }

    if (4 == major && 6 < minor)
        minor = 6;
    if (4 == major && 3 < minor)
        minor = 3;
    
    if (glfwMajor < major)
    {
        major = glfwMajor;
        minor = glfwMinor;
    }
    else if ( glfwMajor == major && glfwMinor < minor)
        minor = glfwMinor;
    
    if (0 >= major)
    {
        major = 3;
        minor = 3;
    }
}