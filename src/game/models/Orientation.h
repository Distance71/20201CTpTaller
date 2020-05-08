#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

#include "State.h"
#include "../types.h"

// Se encarga del manejo interno del state de posicion

class Orientation: virtual State {
    orientation_t orientation_;

    public:
    Orientation();
    orientation_t getOrientation();
    //~Orientation();
};

#endif
