#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.hpp"

class World {
public:
  World();
  ~World() = default;

  std::vector<glm::vec3> render();

private:
  std::vector<glm::vec3> wall;
};

#endif
