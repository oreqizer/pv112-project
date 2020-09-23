#ifndef SETTINGS_H
#define SETTINGS_H

#define SIZE 24
#define FRAMERATE 165
#define WIDTH 1280
#define HEIGHT 720

enum class Arrow {
  Top,
  Bottom,
  Right,
  Left,
  Forward,
  Back,
};

enum class State {
  Game,
  Score,
  Menu,
};

enum class Speed {
  Slow = 10,
  Medium = 50,
};

enum class SpeedMs {
  Slow = 500,
  Medium = 250,
  Fast = 125,
};

#endif
