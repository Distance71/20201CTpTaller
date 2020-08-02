#ifndef COLLISION_RECTANGLE_H_
#define COLLISION_RECTANGLE_H_

using namespace std;

class CollisionRectangle {

private:
	int x_;
	int y_;
	int width_;
	int height_;

public:
	CollisionRectangle(int x, int y, int width, int height);
	void setOffset(int x, int y);
	bool isCollision(CollisionRectangle* other);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};

#endif