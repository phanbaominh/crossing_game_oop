#pragma once

#include "ANIMAL.h"
#include "VEHICLE.h"
class CPEOPLE
{
private:
	int mX, mY;
	bool mState;
public:
	static int LIFE;
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	int getX();
	int getY();
	void setX(int v){ mX = v; }
	void setY(int v){ mY = v; }
	bool isImpact(COBSTACLE**);
	//bool isImpact(CANIMAL**);
	bool isFinish();
	bool isDead();
};

