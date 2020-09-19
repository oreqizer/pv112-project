#include <vector>

#include "settings.hpp"
#include "time.hpp"

#include "snake.hpp"

Snake::Snake(Food& food) : food(food), segments(std::vector<glm::vec3>()), timeMove(std::chrono::milliseconds(0)) {
    segments.push_back(glm::vec3(SIZE / 2, SIZE / 2, SIZE / 2));

    food.generate(segments);
};

void Snake::render() {
    //
}

void Snake::update() {
    timeMove += Time::timeDelta;
    if (segments.size() <= Speed::Slow && timeMove.count() > SpeedMs::Slow) {
        move();
    }
    if (segments.size() <= Speed::Medium && timeMove.count() > SpeedMs::Medium) {
        move();
    }
    if (timeMove.count() > SpeedMs::Fast) {
        move();
    }
}

void Snake::turn(Arrow arrow) {
    //
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
    if (next.x < 0 || next.y < 0 || next.z < 0 || next.x > 32 || next.y > 32 || next.z > 32) {
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
