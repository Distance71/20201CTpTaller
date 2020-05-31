#include "Speed.h"

Speed::Speed(int x_, int y_):State(x_,y_) {

}

int Speed::getX(){
    return x;
}

int Speed::getY(){
    return y;
}

void Speed::setX(int x_){
    x = x_;
}

void Speed::setY(int y_){
    y = y_;
}