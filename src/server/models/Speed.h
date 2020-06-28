#ifndef _SPEED_H_
#define _SPEED_H_

#include "../../common/models/State.h"

class Speed: public State {

    public:
    Speed(int x_,int y_);
    int getX()override;
    int getY()override;
    void setX(int x_)override;
    void setY(int y_)override;
};

#endif
