#ifndef _SPEED_H_
#define _SPEED_H_

#include "State.h"

class Speed: virtual State {

    public:
    Speed(int x_,int y_);
    int getX()override;
    int getY()override;
    void setX(int x_)override;
    void setY(int y_)override;
};

#endif
