#include "GLContext.hpp"
#include "GLWindow.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
    try 
    {
        GLContext context(4, 1);
        GLWindow window(800, 800, "test");

        if (!GLContext::sInitGlad())
        {
            std::cerr << "Glad init failed" << std::endl;
            return 1;
        }
        double start = GLContext::sGetTime();
        while (!window.shoulClose())
        {
            GLContext::sPollEvents();
            window.clear();
            window.setClearColor(0.25f, 0.9f, 0.1f, 0.f);
            double elapsed = GLContext::sGetTime() - start;
            if (5.0 < elapsed)
                window.setWindowClose();
            if (2.0 < elapsed && 3.0 > elapsed)
            {
                window.setSize(500, 500);
                window.setTitle("changed");
            }
            window.swapBuffers();
        }
        GLContext::sTerminate();
    }
    catch(std::runtime_error& e)
    {
        std::cerr << "[Runtime Error] " << e.what() << std::endl;
        return 1;
    }
    catch (std::exception& e)
    {
        std::cerr << "[Other error]" << e.what() << std::endl;
        return 1;
    }
}