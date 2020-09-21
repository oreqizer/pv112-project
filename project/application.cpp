#include <iostream>

#include "application.hpp"

float random() { return rand() / (RAND_MAX + 1.); }
float random_neg() { return (rand() / (RAND_MAX + 1.) * 2.0) - 1.0; }

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  game = new Game();

  // --------------------------------------------------------------------------
  // Initialize UBO Data
  // --------------------------------------------------------------------------

  // TODO
  uboCamera.position = glm::vec4(camera.get_eye_position(), 1.0f);
  uboCamera.projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.01f, 1000.0f);
  uboCamera.view = glm::lookAt(camera.get_eye_position(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  // TODO
  uboLight.position = glm::vec4(0.0f, 3.0f, 2.0f, 1.0f);
  uboLight.ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
  uboLight.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  uboLight.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

  fillWalls();

  // --------------------------------------------------------------------------
  // CREATE BUFFERS
  // --------------------------------------------------------------------------

  glCreateBuffers(1, &bufferCamera);
  glNamedBufferStorage(bufferCamera, sizeof(CameraUBO), &uboCamera, GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferLight);
  glNamedBufferStorage(bufferLight, sizeof(LightUBO), &uboLight, GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferSnake);
  glNamedBufferStorage(bufferSnake, snake.size() * sizeof(ObjectUBO), snake.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferWalls);
  glNamedBufferStorage(bufferWalls, walls.size() * sizeof(ObjectUBO), walls.data(), GL_DYNAMIC_STORAGE_BIT);
}

Application::~Application() {
  glDeleteProgram(programCore);

  glDeleteBuffers(1, &bufferCamera);
}

void Application::update() {
  game->update();
}

void Application::render() {
  // =====
  // TODOs
  // =====
  //
  // 1. fragment shader pimp
  // 2. correct camera alignment
  // 3. https://learnopengl.com/In-Practice/2D-Game/Audio
  // 4. GUI

  // --------------------------------------------------------------------------
  // UPDATE UBOS
  // --------------------------------------------------------------------------

  // Camera

  // TODO
  uboCamera.position = glm::vec4(camera.get_eye_position(), 1.0f);
  uboCamera.view = glm::lookAt(camera.get_eye_position(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  glNamedBufferSubData(bufferCamera, 0, sizeof(CameraUBO), &uboCamera);

  // Snake
  fillSnake();

  glNamedBufferSubData(bufferSnake, 0, snake.size() * sizeof(ObjectUBO), snake.data());

  // Walls
  fillWalls();

  glNamedBufferSubData(bufferWalls, 0, walls.size() * sizeof(ObjectUBO), walls.data());

  // --------------------------------------------------------------------------
  // DRAW THE SCENE
  // --------------------------------------------------------------------------
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, this->width, this->height);
  glEnable(GL_DEPTH_TEST);

  glUseProgram(programCore);

  glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferCamera);
  glBindBufferBase(GL_UNIFORM_BUFFER, 1, bufferLight);

  // Snake and food
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferSnake);
  glBindVertexArray(cube.get_vao());
  glDrawElementsInstanced(cube.get_mode(), static_cast<GLsizei>(cube.get_indices_count()), GL_UNSIGNED_INT, nullptr,
                          static_cast<GLsizei>(snake.size()));

  // Walls
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferWalls);
  glBindVertexArray(cube.get_vao());
  glDrawElementsInstanced(cube.get_mode(), static_cast<GLsizei>(cube.get_indices_count()), GL_UNSIGNED_INT, nullptr,
                          static_cast<GLsizei>(walls.size()));
}

void Application::fillWalls() {
  walls.clear();

  auto wallPositions = game->world->render();

  auto time = glfwGetTime();

  for (auto pos : wallPositions) {
    auto translate = glm::translate(glm::mat4(1.0), pos);
    auto distance = glm::distance(glm::vec3(0.0), pos);
    auto r = sin(distance / SIZE + time) / 2 + 0.5;
    auto g = sin(distance / SIZE + time + 3.14) / 2 + 0.5;
    auto b = sin(distance / SIZE + time + 3.14 / 2) / 2 + 0.5;

    walls.push_back({
        translate,
        glm::vec4(r, g, b, 0.1), // ambient
        glm::vec4(0.0),          // diffuse
        glm::vec4(0.0),          // specular
    });
  }
}

void Application::fillSnake() {
  snake.clear();

  auto foodPosition = game->food->render();
  auto snakePositions = game->snake->render();

  auto ambient = glm::vec4(0.0);
  auto diffuse = glm::vec4(1.0, 1.0, 1.0, 0.5);
  auto specular = glm::vec4(0.0);

  snake.push_back({
      glm::translate(glm::mat4(1.0), foodPosition),
      ambient,
      diffuse,
      specular,
  });

  for (auto pos : snakePositions) {
    auto translate = glm::translate(glm::mat4(1.0), pos);

    snake.push_back({
        translate,
        ambient,
        diffuse,
        specular,
    });
  }
}

void Application::on_resize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;
}
void Application::on_mouse_move(GLFWwindow *window, double x, double y) { camera.on_mouse_move(x, y); }
void Application::on_mouse_pressed(GLFWwindow *window, int button, int action, int mods) { camera.on_mouse_button(button, action, mods); }
void Application::on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_W:
      game->snake->turn(settings::Arrow::Top);
      break;
    case GLFW_KEY_A:
      game->snake->turn(settings::Arrow::Back);
      break;
    case GLFW_KEY_S:
      game->snake->turn(settings::Arrow::Bottom);
      break;
    case GLFW_KEY_D:
      game->snake->turn(settings::Arrow::Right);
      break;
    case GLFW_KEY_Q:
      game->snake->turn(settings::Arrow::Left);
      break;
    case GLFW_KEY_E:
      game->snake->turn(settings::Arrow::Forward);
      break;
    }
  }
}
