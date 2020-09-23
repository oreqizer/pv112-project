#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Time {
public:
  static void init();
  static void update();

  static std::chrono::milliseconds time;
  static std::chrono::milliseconds timeDelta;
  static std::chrono::milliseconds timeTotal;
};
