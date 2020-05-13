#include "Position.h"


Position::Position(int x, int y):State(x,y) {
}

int Position::getX(){
    return x;
}

int Position::getY(){
    return y;
}

void Position::setX(int x_){
    x = x_;
}

void Position::setY(int y_){
    y = y_;
}