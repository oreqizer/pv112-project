#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utilities.hpp"
#include "program.hpp"
#include "data.hpp"

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

  GLuint program = create_program("build/04_pipeline/shaders/main.vert", "build/04_pipeline/shaders/main.frag");

  // Diamond
  GLuint diamond_vao;
  GLuint diamond_positions_vbo;
  GLuint diamond_colors_vbo;

  // Square
  GLuint square_vao;
  GLuint square_vbo;

  // Triangle
  GLuint triangle_vao;
  GLuint triangle_vbo;

  // Diamond Indexed
  GLuint diamond_indexed_vao;
  GLuint diamond_indices_vbo;
  GLuint diamond_positions_indexed_vbo;
  GLuint diamond_colors_indexed_vbo;
};