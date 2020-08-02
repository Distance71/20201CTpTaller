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

    cout << "El valor x " << this->x_ << " El otro " << otherX << endl;
    cout << "El valor y " << this->y_ << " El otro " << otherY << endl;

	bool result = ((this->x_ + this->width_) < otherX || 
                    (otherX + other->getWidth()) < this->x_ || 
                    (this->y_ + this->height_) < otherY || 
                    (otherY + other->getHeight()) < this->y_);
	return !result;
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