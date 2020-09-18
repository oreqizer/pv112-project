#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

// Task 3.8: Output color to fragment shader.
layout(location = 0) out vec3 vs_color;

void main()
{
    gl_Position = vec4(position, 1.0);
    vs_color = color;
}
