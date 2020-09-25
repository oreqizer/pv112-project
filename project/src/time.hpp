#pragma once
#ifndef TIME_H
#define TIME_H

#include <chrono>

class Time {
public:
  static void init();
  static void update();

  static std::chrono::milliseconds time;
  static std::chrono::milliseconds timeDelta;
  static std::chrono::milliseconds timeTotal;
};

#endif
