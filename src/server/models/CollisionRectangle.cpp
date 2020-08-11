#include "CollisionRectangle.h"

CollisionRectangle::CollisionRectangle(int Xstart, int Ystart, int Xend, int Yend) {
	this->Xstart_ = Xstart;
	this->Xend_ = Xend;
	this->Ystart_ = Ystart;
	this->Yend_ = Yend;
}

bool CollisionRectangle::isCollision(CollisionRectangle* other) {
	if ( (this->Xstart_ >= other->getXstart() && this->Xstart_<= other->getXend() )|| (this->Xend_ >= other->getXstart() && this->Xend_ <= other->getXend())){
		if ((other->getYstart() >= this->Ystart_ && other->getYstart() <=this->Yend_ )||(other->getYend() >= this->Ystart_ && other->getYend()  <=this->Yend_)){
			return true;
		}
	}
	
	return false;
}

bool CollisionRectangle::isCollisionWithBoss(CollisionRectangle* other){

	if ( (this->Xstart_ >= other->getXstart() && this->Xstart_<= other->getXend() )|| (this->Xend_ >= other->getXstart() && this->Xend_ <= other->getXend())){

		if (other->getYstart() <= this->Ystart_ && other->getYend() >= this->Ystart_)
			return true;

		if ((other->getYstart() >= this->Ystart_ && other->getYstart() <=this->Yend_ )||(other->getYend() >= this->Ystart_ && other->getYend()  <=this->Yend_)){
			return true;
		}
	}
	
	return false;
}

int CollisionRectangle::getXstart() {
	return this->Xstart_;
}


int CollisionRectangle::getYstart() {
	return 	this->Ystart_;
}

int CollisionRectangle::getXend(){
	return this->Xend_;
}

int CollisionRectangle::getYend() {
	return this->Yend_;
}