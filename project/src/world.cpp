#include <vector>

#include "settings.hpp"

#include "world.hpp"

World::World() {
    for (int side = 0; side < 6; side++) {
        for (int x = 0; x < SIZE; x++) {
            for (int y = 0; y < SIZE; y++) {
                switch (side) {
                    case 0:
                        // Top
                        wall.push_back(glm::vec3(x, SIZE + 1, y));
                        break;
                    case 1:
                        // Bottom
                        wall.push_back(glm::vec3(x, -1, y));
                        break;
                    case 2:
                        // Right
                        wall.push_back(glm::vec3(SIZE + 1, x, y));
                        break;
                    case 3:
                        // Left
                        wall.push_back(glm::vec3(-1, x, y));
                        break;
                    case 4:
                        // Forward
                        wall.push_back(glm::vec3(x, y, SIZE + 1));
                        break;
                    case 5:
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
