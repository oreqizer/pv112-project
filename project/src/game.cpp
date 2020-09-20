#include "time.hpp"

#include "game.hpp"

Game::Game() {
    Time::init();

    food = new Food();
    snake = new Snake(*food);
    world = new World();
}

void Game::update() {
    Time::update();

    snake->update();
}
