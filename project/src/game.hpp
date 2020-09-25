#pragma once
#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

#include "food.hpp"
#include "snake.hpp"
#include "world.hpp"

enum class GameState {
  Playing,
  Crashed,
};

class Game {
public:
  static const glm::vec3 center;

  Game();
  ~Game() = default;

  void update();

  Food *food;
  Snake *snake;
  World *world;

private:
  GameState state = GameState::Playing;
};

#endif
