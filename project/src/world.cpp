#include <vector>

#include "settings.hpp"

#include "world.hpp"

World::World() {
    // Top / Bottom
    // Overreach both sides
    for (int side = 0; side < 2; side++) {
        for (int x = -1; x < SIZE + 1; x++) {
            for (int z = -1; z < SIZE + 1; z++) {
                switch (side) {
                    case 0:
                        // Top
                        wall.push_back(glm::vec3(x, SIZE + 1, z));
                        break;
                    case 1:
                        // Bottom
                        wall.push_back(glm::vec3(x, -1, z));
                        break;
                }
            }
        }
    }

    // Right / Left
    // Overreach Z axis
    for (int side = 0; side < 2; side++) {
        for (int y = 0; y < SIZE; y++) {
            for (int z = -1; z < SIZE + 1; z++) {
                switch (side) {
                    case 1:
                        // Right
                        wall.push_back(glm::vec3(SIZE + 1, y, z));
                        break;
                    case 1:
                        // Left
                        wall.push_back(glm::vec3(-1, y, z));
                        break;
                }
            }
        }
    }

    // Front / Back
    // No overreaching
    for (int side = 0; side < 2; side++) {
        for (int x = 0; x < SIZE; x++) {
            for (int y = 0; y < SIZE; y++) {
                switch (side) {
                    case 1:
                        // Forward
                        wall.push_back(glm::vec3(x, y, SIZE + 1));
                        break;
                    case 2:
                        // Back
                        wall.push_back(glm::vec3(x, y, -1));
                        break;
                }
            }
        }
    }
}

std::vector<glm::vec3> World::render() {
    return wall;
}
