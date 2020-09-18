#version 450

layout(location = 0) out vec4 final_color;

// Task 3.8: Take color from vertex shader as an input and use it to calcualte
//           the final color.
layout(location = 0) in vec3 fs_color;

void main()
{
    final_color = vec4(fs_color, 1.0);
}
