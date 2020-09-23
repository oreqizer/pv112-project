#include <iostream>

#include "application.hpp"

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  game = new Game();

  // --------------------------------------------------------------------------
  // Initialize UBO Data
  // --------------------------------------------------------------------------

  // Camera
  camera.setDistance(SIZE);
  camera.setEyeOffset(Game::center);

  uboCamera.position = glm::vec4(camera.getEyePosition(), 1.0f);
  uboCamera.view = glm::lookAt(camera.getEyePosition(), Game::center, glm::vec3(0.0f, 1.0f, 0.0f));
  uboCamera.projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.01f, 1000.0f);

  // Lights
  std::vector<glm::vec4> edges = {
      glm::vec4(0.0, 0.0, 0.0, 1.0),    glm::vec4(SIZE, 0.0, 0.0, 1.0), glm::vec4(SIZE, SIZE, 0.0, 1.0), glm::vec4(SIZE, 0.0, SIZE, 1.0),
      glm::vec4(SIZE, SIZE, SIZE, 1.0), glm::vec4(0.0, SIZE, 0.0, 1.0), glm::vec4(0.0, SIZE, SIZE, 1.0), glm::vec4(0.0, 0.0, SIZE, 1.0),
  };
  for (auto edge : edges) {
    lights.push_back({
        edge,
        glm::vec4(0.0), // ambient
        glm::vec4(1.0), // diffuse
        glm::vec4(0.0), // specular
    });
  }

  // Initial walls
  fillWalls();

  // --------------------------------------------------------------------------
  // CREATE BUFFERS
  // --------------------------------------------------------------------------

  glCreateBuffers(1, &bufferCamera);
  glNamedBufferStorage(bufferCamera, sizeof(CameraUBO), &uboCamera, GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferLights);
  glNamedBufferStorage(bufferLights, lights.size() * sizeof(ObjectUBO), lights.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferSnake);
  glNamedBufferStorage(bufferSnake, SIZE * SIZE * SIZE * sizeof(ObjectUBO), snake.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferWalls);
  glNamedBufferStorage(bufferWalls, walls.size() * sizeof(ObjectUBO), walls.data(), GL_DYNAMIC_STORAGE_BIT);
}

Application::~Application() {
  glDeleteProgram(programCore);

  glDeleteBuffers(1, &bufferCamera);
  glDeleteBuffers(1, &bufferLights);
  glDeleteBuffers(1, &bufferSnake);
  glDeleteBuffers(1, &bufferWalls);
}

void Application::update() { game->update(); }

void Application::render() {
  // =====
  // TODOs
  // =====
  //
  // 3. https://learnopengl.com/In-Practice/2D-Game/Audio
  // 4. GUI https://stackoverflow.com/questions/5898922/i-have-a-problem-about-opengl-glut-glutstrokecharacter-the-code-did-not-work

  // --------------------------------------------------------------------------
  // UPDATE UBOS
  // --------------------------------------------------------------------------

  // Camera
  uboCamera.position = glm::vec4(camera.getEyePosition(), 1.0f);
  uboCamera.view = glm::lookAt(camera.getEyePosition(), Game::center, glm::vec3(0.0f, 1.0f, 0.0f));

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
  glBindBufferBase(GL_UNIFORM_BUFFER, 1, bufferLights);

  auto alphaUniform = glGetUniformLocation(programCore, "alpha");

  // Snake and food
  glUniform1f(alphaUniform, 0.75);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferSnake);
  glBindVertexArray(cube.get_vao());
  glDrawElementsInstanced(cube.get_mode(), static_cast<GLsizei>(cube.get_indices_count()), GL_UNSIGNED_INT, nullptr,
                          static_cast<GLsizei>(snake.size()));

  // Walls
  glUniform1f(alphaUniform, 0.1);
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
    // Oscillating blocks
    auto distance = glm::distance(glm::vec3(0.0), pos);
    auto center = glm::vec3(SIZE / 2);
    auto offset = glm::normalize(pos - center) * static_cast<float>(sin(distance / (SIZE * 2) + time) + 1) * 0.1f;
    auto translate = glm::translate(glm::mat4(1.0), pos + offset);

    // Fancy colors
    auto distance = glm::distance(glm::vec3(0.0), pos);
    auto r = sin(distance / (SIZE * 2) + time) / 2 + 0.5;
    auto g = sin(distance / (SIZE * 2) + time + 3.14) / 2 + 0.5;
    auto b = sin(distance / (SIZE * 2) + time + 3.14 / 2) / 2 + 0.5;

    walls.push_back({
        translate, glm::vec4(r, g, b, 0.1), // ambient
        glm::vec4(0.0),                     // diffuse
        glm::vec4(0.0),                     // specular
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

void Application::onResize(GLFWwindow *window, int width, int height) {
  this->width = width;
  this->height = height;
}

void Application::onMouseMove(GLFWwindow *window, double x, double y) { camera.onMouseMove(x, y); }

void Application::onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_W:
      game->snake->turn(Arrow::Top);
      break;
    case GLFW_KEY_A:
      game->snake->turn(Arrow::Back);
      break;
    case GLFW_KEY_S:
      game->snake->turn(Arrow::Bottom);
      break;
    case GLFW_KEY_D:
      game->snake->turn(Arrow::Right);
      break;
    case GLFW_KEY_Q:
      game->snake->turn(Arrow::Left);
      break;
    case GLFW_KEY_E:
      game->snake->turn(Arrow::Forward);
      break;
    }
  }
}
