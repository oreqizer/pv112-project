#version 450

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 model;
layout(location = 2) uniform mat4 view;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture_coordinate;

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_normal;
layout(location = 2) out vec2 fs_texture_coordinate;

void main()
{
	fs_position = position;
	fs_normal = transpose(inverse(mat3(model))) * normal;
	fs_texture_coordinate = texture_coordinate;

    gl_Position = projection * view * model * vec4(position, 1.0);
}
