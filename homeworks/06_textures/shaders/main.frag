#version 450

layout(location = 3) uniform vec3 eye_position;

layout(location = 4) uniform vec4 light_position;
layout(location = 5) uniform vec3 light_ambient_color;
layout(location = 6) uniform vec3 light_diffuse_color;
layout(location = 7) uniform vec3 light_specular_color;

layout(location = 8) uniform vec3 material_ambient_color;
layout(location = 9) uniform vec3 material_diffuse_color;
layout(location = 10) uniform vec3 material_specular_color;
layout(location = 11) uniform float material_shininess;

// Task 6.2: Add a sampler binding for texture
layout(binding = 12) uniform sampler2D diffuse_texture;

layout(location = 0) in vec3 fs_position;
layout(location = 1) in vec3 fs_normal;
layout(location = 2) in vec2 fs_texture_coordinate;

layout(location = 0) out vec4 final_color;

void main()
{
    // Direction from the current fragment to the light source.
    // Instead of using 'if (light_position.w == 0.0)', we use this. For
    // directional lights, w is 0.0, so the fragment position is not subtracted
	vec3 light_vector = light_position.xyz - fs_position * light_position.w;
	vec3 L = normalize(light_vector);
	vec3 N = normalize(fs_normal); // Normal vector of the current fragment	
	vec3 E = normalize(eye_position - fs_position); // Direction from the current fragment to the camera	
	vec3 H = normalize(L + E); // Half vector between (E)ye and L

	float NdotL = max(dot(N, L), 0.0);
	float NdotH = max(dot(N, H), 0.0);

	float distance2 = light_position.w == 1.0 ? pow(length(light_vector), 2) : 1.0;

	vec3 material_ambient = material_ambient_color * light_ambient_color;

	// Task 6.2: Fetch color from diffuse texture using fs_texture_coordinate
	//           The function is: texture(sampler, texture_coordinate) and returns vec4
	// Task 6.2: Multiply diffuse color by diffuse texture
    vec4 texture_color = texture(diffuse_texture, fs_texture_coordinate);  

	vec3 material_diffuse = material_diffuse_color * light_diffuse_color * texture_color.rgb;

	vec3 material_specular = material_specular_color * light_specular_color;

	vec3 material_color = material_ambient
		+ NdotL * material_diffuse 
		+ pow(NdotH, material_shininess) * material_specular;

	final_color = vec4(material_color / distance2, 1.0);
}
