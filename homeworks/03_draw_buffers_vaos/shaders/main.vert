#version 450

// Task 3.1: Draw a Square
// Task 3.2: Draw a Square using strip
const vec2 triangle[6] = {
	vec2(0.5, -0.5),
	vec2(-0.5, 0.5),
	vec2(-0.5, -0.5),
	vec2(0.5, -0.5),
	vec2(-0.5, 0.5),
	vec2(0.5, 0.5)
};

void main()
{
    gl_Position = vec4(triangle[gl_VertexID], 0.0, 1.0);
}
