#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utilities.hpp"
#include "program.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "texture.hpp"

// Constants
const float clear_color[4] = {0.0, 0.0, 0.0, 1.0};
const float clear_depth[1] = {1.0};

class Application {
public:
  Application(size_t initial_width, size_t initial_height);
  ~Application();

  void render();

  /// Input callbacks
  /// https://www.glfw.org/docs/latest/input_guide.html
  ///
  void on_resize(GLFWwindow *window, int width, int height);
  void on_mouse_move(GLFWwindow *window, double x, double y);
  void on_mouse_pressed(GLFWwindow *window, int button, int action, int mods);
  void on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
  size_t width;
  size_t height;

  Camera camera;

  GLuint main_program = create_program("build/07_framebuffer/shaders/main.vert", "build/07_framebuffer/shaders/main.frag");
  GLuint postprocess_program = create_program("build/07_framebuffer/shaders/postprocess.vert", "build/07_framebuffer/shaders/postprocess.frag");

  Mesh cube = Mesh::cube();
  Mesh sphere = Mesh::sphere();
  Mesh teapot = Mesh::teapot();

  GLuint wood_texture = load_texture_2d("images/wood.jpg");
  GLuint rock_texture = load_texture_2d("images/rocks.jpg");

  float light = 0.0f;

  GLuint framebuffer = 0;
  GLuint framebuffer_color = 0;
  GLuint framebuffer_depth = 0;
};