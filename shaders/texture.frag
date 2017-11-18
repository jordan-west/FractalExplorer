#version 330 core

in vec2 texture_coordinate;

out vec4 color;

uniform sampler2D framebuffer_texture;

void main()
{
    color = texture(framebuffer_texture, texture_coordinate);
}
