#version 450

layout(location = 0) in vec4 vs_color;

layout(location = 0) out vec4 final_color;

void main()
{
    final_color = vs_color;
}
