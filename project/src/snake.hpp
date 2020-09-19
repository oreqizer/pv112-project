#include <vector>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.hpp"

#include "settings.hpp"
#include "food.hpp"

namespace dir {
    glm::vec3 top = glm::vec3(0, 1, 0);
    glm::vec3 bottom = glm::vec3(0, -1, 0);
    glm::vec3 right = glm::vec3(1, 0, 0);
    glm::vec3 left = glm::vec3(-1, 0, 0);
    glm::vec3 forward = glm::vec3(0, 0, 1);
    glm::vec3 back = glm::vec3(0, 0, -1);
};

class Snake {
public:
    Snake(Food &food);
    ~Snake() = default;

    std::vector<Mesh> render();
    void update();
    void turn(Arrow arrow);
    void move();
    bool isNextMovable();
    bool isColliding(const glm::vec3 &pos);

    Food &food;

    std::vector<glm::vec3> segments;
private:
    std::chrono::milliseconds timeMove;
    glm::vec3 direction = dir::forward;
};
