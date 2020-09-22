#pragma once

#include <glm/glm.hpp>

/// This is a VERY SIMPLE class that allows to very simply move with the camera.
/// It is not a perfect, brilliant, smart, or whatever implementation of a camera,
/// but it is sufficient for PV112 lectures.
///
/// Use left mouse button to change the point of view.
/// Use right mouse button to zoom in and zoom out.
class Camera {
public:
  Camera();
  ~Camera() = default;

  /// Call when the user moves with the mouse cursor (see glfwSetCursorPosCallback)
  void onMouseMove(double x, double y);

  /// Sets distance
  void setDistance(float value);
  /// Sets eye offset
  void setEyeOffset(glm::vec3 value);
  /// Returns the position of the eye in world space coordinates
  glm::vec3 getEyePosition() const;

private:
  /// Constants that defines the behaviour of the camera
  ///		- Minimum elevation in radians
  static const float elevationMin;
  ///		- Maximum elevation in radians
  static const float elevationMax;
  ///		- Sensitivity of the mouse when changing elevation or direction angles
  static const float angleSensitivity;

  /// angleDirection is an angle in which determines into which direction in xz plane I look.
  ///		- 0 degrees .. I look in -z direction
  ///		- 90 degrees .. I look in -x direction
  ///		- 180 degrees .. I look in +z direction
  ///		- 270 degrees .. I look in +x direction
  float angleDirection;

  /// angleDirection is an angle in which determines from which "height" I look.
  ///		- positive elevation .. I look from above the xz plane
  ///		- negative elevation .. I look from below the xz plane
  float angleElevation;

  /// Distance from (0,0,0), the point at which I look
  float distance;

  /// Final position of the eye in world space coordinates, for LookAt or shaders
  glm::vec3 eyePosition;
  /// Eye offset for correctly calculating angles around a point
  glm::vec3 eyeOffset;

  /// Last X and Y coordinates of the mouse cursor
  int xLast, yLast;

  /// Recomputes 'eyePosition' from 'angleDirection', 'angleElevation'
  void updateEyePosition();
};
