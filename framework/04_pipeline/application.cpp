#include <iostream>

#include "application.hpp"

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Diamond
  glCreateBuffers(1, &diamond_positions_vbo);
  glNamedBufferStorage(diamond_positions_vbo, sizeof(diamond_positions), diamond_positions, NULL);
  glCreateBuffers(1, &diamond_colors_vbo);
  glNamedBufferStorage(diamond_colors_vbo, sizeof(diamond_colors), diamond_colors, NULL);

  glCreateVertexArrays(1, &diamond_vao);
  glVertexArrayVertexBuffer(diamond_vao, 0, diamond_positions_vbo, 0, 3 * sizeof(float));
  glVertexArrayVertexBuffer(diamond_vao, 1, diamond_colors_vbo, 0, 4 * sizeof(float));

  glEnableVertexArrayAttrib(diamond_vao, 0);
  glVertexArrayAttribFormat(diamond_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(diamond_vao, 0, 0);

  glEnableVertexArrayAttrib(diamond_vao, 1);
  glVertexArrayAttribFormat(diamond_vao, 1, 4, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(diamond_vao, 1, 1);

  // Square
  glCreateBuffers(1, &square_vbo);
  glNamedBufferStorage(square_vbo, sizeof(square_data), square_data, NULL);

  glCreateVertexArrays(1, &square_vao);
  glVertexArrayVertexBuffer(square_vao, 0, square_vbo, 0, 3 * sizeof(float));
  glVertexArrayVertexBuffer(square_vao, 1, square_vbo, 6 * 3 * sizeof(float), 4 * sizeof(float));

  glEnableVertexArrayAttrib(square_vao, 0);
  glVertexArrayAttribFormat(square_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(square_vao, 0, 0);

  glEnableVertexArrayAttrib(square_vao, 1);
  glVertexArrayAttribFormat(square_vao, 1, 4, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(square_vao, 1, 1);

  // Triangle
  glCreateBuffers(1, &triangle_vbo);
  glNamedBufferStorage(triangle_vbo, sizeof(triangle_vertices), triangle_vertices, NULL);

  glCreateVertexArrays(1, &triangle_vao);
  glVertexArrayVertexBuffer(triangle_vao, 0, triangle_vbo, 0, sizeof(Vertex));

  glEnableVertexArrayAttrib(triangle_vao, 0);
  glVertexArrayAttribFormat(triangle_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(triangle_vao, 0, 0);

  glEnableVertexArrayAttrib(triangle_vao, 1);
  glVertexArrayAttribFormat(triangle_vao, 1, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, color));
  glVertexArrayAttribBinding(triangle_vao, 1, 0);

  // Diamond
  glCreateBuffers(1, &diamond_indices_vbo);
  glCreateBuffers(1, &diamond_positions_indexed_vbo);
  glCreateBuffers(1, &diamond_colors_indexed_vbo);

  glNamedBufferStorage(diamond_indices_vbo, sizeof(diamond_indices), diamond_indices, NULL);
  glNamedBufferStorage(diamond_positions_indexed_vbo, sizeof(diamond_positions_indexed), diamond_positions_indexed, NULL);
  glNamedBufferStorage(diamond_colors_indexed_vbo, sizeof(diamond_colors_indexed), diamond_colors_indexed, NULL);

  glCreateVertexArrays(1, &diamond_indexed_vao);
  glVertexArrayVertexBuffer(diamond_indexed_vao, 0, diamond_positions_indexed_vbo, 0, 3 * sizeof(float));
  glVertexArrayVertexBuffer(diamond_indexed_vao, 1, diamond_colors_indexed_vbo, 0, 4 * sizeof(float));

  glVertexArrayElementBuffer(diamond_indexed_vao, diamond_indices_vbo);

  glEnableVertexArrayAttrib(diamond_indexed_vao, 0);
  glVertexArrayAttribFormat(diamond_indexed_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(diamond_indexed_vao, 0, 0);

  glEnableVertexArrayAttrib(diamond_indexed_vao, 1);
  glVertexArrayAttribFormat(diamond_indexed_vao, 1, 4, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(diamond_indexed_vao, 1, 1);

  // Task 4.2: Enable the depth test using glEnable function
  // glEnable(GL_DEPTH_TEST);

  // Task 4.3: Enable multisampling on opengl side using glEnable
  glEnable(GL_MULTISAMPLE);

  // Task 4.4: Enable blending and try out different configurations of blend equation
  //           Turn off depth before turning this on
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);

  // Task 4.5: Enable culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

Application::~Application() {
  glDeleteProgram(program);

  glDeleteVertexArrays(1, &diamond_vao);
  glDeleteBuffers(1, &diamond_positions_vbo);
  glDeleteBuffers(1, &diamond_colors_vbo);

  glDeleteVertexArrays(1, &square_vao);
  glDeleteBuffers(1, &square_vbo);

  glDeleteVertexArrays(1, &triangle_vao);
  glDeleteBuffers(1, &triangle_vbo);

  glDeleteVertexArrays(1, &diamond_indexed_vao);
  glDeleteBuffers(1, &diamond_indices_vbo);
  glDeleteBuffers(1, &diamond_positions_indexed_vbo);
  glDeleteBuffers(1, &diamond_colors_indexed_vbo);
}

void Application::render() {
  // Task 4.2: Modify the glClear call to clear the depth buffer as well
  glClear(GL_COLOR_BUFFER_BIT);
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(program);

  glBindVertexArray(diamond_vao);
  glDrawArrays(GL_TRIANGLES, 0, 12);

  glBindVertexArray(triangle_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindVertexArray(square_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindVertexArray(diamond_indexed_vao);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
}

void Application::on_resize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}
void Application::on_mouse_move(GLFWwindow *window, double x, double y) {}
void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) {}
void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  // Task 4.1: Change the polygon mode to GL_LINE when L is pressed on the keyboard
  //                                      GL_FILL when F is pressed on the keyboard
  switch (static_cast<char>(key)) {
    case 'L':
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;

    case 'F':
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
  }
}
