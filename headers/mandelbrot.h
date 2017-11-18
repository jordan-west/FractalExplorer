#ifndef FRACTAL_EXPLORER_MANDELBROT_H_
#define FRACTAL_EXPLORER_MANDELBROT_H_

#include "mesh.h"
#include "shader_program.h"
#include "file_utilities.h"
#include "render_texture.h"

#include <stack>

class Mandelbrot
{
    public:
        Mandelbrot(const char* fragment_shader_file, int width, int height, int max_iterations);

        void SelectScreenLocation(double x, double y, bool increment_zoom);
        void Undo();
        void Reset();
        void IncrementIterations(int amount);

        void UpdateShader();

        void RenderToScreen() const;
        void RenderToTexture() const;
    private:
        struct MandelbrotData
        {
            MandelbrotData(double center_x, double center_y, double zoom) : center_x(center_x), center_y(center_y), zoom(zoom) { }

            double center_x, center_y, zoom;
        };

        ShaderProgram m_mandelbrot_shader;
        ShaderProgram m_texture_shader;
        RenderTexture m_mandelbrot_texture;
        Mesh m_screen_quad;

        int m_width, m_height, m_max_iterations, m_original_iterations;
        MandelbrotData m_current_state;

        std::stack<MandelbrotData> m_history;

        // At this cutoff, the speed at which you can decrease iterations is reduced 
        const int m_iteration_cutoff = 40;
};
#endif
