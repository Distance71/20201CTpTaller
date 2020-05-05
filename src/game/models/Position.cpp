#include "Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getXPosition(){
    return this->x;
}

int Position::getYPosition(){
    return this->y;
}

void Position::setXPosition(int x){
    this->x = x;
}

void Position::setYPosition(int y){
    this->y = y;
}