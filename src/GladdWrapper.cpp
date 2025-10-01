#include "GladWrapper.hpp"

bool GladWrapper::sGWGLWFInnit()
{
    if (!glfwInit())
        return false;
    return true;
}

bool GladWrapper::sGWCreateWindow(GLFWwindow* window, int width, int height, const std::string& name)
{
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!window)
        return false;
    return true;
}

bool GladWrapper::sGWInnit()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;
    return true;
}