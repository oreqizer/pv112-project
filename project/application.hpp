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
  glm::vec4 ambient_color;
  glm::vec4 diffuse_color;
  glm::vec4 specular_color;
};

struct ObjectUBO {
  glm::mat4 model_matrix;  // [  0 -  64) bytes
  glm::vec4 ambient_color; // [ 64 -  80) bytes
  glm::vec4 diffuse_color; // [ 80 -  96) bytes

  // Contains shininess in .w element
  glm::vec4 specular_color; // [ 96 - 112) bytes
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
  GLuint main_program = create_program("build/08_ubo/shaders/main.vert", "build/08_ubo/shaders/main.frag");
  GLuint draw_light_program = create_program("build/08_ubo/shaders/draw_light.vert", "build/08_ubo/shaders/draw_light.frag");

  // Objects
  Mesh cube = Mesh::cube();
  Mesh sphere = Mesh::sphere();
  Mesh teapot = Mesh::teapot();

  // UBOs
  GLuint camera_buffer = 0;
  CameraUBO camera_ubo;

  GLuint light_buffer = 0;
  LightUBO light_ubo;

  GLuint object_buffer = 0;
  ObjectUBO object_ubo;

  // Many Lights
  std::vector<LightUBO> lights;
  GLuint lights_buffer = 0;

  // Instancing/MultiDraw
  std::vector<ObjectUBO> instanced_objects;
  GLuint instanced_objects_buffer = 0;
};