#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

namespace settings {
  const int size = 24;

  namespace speed {
    const int slow = 10;
    const int medium = 50;
  }

  namespace speedMs {
    const int slow = 500;
    const int medium = 250;
    const int fast = 125;
  }
}

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

#endif
