#define SIZE 24
#define FRAMERATE 165
#define WIDTH 1280
#define HEIGHT 720

namespace settings {
    enum Arrow {
        Top,
        Bottom,
        Right,
        Left,
        Forward,
        Back,
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
}
