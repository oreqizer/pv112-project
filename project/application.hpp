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

struct ObjectUBO {
  glm::mat4 model;         // [  0 -  64) bytes
  glm::vec4 colorAmbient;  // [ 64 -  80) bytes
  glm::vec4 colorDiffuse;  // [ 80 -  96) bytes

  // Contains shininess in .w element
  glm::vec4 colorSpecular; // [ 96 - 112) bytes
};

// ----------------------------------------------------------------------------
// APPLICATION
// ----------------------------------------------------------------------------
class Application {
public:
  Application(size_t initial_width, size_t initial_height);
  ~Application();

  void render();

  void on_resize(GLFWwindow *window, int width, int height);
  void on_mouse_move(GLFWwindow *window, double x, double y);
  void on_mouse_pressed(GLFWwindow *window, int button, int action, int mods);
  void on_key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
  size_t width;
  size_t height;

  Game *game;

  Camera camera;

  // Programs
  GLuint programCore = create_program("build/project/shaders/core.vert", "build/project/shaders/core.frag");

  // Objects
  Mesh cube = Mesh::cube();

  // UBOs
  GLuint bufferCamera = 0;
  CameraUBO uboCamera;

  GLuint bufferLight = 0;
  LightUBO uboLight;

  // Snake / food
  std::vector<ObjectUBO> snake;
  GLuint bufferSnake = 0;

  // Walls
  std::vector<ObjectUBO> walls;
  GLuint bufferWalls = 0;
};
