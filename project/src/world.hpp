#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.hpp"

class World {
public:
World();
~World() = default;

std::vector<Mesh> render();

private:
    std::vector<glm::vec3> wall;
};
