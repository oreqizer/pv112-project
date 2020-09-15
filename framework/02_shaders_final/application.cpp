#include "application.hpp"
#include "utilities.hpp"

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Reserved for future lesson
  glCreateVertexArrays(1, &vao);
}

Application::~Application() {
  glDeleteVertexArrays(1, &vao);

  glDeleteProgram(program1);
  glDeleteProgram(program2);
}

void Application::render() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(vao);

  glViewport(0, 0, width / 2, height);
  glUseProgram(program1);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glViewport(width / 2, 0, width / 2, height);
  glUseProgram(program2);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::on_resize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}
void Application::on_mouse_move(GLFWwindow *window, double x, double y) {}
void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) {}
void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_R:
      std::swap(program1, program2);
      break;
    }
  }
}