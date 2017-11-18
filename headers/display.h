#ifndef FRACTAL_EXPLORER_DISPLAY_H_
#define FRACTAL_EXPLORER_DISPLAY_H_

#include <GLFW/glfw3.h>

#include <functional>

class Display
{
    public:
        Display(int width, int height, const char* title);
        ~Display();

        bool IsOpen() const;
        void SwapBuffers() const;
        void PollEvents() const;

        void SetClickCallback(std::function<void(int, int, int)> callback);
        void SetKeyCallback(std::function<void(int)> callback);

        void ClickCallback(int x, int y, int button_type);
        void KeyCallback(int key);

        int GetWidth() const;
        int GetHeight() const;
    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;

        std::function<void(int, int, int)> m_click_callback;
        std::function<void(int)> m_key_callback;
};

#endif
