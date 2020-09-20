#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.hpp"

class Food {
public:
    Food();
    ~Food() = default;

    std::vector<Mesh> render();
    void generate(const std::vector<glm::vec3> &options);

    glm::vec3 position;
};
