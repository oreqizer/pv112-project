#include <iostream>

#include "application.hpp"
#include "data.hpp"

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glCreateVertexArrays(1, &vao_empty);

  // Task 3.3: Create Vertex Buffer Objects (VBO)
  //           Copy vertex data found in data.hpp to VBOs
  // Task 3.4-3.6: Create Vertex Array Objects (VAO) fetching data from VBOs
}

Application::~Application() {
  glDeleteProgram(program);
  glDeleteProgram(program_vao);
}

void Application::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  // Task 3.1: Draw a Square
  // Task 3.2: Draw a Square using GL_TRIANGLE_STRIP
  // glUseProgram(program);
  // glBindVertexArray(vao_empty);
  // glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

  // Task 3.4-3.6: Draw all objects
  glUseProgram(program_vao);

  // Diamond
  // -------
  glCreateBuffers(1, &vboDiamondVertices);
  glNamedBufferStorage(vboDiamondVertices, sizeof(diamond_positions), &diamond_positions, NULL);

  glCreateBuffers(1, &vboDiamondColors);
  glNamedBufferStorage(vboDiamondColors, sizeof(diamond_colors), &diamond_colors, NULL);

  glCreateVertexArrays(1, &vaoDiamond);
  glVertexArrayVertexBuffer(vaoDiamond, LOC_POSITION, vboDiamondVertices, 0, 3 * sizeof(float));
  glVertexArrayVertexBuffer(vaoDiamond, LOC_COLOR, vboDiamondColors, 0, 3 * sizeof(float));

  glEnableVertexArrayAttrib(vaoDiamond, LOC_POSITION);
  glVertexArrayAttribFormat(vaoDiamond, LOC_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoDiamond, LOC_POSITION, LOC_POSITION);

  glEnableVertexArrayAttrib(vaoDiamond, LOC_COLOR);
  glVertexArrayAttribFormat(vaoDiamond, LOC_COLOR, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoDiamond, LOC_COLOR, LOC_COLOR);

  glBindVertexArray(vaoDiamond);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(diamond_positions) / (3 * sizeof(float)));

  // Square
  // ------
  glCreateBuffers(1, &vboSquare);
  glNamedBufferStorage(vboSquare, sizeof(square_data), &square_data, NULL);

  glCreateVertexArrays(1, &vaoSquare);
  glVertexArrayVertexBuffer(vaoSquare, LOC_POSITION, vboSquare, 0, 3 * sizeof(float));
  glVertexArrayVertexBuffer(vaoSquare, LOC_COLOR, vboSquare, sizeof(square_data) / 2, 3 * sizeof(float));

  glEnableVertexArrayAttrib(vaoSquare, LOC_POSITION);
  glVertexArrayAttribFormat(vaoSquare, LOC_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoSquare, LOC_POSITION, LOC_POSITION);

  glEnableVertexArrayAttrib(vaoSquare, LOC_COLOR);
  glVertexArrayAttribFormat(vaoSquare, LOC_COLOR, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoSquare, LOC_COLOR, LOC_COLOR);

  glBindVertexArray(vaoSquare);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(square_data) / (3 * sizeof(float)) / 2);
  
  // Triangle
  // --------
  glCreateBuffers(1, &vboTriangle);
  glNamedBufferStorage(vboTriangle, sizeof(triangle_vertices), &triangle_vertices, NULL);

  glCreateVertexArrays(1, &vaoTriangle);
  glVertexArrayVertexBuffer(vaoTriangle, LOC_POSITION, vboTriangle, 0, sizeof(Vertex));
  glVertexArrayVertexBuffer(vaoTriangle, LOC_COLOR, vboTriangle, 0, sizeof(Vertex));

  glEnableVertexArrayAttrib(vaoTriangle, LOC_POSITION);
  glVertexArrayAttribFormat(vaoTriangle, LOC_POSITION, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
  glVertexArrayAttribBinding(vaoTriangle, LOC_POSITION, LOC_POSITION);

  glEnableVertexArrayAttrib(vaoTriangle, LOC_COLOR);
  glVertexArrayAttribFormat(vaoTriangle, LOC_COLOR, 3, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, color));
  glVertexArrayAttribBinding(vaoTriangle, LOC_COLOR, LOC_COLOR);

  glBindVertexArray(vaoTriangle);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle_vertices) / sizeof(Vertex));
  
  // Diamond 2
  // ---------
  glCreateBuffers(1, &vboDiamondVerticesIndexed);
  glNamedBufferStorage(vboDiamondVerticesIndexed, sizeof(diamond_positions_indexed), &diamond_positions_indexed, NULL);

  glCreateBuffers(1, &vboDiamondColorsIndexed);
  glNamedBufferStorage(vboDiamondColorsIndexed, sizeof(diamond_colors_indexed), &diamond_colors_indexed, NULL);

  glCreateBuffers(1, &vboDiamondIndicesIndexed);
  glNamedBufferStorage(vboDiamondIndicesIndexed, sizeof(diamond_indices), &diamond_indices, NULL);

  glCreateVertexArrays(1, &vaoDiamondIndexed);
  glVertexArrayVertexBuffer(vaoDiamondIndexed, LOC_POSITION, vboDiamondVerticesIndexed, 0, 3 * sizeof(float));
  glVertexArrayVertexBuffer(vaoDiamondIndexed, LOC_COLOR, vboDiamondColorsIndexed, 0, 3 * sizeof(float));

  glEnableVertexArrayAttrib(vaoDiamondIndexed, LOC_POSITION);
  glVertexArrayAttribFormat(vaoDiamondIndexed, LOC_POSITION, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoDiamondIndexed, LOC_POSITION, LOC_POSITION);

  glEnableVertexArrayAttrib(vaoDiamondIndexed, LOC_COLOR);
  glVertexArrayAttribFormat(vaoDiamondIndexed, LOC_COLOR, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vaoDiamondIndexed, LOC_COLOR, LOC_COLOR);

  glVertexArrayElementBuffer(vaoDiamondIndexed, vboDiamondIndicesIndexed);
  
  glBindVertexArray(vaoDiamondIndexed);
  glDrawElements(GL_TRIANGLES, sizeof(diamond_positions_indexed) / 3 * sizeof(float), GL_UNSIGNED_INT, 0);
}

void Application::on_resize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}
void Application::on_mouse_move(GLFWwindow *window, double x, double y) {}
void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) {}
void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {}