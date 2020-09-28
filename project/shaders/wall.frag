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

	vec3 color_sum = vec3(0.0);

    float r = sin(object.dist.x / size + time) / 2 + 0.5;
    float g = sin(object.dist.x / size + time + 3.14) / 2 + 0.5;
    float b = sin(object.dist.x / size + time + 3.14 / 2) / 2 + 0.5;

	vec3 object_ambient = object.ambient_color.rgb * vec3(r, g, b);
	vec3 object_diffuse = object.diffuse_color.rgb * vec3(r, g, b);
	vec3 object_specular = object.specular_color.rgb * vec3(r, g, b);

	for (int i = 0; i < lights.length(); i++) {
		Light light = lights[i];
		vec3 light_vector = light.position.xyz - fs_position * light.position.w;
		vec3 L = normalize(light_vector);
		vec3 N = normalize(fs_normal);
		vec3 E = normalize(camera.position - fs_position);
		vec3 H = normalize(L + E);

		float NdotL = max(dot(N, L), 0.0);
		float NdotH = max(dot(N, H), 0.0001);

		vec3 ambient = object_ambient * light.ambient_color.rgb;
		vec3 diffuse = object_diffuse * light.diffuse_color.rgb;
		vec3 specular = object_specular * light.specular_color.rgb;

		vec3 color = ambient.rgb
			+ NdotL * diffuse.rgb 
			+ pow(NdotH, object.specular_color.w) * specular.rgb;
		color /= length(light_vector);

		color_sum += color;
	}

    color_sum = color_sum / (color_sum + 1.0);   // tone mapping
    color_sum = pow(color_sum, vec3(1.0 / 2.2)); // gamma correction
	final_color = vec4(color_sum, alpha);
}
