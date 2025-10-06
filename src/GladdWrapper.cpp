#include "GladWrapper.hpp"

/**
 * @return True if glfw is initialized, false if initializtion failed.
 * @brief Initializes the glfw library
 */
bool GladWrapper::sGWGLWFInnit()
{
    if (!glfwInit())
        return false;
    return true;
}

/**
 * @brief Terminates the glfw library and cleans all the remaining window and monitor data up.
 * @warning The contexts of any remaining windows must not be current on any other thread when this function is called.
 */
void GladWrapper::sGWCleanupGLFW()
{
    glfwTerminate();
}

/**
 * @param window The window pointer to be cleaned up
 * @brief Destroys the window and its current context
 */
void GladWrapper::sGWCleanupWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
}

/**
 * @param window An NULL GLFWwindow pointer to hold the window info
 * @param width The width of the window as int
 * @param height The hegiht of the window as int
 * @param name The name of the window
 * @return True if window is created, false if window creation fails
 * @brief Creates a window of the given width and height and name. On a failed cleanup of the libraries still needs to happen.
 */
bool GladWrapper::sGWCreateWindow(GLFWwindow* window, int width, int height, const std::string& name)
{
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!window)
        return false;
    return true;
}

/**
 * @param window An null pointer that will hold the window info
 * @param name The name of the window
 * @return True if the window is created as a fullscreen window, false if getting the primary monitor fails, or the monitor info fails, or window creation fails
 * @brief Creates a fullscreen window on the primary monitor, with the monitor color and refresh rate settings. The window will have the given name.
 */
bool GladWrapper::sGWCreateFullscreenWindow(GLFWwindow* window, const std::string& name)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor)
        return false;
    
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode)
    {
        return false;
    }

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(mode->width, mode->height, name.c_str(), monitor, nullptr);
    if (!window)
        return false;
    return true;
}

/**
 * @brief Initializes the glad library
 * @return True if glad is initialized, false if an error happens
 */
bool GladWrapper::sGWInnit()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;
    return true;
}