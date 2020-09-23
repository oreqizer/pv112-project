#include <vector>

#include "settings.hpp"
#include "time.hpp"

#include "snake.hpp"

const glm::vec3 Snake::top = glm::vec3(0, 1, 0);
const glm::vec3 Snake::bottom = glm::vec3(0, -1, 0);
const glm::vec3 Snake::right = glm::vec3(1, 0, 0);
const glm::vec3 Snake::left = glm::vec3(-1, 0, 0);
const glm::vec3 Snake::forward = glm::vec3(0, 0, 1);
const glm::vec3 Snake::back = glm::vec3(0, 0, -1);

Snake::Snake(Food &food) : food(food), segments(std::vector<glm::vec3>()), timeMove(std::chrono::milliseconds(0)) {
  segments.push_back(glm::vec3(SIZE / 2, SIZE / 2, SIZE / 2));

  food.generate(segments);
};

std::vector<glm::vec3> Snake::render() { return segments; }

void Snake::update() {
  timeMove += Time::timeDelta;
  if (segments.size() <= static_cast<int>(Speed::Slow) && timeMove.count() > static_cast<int>(SpeedMs::Slow)) {
    move();
  }
  if (segments.size() <= static_cast<int>(Speed::Medium) && timeMove.count() > static_cast<int>(SpeedMs::Medium)) {
    move();
  }
  if (timeMove.count() > static_cast<int>(SpeedMs::Fast)) {
    move();
  }
}

void Snake::turn(Arrow arrow) {
  switch (arrow) {
  case Arrow::Top:
    direction = Snake::top;
    break;
  case Arrow::Bottom:
    direction = Snake::bottom;
    break;
  case Arrow::Right:
    direction = Snake::right;
    break;
  case Arrow::Left:
    direction = Snake::left;
    break;
  case Arrow::Forward:
    direction = Snake::forward;
    break;
  case Arrow::Back:
    direction = Snake::back;
    break;
  }
}

void Snake::move() {
  auto next = segments.back() + direction;

  segments.push_back(next);
  if (!isColliding(food.position)) {
    segments.erase(segments.begin());
  } else {
    food.generate(segments);
  }
  timeMove = std::chrono::milliseconds(0);
}

bool Snake::isNextMovable() {
  auto next = segments.back() + direction;

  // Map OOB
  if (next.x < 0 || next.y < 0 || next.z < 0 || next.x > SIZE || next.y > SIZE || next.z > SIZE) {
    return false;
  }

  // Self-collision
  return !isColliding(next);
}

bool Snake::isColliding(const glm::vec3 &pos) {
  for (auto s : segments) {
    if (s == pos) {
      return true;
    }
  }

  return false;
}
