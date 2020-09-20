#include "food.hpp"
#include "snake.hpp"
#include "world.hpp"

class Game {
public:
    Game();
    ~Game() = default;

    void update();

    Food *food;
    Snake *snake;
    World *world;
};
