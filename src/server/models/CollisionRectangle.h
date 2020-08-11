#ifndef COLLISION_RECTANGLE_H_
#define COLLISION_RECTANGLE_H_

using namespace std;
#include <iostream>

class CollisionRectangle {

private:
	int Xstart_;
	int Xend_;
	int Ystart_;
	int Yend_;

public:
	CollisionRectangle(int Xstart, int Ystart, int Xend, int Yend);
	void setOffset(int x, int y);
	bool isCollision(CollisionRectangle* other);
	bool isCollisionWithBoss(CollisionRectangle* other);
	int getXstart();
	int getYstart();
	int getXend();
	int getYend();
};

#endif