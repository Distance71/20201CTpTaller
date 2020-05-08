#ifndef _SPEED_H_
#define _SPEED_H_

#include "State.h"

class Speed: virtual State {
    private:
    int x, y;

    public:
    Speed();
    Speed(int x, int y);
    int getXSpeed();
    int getYSpeed();
    void setXSpeed(int x);
    void setYSpeed(int y);
};

#endif
