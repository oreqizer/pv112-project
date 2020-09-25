#include <vector>

#include <glm/glm.hpp>

#include "settings.hpp"
#include "time.hpp"

#include "snake.hpp"

const glm::vec3 Snake::top = glm::vec3(0, 1, 0);
const glm::vec3 Snake::bottom = glm::vec3(0, -1, 0);
const glm::vec3 Snake::right = glm::vec3(1, 0, 0);
const glm::vec3 Snake::left = glm::vec3(-1, 0, 0);
const glm::vec3 Snake::forward = glm::vec3(0, 0, 1);
const glm::vec3 Snake::back = glm::vec3(0, 0, -1);

Snake::Snake(Food &food) : food(food), segments(std::vector<glm::vec3>()), moveTimer(std::chrono::milliseconds(0)) {
  auto initial = glm::vec3(settings::size / 2, settings::size / 2, settings::size / 2);

  segments.push_back(initial - direction);
  segments.push_back(initial);

  food.generate(segments);
};

std::vector<glm::vec3> Snake::render() { return segments; }

void Snake::update() {
  moveTimer += Time::timeDelta;
  if (segments.size() <= settings::speed::slow) {
    if (moveTimer.count() > settings::speedMs::slow) {
      move();
    }
    return;
  }
  
  if (segments.size() <= settings::speed::medium) {
    if (moveTimer.count() > settings::speedMs::medium) {
      move();
    }
    return;
  }

  if (moveTimer.count() > settings::speedMs::fast) {
    move();
  }
}

void Snake::turn(Arrow arrow) {
  if (movePending) {
    return;
  }

  switch (arrow) {
  case Arrow::Top:
    if (direction != Snake::bottom) {
      direction = Snake::top;
    }
    break;
  case Arrow::Bottom:
    if (direction != Snake::top) {
      direction = Snake::bottom;
    }
    break;
  case Arrow::Right:
    if (direction != Snake::left) {
      direction = Snake::right;
    }
    break;
  case Arrow::Left:
    if (direction != Snake::right) {
      direction = Snake::left;
    }
    break;
  case Arrow::Forward:
    if (direction != Snake::back) {
      direction = Snake::forward;
    }
    break;
  case Arrow::Back:
    if (direction != Snake::forward) {
      direction = Snake::back;
    }
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

  movePending = false;
  moveTimer = std::chrono::milliseconds(0);
}

bool Snake::isCrashed() {
  if (segments.size() <= settings::speed::slow) {
    if (moveTimer.count() > settings::speedMs::slow) {
      return !isNextMovable();
    }
  }
  
  if (segments.size() <= settings::speed::medium) {
    if (moveTimer.count() > settings::speedMs::medium) {
      return !isNextMovable();
    }
  }

  if (moveTimer.count() > settings::speedMs::fast) {
    return !isNextMovable();
  }

  return false;
}

bool Snake::isNextMovable() {
  auto next = segments.back() + direction;

  // Map OOB
  if (next.x < 0 || next.y < 0 || next.z < 0 || next.x > settings::size || next.y > settings::size || next.z > settings::size) {
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
