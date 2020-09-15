#version 450

const vec2 triangle[3] = {
	vec2(-1.0, 0.0),
	vec2(-1.0, 1.0),
	vec2(1.0, 1.0)
};

void main()
{
    gl_Position = vec4(triangle[gl_VertexID], 0.0, 1.0);
}