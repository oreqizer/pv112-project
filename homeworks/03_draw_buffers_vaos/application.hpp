#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utilities.hpp"
#include "program.hpp"
#include "data.hpp"

// see main_vao.vert
const int LOC_POSITION = 0;
const int LOC_COLOR = 1;

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

  GLuint vao_empty;

  GLuint vboDiamondVertices;
  GLuint vboDiamondColors;
  GLuint vaoDiamond;

  GLuint vboSquare;
  GLuint vaoSquare;

  GLuint vboTriangle;
  GLuint vaoTriangle;

  GLuint vboDiamondIndicesIndexed;
  GLuint vboDiamondVerticesIndexed;
  GLuint vboDiamondColorsIndexed;
  GLuint vaoDiamondIndexed;

  GLuint program = create_program("build/03_draw_buffers_vaos/shaders/main.vert", "build/03_draw_buffers_vaos/shaders/main.frag");
  GLuint program_vao = create_program("build/03_draw_buffers_vaos/shaders/main_vao.vert", "build/03_draw_buffers_vaos/shaders/main_vao.frag");
};