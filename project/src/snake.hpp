#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.hpp"

#include "settings.hpp"
#include "food.hpp"

class Snake {
public:
  static const glm::vec3 top;
  static const glm::vec3 bottom;
  static const glm::vec3 right;
  static const glm::vec3 left;
  static const glm::vec3 forward;
  static const glm::vec3 back;

  Snake(Food &food);
  ~Snake() = default;

  std::vector<glm::vec3> render();
  void update();
  void turn(Arrow arrow);
  void move();
  bool isNextMovable();
  bool isColliding(const glm::vec3 &pos);

private:
  Food &food;
  std::vector<glm::vec3> segments;
  std::chrono::milliseconds timeMove;
  glm::vec3 direction = Snake::forward;
};

#endif
