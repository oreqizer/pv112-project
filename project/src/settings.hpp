#define SIZE 32
#define FRAMERATE 165
#define WIDTH 1280
#define HEIGHT 720

enum Arrow {
    Up,
    Down,
    Left,
    Right,
    SpinLeft,
    SpinRight,
};

enum State {
    Game,
    Score,
    Menu,
};

enum Speed {
    Slow = 10,
    Medium = 50,
};

enum SpeedMs {
    Slow = 500,
    Medium = 250,
    Fast = 125,
};
