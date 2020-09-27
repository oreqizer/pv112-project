#version 450

layout(binding = 0, std140) uniform Camera {
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

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

uniform int size = 10;
uniform float time = 1.0;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_normal;
layout(location = 2) out flat int fs_instance_id;

void main()
{
	Object object = objects[gl_InstanceID];

	vec3 center = vec3(size / 2);
	vec3 offset = normalize(position - center) * (sin(object.dist.x / size + time * 3) * 0.2 + 1);
	
	fs_position = vec3(object.model_matrix * vec4(position + offset, 1.0));
	fs_normal = transpose(inverse(mat3(object.model_matrix))) * normal;
	fs_instance_id = gl_InstanceID;

    gl_Position = camera.projection * camera.view * vec4(fs_position, 1.0);
}
