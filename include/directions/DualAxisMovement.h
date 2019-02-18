#ifndef DUALAXISMOVEMENT_H
#define DUALAXISMOVEMENT_h

class DualAxisMovement {
    public:
        DualAxisMovement(int, int);
        int getPanMovement();
        int getPitchMovement();
    
    private:
        int _panMovement;
        int _pitchMovement;
};

#endif