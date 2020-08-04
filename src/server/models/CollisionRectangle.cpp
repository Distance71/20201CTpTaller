#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle(int x, int y, int width, int height) {
	this->x_ = x;
	this->y_ = y;
	this->width_ = width;
	this->height_ = height;
}

bool CollisionRectangle::isCollision(CollisionRectangle* other) {
	int otherX = other->getX();
	int otherY = other->getY();
	if (this->x_ >= otherX && this->x_ <= (otherX + other->getWidth())){ //|| (this->x_ + this->width_ >= otherX && this->x_ + this->width_ <= otherX + other->getWidth())){
		if ( (otherY >= this->y_ && otherY <= this->y_ + this->height_ ) || ( otherY + other->getHeight() >= this->y_  && otherY + other->getHeight()  <= this->y_ + this->height_)){
			return true;
		}
	}
	
	return false;
}


int CollisionRectangle::getX() {
	return this->x_;
}

void CollisionRectangle::setX(int x){
    this->x_ = x;
}

void CollisionRectangle::setY(int y){
    this->y_ = y;
}

int CollisionRectangle::getY() {
	return this->y_;
}

int CollisionRectangle::getWidth() {
	return this->width_;
}

int CollisionRectangle::getHeight() {
	return this->height_;
}