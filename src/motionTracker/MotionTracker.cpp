#include <iostream>
#include "motionTracker/MotionTracker.h"
#include "directions/PanDirections.h"
#include "directions/PitchDirections.h"

bool MotionTracker::isEnabled() {
  return _enabled;
}

void MotionTracker::toggleTracker() {
  _enabled = !_enabled;
}

MotionTracker::MotionTracker(bool trackingEnabled) {
  _enabled = trackingEnabled;
}

DualAxisMovement MotionTracker::getRequiredMovement(int sector) {

  DualAxisMovement dam = DualAxisMovement((int) PanDirections::NO_MOVEMENT, (int) PitchDirections::NO_MOVEMENT);
  // Maybe throw exception here
  if (!_enabled) return dam;

  switch(sector) {
    case (int) FieldOfViewSectors::UPPER_LEFT:
      dam = DualAxisMovement((int) PanDirections::LEFT, (int) PitchDirections::UP);
      break;
    case (int) FieldOfViewSectors::UPPER_CENTER:
      dam = DualAxisMovement((int) PanDirections::NO_MOVEMENT, (int) PitchDirections::UP);
      break;
    case (int) FieldOfViewSectors::UPPER_RIGHT:
      dam = DualAxisMovement((int) PanDirections::RIGHT, (int) PitchDirections::UP);
      break;
    case (int) FieldOfViewSectors::CENTER_LEFT:
      dam = DualAxisMovement((int) PanDirections::LEFT, (int) PitchDirections::NO_MOVEMENT);
      break;
    case (int) FieldOfViewSectors::CENTER_CENTER:
      dam = DualAxisMovement((int) PanDirections::NO_MOVEMENT, (int) PitchDirections::NO_MOVEMENT);
      break;
    case (int) FieldOfViewSectors::CENTER_RIGHT:
      dam = DualAxisMovement((int) PanDirections::RIGHT, (int) PitchDirections::NO_MOVEMENT);
      break;
    case (int) FieldOfViewSectors::BOTTOM_LEFT:
      dam = DualAxisMovement((int) PanDirections::LEFT, (int) PitchDirections::DOWN);
      break;
    case (int) FieldOfViewSectors::BOTTOM_CENTER:
      dam = DualAxisMovement((int) PanDirections::NO_MOVEMENT, (int) PitchDirections::DOWN);
      break;
    case (int) FieldOfViewSectors::BOTTOM_RIGHT:
      dam = DualAxisMovement((int) PanDirections::RIGHT, (int) PitchDirections::DOWN);
      break;
    default:
      break;
  }
  return dam;
}