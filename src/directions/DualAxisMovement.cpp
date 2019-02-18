#include "directions/DualAxisMovement.h"
#include "directions/PanDirections.h"
#include "directions/PitchDirections.h"

DualAxisMovement::DualAxisMovement(int panMovement, int pitchMovement) {

    const bool isValidPanMovement = panMovement < 0 || panMovement > (int) PanDirections::MAX; 
    const bool isValidPitchMovement = pitchMovement < 0 || pitchMovement > (int) PitchDirections::MAX; 

    // If not provided with proper movement, set it to NO_MOVEMENT
    // Maybe later make it throw Exception?

    _panMovement = panMovement;
    _pitchMovement = pitchMovement;

    if (!isValidPanMovement) {
        panMovement = (int) PanDirections::NO_MOVEMENT;
    }

    if (!isValidPitchMovement) {
        pitchMovement = (int) PitchDirections::NO_MOVEMENT;
    }
}

int DualAxisMovement::getPanMovement() {
    return _panMovement;
}

int DualAxisMovement::getPitchMovement() {
    return _pitchMovement;
}