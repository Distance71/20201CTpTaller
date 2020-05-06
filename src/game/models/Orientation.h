#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

#include "State.h"

// Se encarga del manejo interno del state de posicion

enum orientation_t {FRONT, BACK, UP, DOWN, FRONT_UP, FRONT_DOWN, BACK_DOWN, BACK_UP};

class Orientation: State {
    orientation_t orientation_;

    public:
    Orientation();
    orientation_t getOrientation();
    //~Orientation();
};

#endif
