#pragma once
#ifndef FOOD_H
#define FOOD_H

#include <vector>

#include <glm/glm.hpp>

class Food {
public:
  Food() {};
  ~Food() = default;

  glm::vec3 render();
  void generate(const std::vector<glm::vec3> &options);

  glm::vec3 position;
};

#endif
