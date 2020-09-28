#include "time.hpp"

#include "game.hpp"

const glm::vec3 Game::center = glm::vec3(settings::size / 2);

Game::Game() {
  Time::init();

  food = new Food();
  snake = new Snake(*food);
  world = new World();
  gui = new Gui();
}

void Game::update() {
  Time::update();

  if (snake->isCrashed()) {
    if (state == GameState::Playing) {
      Audio::play(Audio::crash);
    }

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
  delete(gui);
}
