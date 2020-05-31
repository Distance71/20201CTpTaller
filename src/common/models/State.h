#ifndef _STATE_H_
#define _STATE_H_

#include "../types.h"
// Se encarga del manejo interno del state de posicion

class State {

    protected:
    int x;
    int y;

    public:
    State(int x_, int y_);
    virtual int getX();
    virtual int getY();
    virtual void setX(int x_);
    virtual void setY(int y_);
    ~State();
};

#endif
