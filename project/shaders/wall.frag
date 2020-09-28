#version 450

layout(binding = 0, std140) uniform Camera {
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

struct Light {
	vec4 position;
	vec4 direction; // .w is radius
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
};

layout(binding = 1, std430) buffer Lights {
	Light lights[];
};

struct Object {
	mat4 model_matrix;
	vec4 ambient_color;
	vec4 diffuse_color;
	vec4 specular_color;
	vec4 dist;
};

layout(binding = 2, std430) buffer Objects {
	Object objects[];
};

uniform float alpha = 1.0;
uniform int size = 10;
uniform float time = 1.0;

layout(location = 0) in vec3 fs_position;
layout(location = 1) in vec3 fs_normal;
layout(location = 2) in flat int fs_instance_id;

layout(location = 0) out vec4 final_color;

void main()
{
	Object object = objects[fs_instance_id];

    float r = sin(object.dist.x / size + time) / 2 + 0.5;
    float g = sin(object.dist.x / size + time + 3.14) / 2 + 0.5;
    float b = sin(object.dist.x / size + time + 3.14 / 2) / 2 + 0.5;

	final_color = vec4(vec3(r, g, b), alpha);
}
