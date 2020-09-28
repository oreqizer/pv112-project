#include <iostream>

#include "application.hpp"

const float scaleCube = 2;
const glm::vec3 scaleCubeVec = glm::vec3(scaleCube);

const float lightConeCos = 0.95f;

const float alphaSnake = 1.0f;
const float alphaWall = 0.025f;

Application::Application(size_t initial_width, size_t initial_height) {
  this->width = initial_width;
  this->height = initial_height;

  game = new Game();

  // --------------------------------------------------------------------------
  // Initialize UBO Data
  // --------------------------------------------------------------------------

  // Camera
  camera.setDistance(settings::size * scaleCube * 2);
  camera.setEyeOffset(Game::center * scaleCubeVec);

  uboCamera.position = glm::vec4(camera.getEyePosition(), 1.0f);
  uboCamera.view = glm::lookAt(camera.getEyePosition(), Game::center * scaleCubeVec, glm::vec3(0.0f, 1.0f, 0.0f));
  uboCamera.projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.01f, 1000.0f);

  // Lights
  glm::vec4 ambient(0.2f);
  glm::vec4 diffuse(0.5f); 
  glm::vec4 specular(1.0f);

  auto arenaSize = settings::size * scaleCube;

  lights.push_back({glm::vec4(0, arenaSize, 0, 1.0), glm::vec4(0.5, -1, 0.5, lightConeCos), ambient, diffuse, specular});
  lights.push_back({glm::vec4(arenaSize, arenaSize, 0, 1.0), glm::vec4(-0.5, -1, 0.5, lightConeCos), ambient, diffuse, specular});
  lights.push_back({glm::vec4(0, arenaSize, arenaSize, 1.0), glm::vec4(0.5, -1, -0.5, lightConeCos), ambient, diffuse, specular});
  lights.push_back({glm::vec4(arenaSize, arenaSize, arenaSize, 1.0), glm::vec4(-0.5, -1, -0.5, lightConeCos), ambient, diffuse, specular});

  // Initial walls
  fillWalls();

  // --------------------------------------------------------------------------
  // CREATE BUFFERS
  // --------------------------------------------------------------------------

  glCreateBuffers(1, &bufferCamera);
  glNamedBufferStorage(bufferCamera, sizeof(CameraUBO), &uboCamera, GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferLights);
  glNamedBufferStorage(bufferLights, lights.size() * sizeof(LightUBO), lights.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferSnake);
  glNamedBufferStorage(bufferSnake, settings::size * settings::size * settings::size * sizeof(SnakeUBO), snake.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &bufferWalls);
  glNamedBufferStorage(bufferWalls, walls.size() * sizeof(WallUBO), walls.data(), GL_DYNAMIC_STORAGE_BIT);
}

Application::~Application() {
  glDeleteProgram(programSnake);

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
  uboCamera.view = glm::lookAt(camera.getEyePosition(), Game::center * scaleCubeVec, glm::vec3(0.0f, 1.0f, 0.0f));

  glNamedBufferSubData(bufferCamera, 0, sizeof(CameraUBO), &uboCamera);

  // Snake
  fillSnake();

  glNamedBufferSubData(bufferSnake, 0, snake.size() * sizeof(SnakeUBO), snake.data());

  // --------------------------------------------------------------------------
  // DRAW THE SCENE
  // --------------------------------------------------------------------------
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, this->width, this->height);

  // === 1. BLEND ===
  glEnable(GL_BLEND);  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Snake and food
  glEnable(GL_DEPTH_TEST);

  glUseProgram(programSnake);

  glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferCamera);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferLights);

  auto alphaSnakeUniform = glGetUniformLocation(programSnake, "alpha");

  glUniform1f(alphaSnakeUniform, alphaSnake);

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, bufferSnake);
  glBindVertexArray(cube.get_vao());
  glDrawElementsInstanced(cube.get_mode(), static_cast<GLsizei>(cube.get_indices_count()), GL_UNSIGNED_INT, nullptr,
                          static_cast<GLsizei>(snake.size()));
                          
  glDisable(GL_DEPTH_TEST);

  // Walls
  glUseProgram(programWall);

  glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferCamera);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferLights);

  auto alphaWallUniform = glGetUniformLocation(programWall, "alpha");
  auto sizeUniform = glGetUniformLocation(programWall, "size");
  auto timeUniform = glGetUniformLocation(programWall, "time");

  glUniform1f(alphaWallUniform, alphaWall);
  glUniform1i(sizeUniform, settings::size);
  glUniform1f(timeUniform, glfwGetTime());

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
    auto position = pos * scaleCubeVec;

    auto distance = glm::distance(glm::vec3(0.0), position);
    auto translate = glm::translate(glm::mat4(1.0), position);

    walls.push_back({
        translate,             // position
        glm::vec4(1.0),        // ambient
        glm::vec4(1.0),        // diffuse
        glm::vec4(1.0),        // specular
        glm::vec4(distance, 0.0, 0.0, 0.0),
    });
  }
}

void Application::fillSnake() {
  snake.clear();

  auto foodPosition = game->food->render();
  auto snakePositions = game->snake->render();

  auto ambient = game->state == GameState::Crashed ? glm::vec4(1.0, 0, 0, 1.0) : glm::vec4(1.0);
  auto diffuse = game->state == GameState::Crashed ? glm::vec4(1.0, 0, 0, 1.0) : glm::vec4(1.0);
  auto specular = game->state == GameState::Crashed ? glm::vec4(1.0, 0, 0, 4.0) : glm::vec4(1.0, 1.0, 1.0, 4);

  snake.push_back({
      glm::translate(glm::mat4(1.0), foodPosition * scaleCubeVec),
      glm::vec4(0.25),
      glm::vec4(1.0),
      glm::vec4(1.0, 1.0, 1.0, 4),
  });

  for (auto pos : snakePositions) {
    auto position = pos * scaleCubeVec;
    auto translate = glm::translate(glm::mat4(1.0), position);

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
    case GLFW_KEY_S:
      game->snake->turn(Arrow::Bottom);
      break;
    case GLFW_KEY_D:
      game->snake->turn(Arrow::Left);
      break;
    case GLFW_KEY_A:
      game->snake->turn(Arrow::Right);
      break;
    case GLFW_KEY_E:
      game->snake->turn(Arrow::Back);
      break;
    case GLFW_KEY_Q:
      game->snake->turn(Arrow::Forward);
      break;
    case GLFW_KEY_SPACE:
      game = new Game();
      break;
    }
  }
}
