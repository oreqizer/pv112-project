#include <vector>

#include "settings.hpp"

#include "world.hpp"

World::World() {
  // Top / Bottom
  // Overreach both sides
  for (int x = -1; x < SIZE + 1; x++) {
    for (int z = -1; z < SIZE + 1; z++) {
      wall.push_back(glm::vec3(x, SIZE + 1, z));
    }
  }
  for (int x = -1; x < SIZE + 1; x++) {
    for (int z = -1; z < SIZE + 1; z++) {
      wall.push_back(glm::vec3(x, -1, z));
    }
  }

  // Right / Left
  // Overreach Z axis
  for (int y = 0; y < SIZE; y++) {
    for (int z = -1; z < SIZE + 1; z++) {
      wall.push_back(glm::vec3(SIZE + 1, y, z));
    }
  }
  for (int y = 0; y < SIZE; y++) {
    for (int z = -1; z < SIZE + 1; z++) {
      wall.push_back(glm::vec3(-1, y, z));
    }
  }

  // Front / Back
  // No overreaching
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      wall.push_back(glm::vec3(x, y, SIZE + 1));
    }
  }
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      wall.push_back(glm::vec3(x, y, -1));
    }
  }
}

std::vector<glm::vec3> World::render() { return wall; }
