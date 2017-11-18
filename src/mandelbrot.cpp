#include "mandelbrot.h"

#include <iostream>

namespace
{
    static float map(double value, double original_min, double original_max, double new_min, double new_max)
    {
        return (value - original_min) / (original_max - original_min) * (new_max - new_min) + new_min;
    }
}

Mandelbrot::Mandelbrot(const char* fragment_shader_file, int width, int height, int max_iterations) : 
    m_mandelbrot_shader(FileUtilities::LoadFile("../shaders/pass_through.vert").c_str(), FileUtilities::LoadFile(fragment_shader_file).c_str()), 
    m_texture_shader(FileUtilities::LoadFile("../shaders/texture.vert").c_str(), FileUtilities::LoadFile("../shaders/texture.frag").c_str()), 
    m_screen_quad({{-1.0f, 1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f}, {1.0f, -1.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f, 1.0f}}, {0, 1, 2, 0, 2, 3}), 
    m_mandelbrot_texture(width, height),
    m_width(width),
    m_height(height),
    m_current_state({-0.5, 0.0, 1.0}),
    m_original_iterations(max_iterations),
    m_max_iterations(max_iterations)
{
    m_texture_shader.Bind();
    m_texture_shader.SetUniform1i("framebuffer_texture", 0);
    m_texture_shader.Unbind();

    m_mandelbrot_shader.Bind();
    m_mandelbrot_shader.SetUniform2d("window_size", width, height);
    m_mandelbrot_shader.SetUniform1i("max_iterations", max_iterations);
    m_mandelbrot_shader.Unbind();

    SelectScreenLocation(m_width / 2, m_height / 2, false);
}

void Mandelbrot::SelectScreenLocation(double x, double y, bool increment_zoom)
{
    if (increment_zoom)
        m_history.push(m_current_state);

    m_current_state.center_x = ((3 * (x / m_width) - 1.5) / m_current_state.zoom) + m_current_state.center_x; 
    m_current_state.center_y = ((2 * (map(y, 0, m_height, m_height, 0) / m_height) - 1) / m_current_state.zoom) + m_current_state.center_y; 

    if (increment_zoom)
    {
        m_current_state.zoom *= 2.0;
    }

    UpdateShader();

    RenderToTexture();
}

void Mandelbrot::Undo()
{
    if (m_history.empty())
        return;

    m_current_state = m_history.top();
    m_history.pop();

    UpdateShader();

    RenderToTexture();
}

void Mandelbrot::Reset()
{
    m_history = {};
    m_current_state = {-0.5, 0.0, 1.0};
    m_max_iterations = m_original_iterations;

    UpdateShader();
    RenderToTexture();
}

void Mandelbrot::IncrementIterations(int amount)
{
    int sign = (amount < 0) ? -1 : 1;

    if (m_max_iterations < m_iteration_cutoff)
        m_max_iterations += 1 * sign;
    else if (m_max_iterations + amount > m_iteration_cutoff)
        m_max_iterations += amount;
    else
        m_max_iterations = m_iteration_cutoff - 1;

    if (m_max_iterations <= 1)
        m_max_iterations = 2;

    UpdateShader();
    RenderToTexture();
}

void Mandelbrot::UpdateShader()
{
    m_mandelbrot_shader.Bind();
    m_mandelbrot_shader.SetUniform2d("center", m_current_state.center_x, m_current_state.center_y);
    m_mandelbrot_shader.SetUniform1d("zoom", m_current_state.zoom);
    m_mandelbrot_shader.SetUniform1i("max_iterations", m_max_iterations);
    m_mandelbrot_shader.Unbind();
}

void Mandelbrot::RenderToScreen() const
{
    m_texture_shader.Bind();
    m_mandelbrot_texture.BindTexture();

    m_screen_quad.Render();

    m_mandelbrot_texture.UnbindTexture();
    m_texture_shader.Unbind();
}

void Mandelbrot::RenderToTexture() const
{
    m_mandelbrot_shader.Bind();
    m_mandelbrot_texture.Bind();

    m_screen_quad.Render();
    
    m_mandelbrot_texture.Unbind(); 
    m_mandelbrot_shader.Unbind();
}
