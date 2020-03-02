#pragma once
#include <thread>
#include <string>
#include "ANIMAL.h"
#include "PEOPLE.h"
#include "VEHICLE.h"
class CGAME
{
	
	int LANE_COUNT=4;
	int LANE_HEIGHT;
	int LIFE_COUNT = 4;
	const int DEFAULT = 4;
	int MAX_X;
	int MAX_Y;
	//int SYMBOL_PER_LANE = 4;
	int MARGIN;
	string TRUCK_SYMBOL = "ooD";
	string CAR_SYMBOL = "o[]o";
	string BIRD_SYMBOL = "B";
	string DINO_SYMBOL = "D";
	
	COBSTACLE **at,**ac,**ad,**ab;
	CPEOPLE *pp;
public:
	static int MAX_LEVEL;
	static string HUMAN_SYMBOL;
	static bool MUSIC;
	static bool SOUND;
	static int SPEED;
	static bool LIGHT_CAR;
	static bool LIGHT_TRUCK;
	static int TIME_C;
	static int TIME_T;
	static int LEVEL_COUNT;
	void drawGame(CCONSOLE cs, bool p, HANDLE out, HANDLE buff);
	void resetGame();
	void startGame();
	CPEOPLE* getPeople(){ return pp; };
	COBSTACLE** getTruck(){ return at; };
	COBSTACLE** getBird(){ return ab; };
	COBSTACLE** getDino(){ return ad; };
	COBSTACLE** getCar(){ return ac; };
	void checkLight(int&,int&,bool);
	void loadGame();
	bool saveGame();
	void pauseGame(HANDLE);
	void resumeGame(HANDLE);
	void updatePosPeople(char);
	void updatePosVehicle(bool,bool);
	void updatePosAnimal();
	void updateLevel();
	void enterSetting();
	void printInfo();
	CGAME(CCONSOLE);
	~CGAME();
};

