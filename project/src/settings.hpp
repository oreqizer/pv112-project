#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

enum class Settings : int {
  Size = 24,
};

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

enum class Speed : int {
  Slow = 10,
  Medium = 50,
};

enum class SpeedMs : int {
  Slow = 500,
  Medium = 250,
  Fast = 125,
};

#endif
