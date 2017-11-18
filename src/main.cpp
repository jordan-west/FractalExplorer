#include "display.h"
#include "mandelbrot.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <functional>

Mandelbrot* mandelbrot;

void key_callback(int key)
{
    if (key == GLFW_KEY_R)
        mandelbrot->Reset();
    else if (key == GLFW_KEY_UP)
        mandelbrot->IncrementIterations(50);
    else if (key == GLFW_KEY_DOWN)
        mandelbrot->IncrementIterations(-50);
}

void click_callback(int x, int y, int button_type)
{
    if (button_type == GLFW_MOUSE_BUTTON_LEFT)
        mandelbrot->SelectScreenLocation(x, y, true);
    else if (button_type == GLFW_MOUSE_BUTTON_RIGHT)
        mandelbrot->Undo();
}

int main(int argc, char** argv)
{
    Display display(960, 640, "Fractal Explorer");

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glViewport(0, 0, display.GetWidth(), display.GetHeight());
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    mandelbrot = new Mandelbrot("../shaders/mandelbrot.frag", display.GetWidth(), display.GetHeight(), 500);

    display.SetClickCallback(&click_callback);
    display.SetKeyCallback(&key_callback);

    while (display.IsOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        mandelbrot->RenderToScreen();

        display.SwapBuffers();
        display.PollEvents();
    }

    delete mandelbrot;

    return 0;
}
