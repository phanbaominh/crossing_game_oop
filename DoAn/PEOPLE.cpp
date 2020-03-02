#include "PEOPLE.h"


CPEOPLE::CPEOPLE()
{
	mX = 0;
	mY = 0;
}
void CPEOPLE::Up(int v){

	mY -= v;
}
void CPEOPLE::Left(int v){

	mX -= v;
}
void CPEOPLE::Right(int v){
	mX += v;
}
void CPEOPLE::Down(int v){
	mY =mY+ v;
}
int CPEOPLE::getX(){
	return mX;
}
int CPEOPLE::getY(){
	return mY;
}
bool CPEOPLE::isImpact(COBSTACLE**a){
	for (int i = 0; i < COBSTACLE::SYMBOL_PER_LANE; i++)
	{
		if (a[i]->getY() == mY &&  mX >= a[i]->getX() && mX <= a[i]->getX() + a[i]->getSymbol().length())
		{
			LIFE--;
			return true;
		}
	}
	return false;
}
bool CPEOPLE::isFinish(){
	if (mY==0)
		return true;
	return false;
}
bool CPEOPLE::isDead(){
	if (LIFE <= 0)
		return true;
	else
		return false;
}


