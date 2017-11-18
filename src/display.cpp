#include "display.h"

#include <iostream>
#include <stdexcept>

namespace
{ 
    static void error_callback(int error, const char* description)
    {
        std::cerr << "GLFW Error: " << description << '\n';
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            Display* display = (Display*) glfwGetWindowUserPointer(window);

            display->KeyCallback(key);
        }

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            Display* display = (Display*) glfwGetWindowUserPointer(window);

            double mouse_x, mouse_y;

            glfwGetCursorPos(window, &mouse_x, &mouse_y);

            display->ClickCallback(mouse_x, mouse_y, button);
        }
    }
}

Display::Display(int width, int height, const char* title)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";

        throw std::runtime_error("GLFW INIT ERROR");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    m_window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!m_window)
    {
        std::cerr << "Failed to create a GLFW window\n";
        glfwTerminate();

        throw std::runtime_error("GLFW WINDOW CREATION ERROR");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);
    
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
}

Display::~Display()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Display::IsOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

void Display::SwapBuffers() const
{
    glfwSwapBuffers(m_window);
}

void Display::PollEvents() const
{
    glfwPollEvents();
}
        
void Display::SetClickCallback(std::function<void(int, int, int)> callback)
{
    m_click_callback = callback;
}

void Display::SetKeyCallback(std::function<void(int)> callback)
{
    m_key_callback = callback;
}

void Display::ClickCallback(int x, int y, int button_type)
{
    if (m_click_callback != nullptr)
    {
        m_click_callback(x, y, button_type);
    }
}

void Display::KeyCallback(int key)
{
    if (m_key_callback != nullptr)
    {
        m_key_callback(key);
    }
}

int Display::GetWidth() const
{
    return m_width;
}

int Display::GetHeight() const
{
    return m_height;
}
