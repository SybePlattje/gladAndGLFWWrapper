#ifndef GLWINDOW_HPP
# define GLWINDOW_HPP

# include <GLFW/glfw3.h>
# include <string>

class GLWindow
{
    public:
        GLWindow(int width, int height, const std::string& title);
        GLWindow(const std::string& title);
        ~GLWindow();

        bool shoulClose() const;
        void swapBuffers() const;
        void setTitle(const std::string& title);
        void setSize(int width, int height);
        void getSize(int& width, int& height) const;

        bool isKeyPressed(int key) const;
        GLFWkeyfun setKeyCallback(GLFWkeyfun callback);
        GLFWcursorposfun setCursorCallback(GLFWcursorposfun callback);

        void setClearColor(float red, float green, float blue, float alpha);
        void clear(bool color = true, bool depth = true) const;

        void makeWindowCurrent();
        void swapIntervals(int interval);
        void getFrameBuffer(int* fbWidth, int* fbHeight);
        
        template<typename T>
        void setWindowPointer(T* data);

        template<typename T>
        T* getWindowPointer();
    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        int m_fbWidth;
        int m_fbHeight;
        std::string m_title;


};

#endif