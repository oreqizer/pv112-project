#include "time.hpp"

std::chrono::milliseconds Time::time = std::chrono::milliseconds(0);
std::chrono::milliseconds Time::timeDelta = std::chrono::milliseconds(0);
std::chrono::milliseconds Time::timeTotal = std::chrono::milliseconds(0);

void Time::init() {
  Time::time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Time::update() {
  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

  Time::timeDelta = now - Time::time;
  Time::timeTotal += Time::timeDelta;
  Time::time = now;
}
