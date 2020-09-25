#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>

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
