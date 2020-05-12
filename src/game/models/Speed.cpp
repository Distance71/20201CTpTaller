#include "Speed.h"

Speed::Speed(int x, int y) {
    this->x = x;
    this->y = y;
}

int Speed::getXSpeed(){
    return this->x;
}

int Speed::getYSpeed(){
    return this->y;
}

void Speed::setXSpeed(int x){
    this->x = x;
}

void Speed::setYSpeed(int y){
    this->y = y;
}