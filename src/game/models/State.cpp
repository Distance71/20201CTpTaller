#include "State.h"

State::State(int x_, int y_){
    x = x_;
    y = y_;
}

int State::getX(){
    return x;
}
int State::getY(){
    return y;
}
void State::setX(int x_){
    x=x_;
}
void State:: setY(int y_){
    y=y_;
}
//State::~State();
