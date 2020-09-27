#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utilities.hpp"
#include "program.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "texture.hpp"

#include "src/game.hpp"

// ----------------------------------------------------------------------------
// UNIFORM STRUCTS
// ----------------------------------------------------------------------------
struct CameraUBO {
  glm::mat4 projection;
  glm::mat4 view;
  glm::vec4 position;
};

struct LightUBO {
  glm::vec4 position;
  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;
};

struct SnakeUBO {
  glm::mat4 model;        // [  0 -  64) bytes
  glm::vec4 colorAmbient; // [ 64 -  80) bytes
  glm::vec4 colorDiffuse; // [ 80 -  96) bytes

  // Contains shininess in .w element
  glm::vec4 colorSpecular; // [ 96 - 112) bytes
};

struct WallUBO {
  glm::mat4 model;        // [  0 -  64) bytes
  glm::vec4 colorAmbient; // [ 64 -  80) bytes
  glm::vec4 colorDiffuse; // [ 80 -  96) bytes

  // Contains shininess in .w element
  glm::vec4 colorSpecular; // [ 96 - 112) bytes

  // Contains distance in .x element
  glm::vec4 distance;      // [112 - 128) bytes
};

// ----------------------------------------------------------------------------
// APPLICATION
// ----------------------------------------------------------------------------
class Application {
public:
  Application(size_t initial_width, size_t initial_height);
  ~Application();

  void update();
  void render();

  void fillWalls();
  void fillSnake();

  void onResize(GLFWwindow *window, int width, int height);
  void onMouseMove(GLFWwindow *window, double x, double y);
  void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
  size_t width;
  size_t height;

  Game *game;

  Camera camera;

  // Programs
  GLuint programSnake = create_program("../shaders/snake.vert", "../shaders/snake.frag");
  GLuint programWall = create_program("../shaders/wall.vert", "../shaders/wall.frag");

  // Objects
  Mesh cube = Mesh::cube();

  // UBOs
  GLuint bufferCamera = 0;
  CameraUBO uboCamera;

  // Lights
  std::vector<LightUBO> lights;
  GLuint bufferLights = 0;

  // Snake / food
  std::vector<SnakeUBO> snake;
  GLuint bufferSnake = 0;

  // Walls
  std::vector<WallUBO> walls;
  GLuint bufferWalls = 0;
};
