#pragma once
#include "OBSTACLE.h"
class CANIMAL :public COBSTACLE
{
public:
	CANIMAL();
	virtual void Tell()=0;

};
class CDINOSAUR: public CANIMAL
{
public:
	void Tell(){
		cout << "Rawwrr!" << endl;
	}
};
class CBIRD : public CANIMAL
{
public:
	void Tell(){
		cout << "Chirp!" << endl;
	}
};


