#version 450

layout(location = 0) out vec4 final_color;

void main()
{
    if(gl_FragCoord.y > 500)
    {
        final_color = vec4(0.0, 0.0, 1.0, 1.0);
    }
    else
    {
        final_color = vec4(1.0, 0.0, 0.0, 1.0);
    }
}
