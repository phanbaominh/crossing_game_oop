#pragma once
#include "CONSOLE.h"
#include <iostream>
#include <string>
using namespace std;

class COBSTACLE
{
protected:
	int mX, mY;
	string mSymbol;
public:
	static int SYMBOL_PER_LANE;
	void Move(int x, int y){
		mX += x;
		mY += y;
	}
	COBSTACLE(){
		mX = 0;
		mY = 0;
	}
	int getX(){ return mX; }
	int getY(){ return mY; }
	void setX(int v){ mX = v; }
	void setY(int v){ mY = v; }
	string getSymbol(){ return mSymbol; }
	void setSymbol(string s){ mSymbol = s; }
};

