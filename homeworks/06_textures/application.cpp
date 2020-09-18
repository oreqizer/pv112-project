#include <iostream>

#include "application.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stbi.h"

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // Task 6.1: Initialize textures: "images/wood.jpg" and "images/rocks.jpg"
  int width, height, channels;
  unsigned char *wood_raw = stbi_load("images/wood.jpg", &width, &height, &channels, 4);
  glCreateTextures(GL_TEXTURE_2D, 1, &wood_texture);

  glTextureStorage2D(wood_texture, 
                    std::log2(width), // NUMBER OF MIMPMAP LEVELS
                    GL_RGBA8,         // SIZED INTERNAL FORMAT
                    width, height);

  glTextureSubImage2D(
    wood_texture,
    0,
    0,
    0,
    width,
    height,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    wood_raw
  );
  glGenerateTextureMipmap(wood_texture);

  unsigned char *rocks_raw = stbi_load("images/rocks.jpg", &width, &height, &channels, 4);
  glCreateTextures(GL_TEXTURE_2D, 1, &rocks_texture);

  glTextureStorage2D(rocks_texture, 
                    std::log2(width), // NUMBER OF MIMPMAP LEVELS
                    GL_RGBA8,         // SIZED INTERNAL FORMAT
                    width, height);

  glTextureSubImage2D(
    rocks_texture,
    0,
    0,
    0,
    width,
    height,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    rocks_raw
  );
  glGenerateTextureMipmap(rocks_texture);
}

Application::~Application() {

  glDeleteProgram(main_program);
}

void Application::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Camera
  glm::vec3 eye_position = camera.get_eye_position();
  glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.1f, 100.0f);
  glm::mat4 view_matrix = glm::lookAt(eye_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 model_matrix = glm::mat4(1.0f);

  glProgramUniformMatrix4fv(main_program, 0, 1, false, glm::value_ptr(projection_matrix));
  glProgramUniformMatrix4fv(main_program, 1, 1, false, glm::value_ptr(model_matrix));
  glProgramUniformMatrix4fv(main_program, 2, 1, false, glm::value_ptr(view_matrix));
  glProgramUniform3f(main_program, 3, eye_position.x, eye_position.y, eye_position.z);

  // Light
  glProgramUniform4f(main_program, 4, 0.0f, 3.0f, 2.0f, light);

  glProgramUniform3f(main_program, 5, 0.2f, 0.2f, 0.2f);
  glProgramUniform3f(main_program, 6, 1.0f, 1.0f, 1.0f);
  glProgramUniform3f(main_program, 7, 0.0f, 0.0f, 0.0f);

  // Material
  glProgramUniform3f(main_program, 8, 0.2f, 0.2f, 0.2f);
  glProgramUniform3f(main_program, 9, 0.5f, 0.5f, 0.5f);
  glProgramUniform3f(main_program, 10, 0.0f, 0.0f, 0.0f);
  glProgramUniform1f(main_program, 11, 4.0f);

  glUseProgram(main_program);

  // Task 6.2: Bind a texture using glBindTextureUnit for each object 
  //           (you can choose either wood or rocks texure)
  glBindTextureUnit(12, wood_texture);
  glProgramUniformMatrix4fv(main_program, 1, 1, false, glm::value_ptr(model_matrix));
  glProgramUniform3f(main_program, 9, 1.0f, 1.0f, 1.0f);
  cube.draw();

  model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
  glBindTextureUnit(12, rocks_texture);
  glProgramUniformMatrix4fv(main_program, 1, 1, false, glm::value_ptr(model_matrix));
  glProgramUniform3f(main_program, 9, 0.0f, 0.0f, 0.8f);
  sphere.draw();

  model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f));
  glBindTextureUnit(12, 0);
  glProgramUniformMatrix4fv(main_program, 1, 1, false, glm::value_ptr(model_matrix));
  glProgramUniform3f(main_program, 9, 0.8f, 0.0f, 0.0f);
  teapot.draw();
}

void Application::on_resize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}
void Application::on_mouse_move(GLFWwindow *window, double x, double y) { camera.on_mouse_move(x, y); }
void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) { camera.on_mouse_button(button, action, mods); }
void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_F:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    case GLFW_KEY_L:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case GLFW_KEY_Q:
      light = light == 1.0f ? 0.0f : 1.0f;
      break;
    }
  }
}