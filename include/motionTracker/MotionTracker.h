#ifndef MOTIONTRACKER_H
#define MOTIONTRACKER_H

#include "coordinates/FieldOfViewSectors.h"
#include "directions/DualAxisMovement.cpp"

using namespace std;

/**
 * Class which given a region in the Field of View, decides which
 * motion needs to be assigned to an arbitrary X-Y mechanism, to 
 * displace its center towards that region
 **/

class MotionTracker {
  public:
    MotionTracker(bool);
    bool isEnabled();
    void toggleTracker();
    DualAxisMovement getRequiredMovement(int);

  private:
    bool _enabled;
};

#endif