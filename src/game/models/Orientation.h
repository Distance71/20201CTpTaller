#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_

#include "State.h"
#include "../types.h"

// Se encarga del manejo interno del state de posicion

class Orientation: public State {
    
    public:
        Orientation(int x, int y);
        int getX()override;
        void setX(int x_)override;
        //~Orientation();
};

#endif
