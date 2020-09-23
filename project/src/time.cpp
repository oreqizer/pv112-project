#include "time.hpp"

void Time::init() {
  Time::time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Time::update() {
  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

  Time::timeDelta = now - Time::time;
  Time::timeTotal += Time::timeDelta;
  Time::time = now;
}
