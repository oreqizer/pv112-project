#include "camera.hpp"

#include <GLFW/glfw3.h>

const float Camera::elevationMin = -1.5f;
const float Camera::elevationMax = 1.5f;
const float Camera::angleSensitivity = 0.008f;

Camera::Camera() : angleDirection(0.0f), angleElevation(0.0f), distance(5.0f), xLast(0), yLast(0) {
  updateEyePosition();
}

void Camera::setDistance(float value) {
  distance = value;

  updateEyePosition();
}

void Camera::setEyeOffset(glm::vec3 value) {
  eyeOffset = value;

  updateEyePosition();
}

glm::vec3 Camera::getEyePosition() const {
  return eyePosition;
}

void Camera::updateEyePosition() {
  eyePosition.x = eyeOffset.x + distance * cosf(angleElevation) * -sinf(angleDirection);
  eyePosition.y = eyeOffset.y + distance * sinf(angleElevation);
  eyePosition.z = eyeOffset.z + distance * cosf(angleElevation) * cosf(angleDirection);
}

void Camera::onMouseMove(double x, double y) {
  float dx = float(x - xLast);
  float dy = float(y - yLast);
  xLast = static_cast<int>(x);
  yLast = static_cast<int>(y);

  angleDirection += dx * angleSensitivity;
  angleElevation += dy * angleSensitivity;

  // Clamp the results
  if (angleElevation > elevationMax) {
    angleElevation = elevationMax;
  }
  if (angleElevation < elevationMin) {
    angleElevation = elevationMin;
  }
  
  updateEyePosition();
}

