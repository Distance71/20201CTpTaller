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

	bool result = ((this->x_ + this->width_) < otherX || 
                    (otherX + other->getWidth()) < this->x_ || 
                    (this->y_ + this->height_) < otherY || 
                    (otherY + other->getHeight()) < this->y_);
	return !result;
}

int CollisionRectangle::getX() {
	return this->x_;
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