#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "program.hpp"

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

  GLuint vao;

  GLuint program1 = create_program("build/02_shaders_final/shaders/main.vert", "build/02_shaders_final/shaders/main.frag");
  GLuint program2 = create_program("build/02_shaders_final/shaders/main2.vert", "build/02_shaders_final/shaders/main2.frag");
};
