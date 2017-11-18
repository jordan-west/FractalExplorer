#version 410 core

in vec4 vert_position;

// Writing to render target 0, our texture
layout (location = 0) out vec4 color;

uniform dvec2 window_size;
uniform double window_ratio;
uniform dvec2 center;
uniform double zoom;
uniform int max_iterations;

vec4 get_mandelbrot_color();

void main()
{
    color = get_mandelbrot_color();
}

vec4 get_mandelbrot_color()
{
    dvec2 z, c;
    
    c.x = ((3 * (gl_FragCoord.x / window_size.x) - 1.5) / zoom) + center.x;
    c.y = ((2 * (gl_FragCoord.y / window_size.y) - 1) / zoom) + center.y;

    z = c;
    
    float current_iteration = 0;

    for (current_iteration = 0; current_iteration < max_iterations; current_iteration++)
    {
        double real_temp = (z.x * z.x - z.y * z.y) + c.x;
        double imaginary_temp = (z.y * z.x + z.x * z.y) + c.y;

        z.x = real_temp;
        z.y = imaginary_temp;
    
        if ((real_temp * real_temp + imaginary_temp * imaginary_temp) > 2.0)
            break;
    } 
        
    float divisor = current_iteration / max_iterations;
    float color_interpolate = clamp(divisor, 0.0f, 0.9f);

    if (divisor >= 1.0f)
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    else if (divisor > 0.5f)
        return vec4(color_interpolate, 1.0f, color_interpolate, 1.0f);
    else
        return vec4(0.0f, color_interpolate, 0.0f, 1.0f);
}
