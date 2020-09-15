#version 450

// Gaussian kernel
const float gaussBlurKernel[3][3] = {
	{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0},
	{2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0},
	{1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0}
};

// Edge detection convolution kernel
const float edgeDetectionKernel[3][3] = {
	{-1.0, -1.0, -1.0},
	{-1.0,  8.0, -1.0},
	{-1.0, -1.0, -1.0}
};

layout(binding = 0) uniform sampler2D input_image;

layout(location = 0) out vec4 final_color;

void main() {
	vec3 color = texelFetch(input_image, ivec2(gl_FragCoord.xy), 0).rgb;

	// --------------------------------------------------------------------------
	// TODO Task 7.3: Apply post-process effects (grayscale, convolution kernels)
	// --------------------------------------------------------------------------
	// Use texelFetch(https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/texelFetch.xhtml)
	// to retrieve exact pixel and gl_FragCoord.xy to retrieve the coordinates of the fragment 
	// currently being processed.
	//
	// - make the color grayscale (https://en.wikipedia.org/wiki/Grayscale)
	// - apply a convolution kernel (https://en.wikipedia.org/wiki/Kernel_(image_processing))


	final_color = vec4(color, 1.0);	
}