#version 330 core

layout (location = 0) in vec3 position;

out vec4 vert_position;

void main()
{
    vert_position = vec4(position, 1.0f);
    gl_Position = vec4(position, 1.0f);
}
