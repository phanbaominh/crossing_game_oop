#include "GAME.h"
#include <iostream>
using namespace std;
char MOVING;
bool IS_RUNNING = true;
bool PAUSE = true;
bool PAUSE2 = false;
bool WIN = false;
bool LOSE = false;
int COBSTACLE::SYMBOL_PER_LANE = 4;
int CPEOPLE::LIFE = 1;
bool CGAME::LIGHT_CAR = false;
bool CGAME::LIGHT_TRUCK = false;
int CGAME::TIME_C = 0;
int CGAME::TIME_T = 50;
int CGAME::LEVEL_COUNT = 1;
bool CGAME::MUSIC=true;
bool CGAME::SOUND = true;
int CGAME::SPEED = 100;
int CGAME::MAX_LEVEL = 2;
string CGAME::HUMAN_SYMBOL = "Y";
string CCONSOLE::mitem[10];
CCONSOLE cs;
CGAME *cg=new CGAME(cs);
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hNewScreenBuffer = CreateConsoleScreenBuffer(
	GENERIC_READ |           // read/write access 
	GENERIC_WRITE,
	FILE_SHARE_READ |
	FILE_SHARE_WRITE,        // shared 
	NULL,                    // default security attributes 
	CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
	NULL);
void exitGame(thread *t){
	system("cls");
	IS_RUNNING = false;

	t->join();

}

void ThreadFunc1(){
	while (IS_RUNNING){
		if (!PAUSE){
			SetConsoleActiveScreenBuffer(hNewScreenBuffer);
			if (!cg->getPeople()->isDead())
			{
				cg->updatePosPeople(MOVING);
			}
			MOVING = ' ';
			cg->updatePosAnimal();
			cg->updatePosVehicle(CGAME::LIGHT_TRUCK, CGAME::LIGHT_CAR);
			CGAME::TIME_C++;
			CGAME::TIME_T++;
			cg->drawGame(cs, PAUSE, hStdout, hNewScreenBuffer);
			cg->checkLight(CGAME::TIME_T, CGAME::TIME_C,false);
			
			if (cg->getPeople()->isImpact(cg->getBird()) || cg->getPeople()->isImpact(cg->getDino()) || cg->getPeople()->isImpact(cg->getTruck()) || cg->getPeople()->isImpact(cg->getCar()))
			{
				if (CPEOPLE::LIFE > 0)
				{
					if (CGAME::SOUND)
						PlaySound(TEXT("collide.wav"), NULL, SND_FILENAME | SND_ASYNC);
					SetConsoleActiveScreenBuffer(hStdout);
					CCONSOLE::GoToXY(cg->getPeople()->getX(), cg->getPeople()->getY());
					cout << " ";
					cg->getPeople()->Down(1);
					
					for (int i = 0; i < 6; i++){
						if (i % 2 == 0)
							CCONSOLE::textcolor(15);
						else
							CCONSOLE::textcolor(0);
						CCONSOLE::GoToXY(cg->getPeople()->getX(), cg->getPeople()->getY());
						cout << CGAME::HUMAN_SYMBOL;
						Sleep(200);
					}
					cg->getPeople()->setX(cs.getMaxX() / 2);
					cg->getPeople()->setY(cs.getMaxY());
				}

			}
			if (cg->getPeople()->isFinish())
			{
				
				if (CGAME::SOUND)
					PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
				system("cls");
				if (CGAME::LEVEL_COUNT == CGAME::MAX_LEVEL)
				{
					
					WIN = true;
					PAUSE = true;

					
				}
				if (!WIN)
				{
					SetConsoleActiveScreenBuffer(hStdout);
					cg->updateLevel();

					CGAME::TIME_C = 0; CGAME::TIME_T = 50;
					CGAME::LIGHT_CAR = false;
					CGAME::LIGHT_TRUCK = false;
					cg->startGame();
				}

			}
			if (cg->getPeople()->isDead())
			{
				PAUSE = true;
				if (CGAME::SOUND)
					PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
				system("cls");
				Sleep(50);
				CCONSOLE::GoToXY((cs.getMaxX() / 2)-10, cs.getMaxY() / 2);
				CCONSOLE::textcolor(12);
				SetConsoleActiveScreenBuffer(hStdout);
				cout << "YOU LOSE!!";
				CCONSOLE::textcolor(10);
				CCONSOLE::GoToXY((cs.getMaxX() / 2) - 10, (cs.getMaxY() / 2) + 1);
				cout << "DO YOU WANT TO CONTINUE?(Y/N): ";
				char t;
				while (1){
					cin >> t;
					if (t == 'Y')
					{
						PAUSE = false;
						cg->resetGame();
						system("cls");
						CCONSOLE::textcolor(15);
						cg->startGame();
						break;
					}
					else if (t == 'N')
					{
						CCONSOLE::GoToXY((cs.getMaxX() / 2) - 10, (cs.getMaxY() / 2) + 2);
						cout << ("PRESS ANY BUTTON TO CONTINUE");
						CCONSOLE::textcolor(15);
						
						LOSE = true;
						break;
					}
				}
				if (!WIN) Sleep(200);
				CCONSOLE::textcolor(15);
			}
		}
		else
		{
			if (PAUSE2)
			{
				

					CCONSOLE::GoToXY(cs.getMaxX() / 2, cs.getMaxY() / 2);
					
					CCONSOLE::textcolor(10);
					SetConsoleActiveScreenBuffer(hStdout);
					cout << "PAUSE!";
					cg->drawGame(cs, PAUSE, hStdout, hNewScreenBuffer);
					PAUSE2 = false;

				
			}
		}
	}
}
void main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int x;
	int line = 6;
	bool load = false;
	bool quit = false;
	int number = 4;
	thread t1(ThreadFunc1);
	CCONSOLE::printNameTable("CROSS THE ROAD");
	CCONSOLE::printMenu(0,4);
	CCONSOLE::GoToXY(20, line);
	cout << (char)32; 
	bool qg = false;
	while (!quit) {

		if (_kbhit()) {

			x = CCONSOLE::move();

			CCONSOLE::GoToXY(20, line);
			cout << " "; 

			switch (x) {

			case 1:

			case 3:
			{
					  line++;
					  if (line >= number+6) line = 6;
					  break;

			}

			case 2:

			case 4:
			{
					  line--;
					  if (line < 6) line = number - 1+ 6;
					  break;
			}

			case 5:
			{

					  switch (line){
					  case 6: 
					  {
								  system("cls");
								  Sleep(20);
								  cg->startGame();
								  if (!load)
								  {
									  cg->resetGame();
								  }
								  else 
									load = false;
								  PAUSE = false;
								  LOSE = false;
								  qg = false;
								  
								 // if (CGAME::SOUND)
									//  PlaySound(TEXT("theme.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);
								  while (!qg){
									 
									  if (cg->getPeople()->isDead() && LOSE)
									  {
										  qg = true;
										 
										  break;

									  }

									  if (WIN)
									  {
										  system("cls");
										  Sleep(50);
										  CCONSOLE::GoToXY(cs.getMaxX() / 2, cs.getMaxY() / 2);
										  CCONSOLE::textcolor(10);
										  SetConsoleActiveScreenBuffer(hStdout);
										  cout << "YOU WIN!";
										  Sleep(2000);

										  CCONSOLE::textcolor(15);
										  qg = true;
										  WIN = false;
										  break;

									  }
									  int temp;
									  if (!WIN||!LOSE) temp = toupper(_getch());

									  
									  if (!cg->getPeople()->isDead())
									  {
										  
										  if (temp == 27)
										  {
											  qg = true;
											  PAUSE = true;
											  break;
											  
										  }
										  else if (temp == 'L')
										  {
											  PAUSE = true;
											  system("cls");
											  CCONSOLE::GoToXY(0, 0);
											  Sleep(10);
											  SetConsoleActiveScreenBuffer(hStdout);
											  if (cg->saveGame())
												  PAUSE = false;
											  else
												  break;
											  system("cls");
											  Sleep(10);
											  cg->startGame();
											  cg->checkLight(CGAME::TIME_T, CGAME::TIME_C, true);
											 
										  }
										  else if (temp == 'T')
										  {
											  PAUSE = true;
											  system("cls");
											  CCONSOLE::GoToXY(0, 0);
											  SetConsoleActiveScreenBuffer(hStdout);
											  cg->loadGame();
											  PAUSE = false;
											  system("cls");
											  Sleep(10);
											  cg->startGame();
											  cg->checkLight(CGAME::TIME_T, CGAME::TIME_C, true);
										  }
										  else if (temp == 'P')
										  {
											  //PAUSE = true;
											  PAUSE = true;
											  PAUSE2 = true;
											  Sleep(100);
											 
											  
											
										  }
										  else if (temp == 'R'){
											  system("cls");
											  cg->startGame();
											  PAUSE = false;
										  }
									
										  MOVING = temp;
									  }
									 

								  }
								  SetConsoleActiveScreenBuffer(hStdout);
								  break;
					  }
					  case 7:
					  {
								CCONSOLE::GoToXY(0, 0);
								system("cls");
								cg->loadGame();

								load = true;
								break;
					  }
					  case 8:
					  {
								cg->enterSetting();
								break;
					  }
					  case 9:
					  {
								quit = true;
								exitGame(&t1);
								return;
					  }
					  }
					  system("cls");
					  Sleep(100);
					  CCONSOLE::printNameTable("CROSS THE ROAD");
					  CCONSOLE::printMenu(0,4);
					  break;

			}

			case 8:
			{
					  quit = true;
					  exitGame(&t1);
					  break;
			}
			}

			CCONSOLE::GoToXY(20, line);
			cout << (char)32;

		}

	}
	delete cg;
	system("pause");
}