#version 450

layout(binding = 0, std140) uniform Camera {
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

struct Light {
	vec4 position;
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
};

layout(binding = 2, std430) buffer Objects {
	Object objects[];
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_normal;

void main()
{
	Object object = objects[gl_InstanceID];
	
	fs_position = vec3(object.model_matrix * vec4(position, 1.0));
	fs_normal = transpose(inverse(mat3(object.model_matrix))) * normal;

    gl_Position = camera.projection * camera.view * vec4(fs_position, 1.0);
}
