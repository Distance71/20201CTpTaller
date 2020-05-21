#include "Orientation.h"

//Orientation::~Orientation();

Orientation::Orientation(int x, int y):State(x,y){
    
}

int Orientation::getX(){
    return this->x;
}

void Orientation::setX(int x_){
    this->x = x_;
}