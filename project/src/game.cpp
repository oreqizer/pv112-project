#include "time.hpp"

#include "game.hpp"

const glm::vec3 Game::center = glm::vec3(settings::size / 2);

Game::Game() {
  Time::init();

  audio = new Audio();
  food = new Food();
  snake = new Snake(*food);
  world = new World();

  // Test
  // audio->play("../sound/crunch.mp3");
}

void Game::update() {
  Time::update();

  if (snake->isCrashed()) {
    state = GameState::Crashed;
  }

  if (state == GameState::Playing) {
    snake->update();
  }
}

Game::~Game() {
  delete(snake);
  delete(food);
  delete(world);
  delete(audio);
}
