#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Food {
public:
    Food();
    ~Food() = default;

    void generate(const std::vector<glm::vec3> &options);

    glm::vec3 position;
};
