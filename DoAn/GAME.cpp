#include "GAME.h"
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void CGAME::drawGame(CCONSOLE cs,bool p,HANDLE out,HANDLE buff){
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO* chiBuffer = new CHAR_INFO[(MAX_X+15)*(MAX_Y+1)]; // [2][80]; 
	COORD coordBufSize;
	COORD coordBufCoord;
	BOOL fSuccess;

	ShowConsoleCursor(false);
	printInfo();
	if (pp->getY() > MAX_Y)
		pp->Up(1);
	// Set the source rectangle. 
	COBSTACLE **temp = nullptr;
	//Sleep(100);
	CCONSOLE::GoToXY(0, 0);
	for (int i = 0; i < LANE_COUNT; i++)
	{
		string symbol;
		switch (i)
		{
		case 0:{temp = ab;  break; }
		case 1:{temp = ad;  break; }
		case 2:{temp = at;  break; }
		case 3:{temp = ac;  break; }
		}

		for (int j = 0; j < COBSTACLE::SYMBOL_PER_LANE; j++)
		{

			CCONSOLE::GoToXY(temp[j]->getX(), temp[j]->getY());
			//cout << temp[j]->getSymbol();
			printf("%s", temp[j]->getSymbol().c_str());

		}
	}
	CCONSOLE::GoToXY(pp->getX(), pp->getY());
	cout << HUMAN_SYMBOL;
	CCONSOLE::GoToXY(0, 0);


	
	
	// Get a handle to the STDOUT screen buffer to copy from and 
	// create a new screen buffer to copy to. 
	/*out = GetStdHandle(STD_OUTPUT_HANDLE);
	buff = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL */


	srctReadRect.Top = 0;    // top left: row 0, col 0 
	srctReadRect.Left = 0;
	srctReadRect.Bottom = MAX_Y+1; // bot. right: row 1, col 79 
	srctReadRect.Right = (MAX_X + 15);

	// The temporary buffer size is 2 rows x 80 columns. 

	coordBufSize.Y = MAX_Y+1;
	coordBufSize.X = (MAX_X + 15);

	// The top left destination cell of the temporary buffer is 
	// row 0, col 0. 

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	// Copy the block from the screen buffer to the temp. buffer. 

	fSuccess = ReadConsoleOutput(
		out,        // screen buffer to read from 
		chiBuffer,      // buffer to copy into 
		coordBufSize,   // col-row size of chiBuffer 
		coordBufCoord,  // top left dest. cell in chiBuffer 
		&srctReadRect); // screen buffer source rectangle 



	srctWriteRect.Top = 0;    // top lt: row 10, col 0 
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = MAX_Y; // bot. rt: row 11, col 79 
	srctWriteRect.Right = (MAX_X + 15);

	// Copy from the temporary buffer to the new screen buffer. 

	fSuccess = WriteConsoleOutput(
		buff, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);  // dest. screen buffer rectangle 
	Sleep(SPEED);
	if (!p){
		for (int i = 0; i < LANE_COUNT; i++)
		{
			string symbol;
			switch (i)
			{
			case 0:{temp = ab;  break; }
			case 1:{temp = ad;  break; }
			case 2:{temp = at;  break; }
			case 3:{temp = ac;  break; }
			}

			for (int j = 0; j < COBSTACLE::SYMBOL_PER_LANE; j++)
			{

				CCONSOLE::GoToXY(temp[j]->getX(), temp[j]->getY());

				for (int k = 0; k < temp[j]->getSymbol().length(); k++)
					putchar(' ');


			}
		}
	}
	ShowConsoleCursor(true);
	
}

CGAME::CGAME(CCONSOLE cs)
{
	
	LANE_HEIGHT = cs.getMaxY() / LANE_COUNT;
	COBSTACLE **temp;
	MAX_X = cs.getMaxX();
	MAX_Y = cs.getMaxY();
	MARGIN = 5;
	pp = new CPEOPLE;
	ac = new COBSTACLE*[DEFAULT + MAX_LEVEL];
	at = new COBSTACLE*[DEFAULT + MAX_LEVEL];
	ad = new COBSTACLE*[DEFAULT + MAX_LEVEL];
	ab = new COBSTACLE*[DEFAULT + MAX_LEVEL];
	for (int i = 0; i < 4; i++)
	{
		temp = new COBSTACLE*[DEFAULT + MAX_LEVEL];
		for (int j = 0; j < DEFAULT + MAX_LEVEL; j++)
		{
			
			string symbol;
			switch (i)
			{
				case 0:
				{
						  temp[j] = new CBIRD;
						  break;
				}
				case 1:
				{
						  temp[j] = new CDINOSAUR;
						  break;
				}
				case 2:
				{
						  temp[j] = new CTRUCK;
						  break;
				}
				case 3:
				{
						  temp[j] = new CCAR;
						  break;
				}	
			}
		}
		switch (i)
		{
			case 0:{ab = temp; break; }
			case 1:{ad = temp; break; }
			case 2:{at = temp; break; }
			case 3:{ac = temp;  break; }
			
			
			
		}
	}

	
}
void CGAME::resetGame(){
	pp->setY(MAX_Y);
	pp->setX(MAX_X / 2);
	COBSTACLE **temp = nullptr;
	CCONSOLE::GoToXY(0, 0);
	COBSTACLE::SYMBOL_PER_LANE = DEFAULT;
	CPEOPLE::LIFE = 4;
	CGAME::LEVEL_COUNT = 1;
	LIGHT_CAR = false;
	LIGHT_TRUCK = false;
	TIME_C = 0;
	TIME_T = 50;
	for (int i = 0; i < LANE_COUNT; i++)
	{
		string symbol;
		switch (i)
		{
		case 0:{temp = ab; symbol = BIRD_SYMBOL;  break; }
		case 1:{temp = ad; symbol = DINO_SYMBOL; break; }
		case 2:{temp = at; symbol = TRUCK_SYMBOL; break; }
		case 3:{temp = ac; symbol = CAR_SYMBOL; break; }
		}

		for (int j = 0; j < COBSTACLE::SYMBOL_PER_LANE; j++)
		{
			int space = (MAX_X - MARGIN * 2 - COBSTACLE::SYMBOL_PER_LANE*symbol.length()) / (COBSTACLE::SYMBOL_PER_LANE - 1);
			temp[j]->setX(MARGIN + j*(space)+j*symbol.length());
			temp[j]->setY(LANE_HEIGHT*i + LANE_HEIGHT / 2);
			temp[j]->setSymbol(symbol);
			

		}
	}
}
void CGAME::updateLevel(){
	system("cls");
	CCONSOLE::GoToXY(MAX_X/2-10, MAX_Y/2-5);
	CCONSOLE::textcolor(10);
	cout << "LEVEL: " << ++LEVEL_COUNT;
	CCONSOLE::textcolor(15);
	Sleep(2000);
	CCONSOLE::GoToXY(MAX_X / 2 - 10, MAX_Y / 2 - 5);
	cout << "           ";
	int n=COBSTACLE::SYMBOL_PER_LANE++;
	ac[n] = new CCAR;
	at[n] = new CTRUCK;
	ad[n] = new CDINOSAUR;
	ab[n] = new CBIRD;
	//MARGIN = MARGIN*0.8;
	COBSTACLE **temp = nullptr;
	for (int i = 0; i < LANE_COUNT; i++)
	{
		string symbol;
		switch (i)
		{
		case 0:{temp = ab; symbol = BIRD_SYMBOL;  break; }
		case 1:{temp = ad; symbol =DINO_SYMBOL; break; }
		case 2:{temp = at;  symbol = TRUCK_SYMBOL; break; }
		case 3:{temp = ac;  symbol = CAR_SYMBOL; break; }
		}

		for (int j = 0; j < COBSTACLE::SYMBOL_PER_LANE; j++)
		{
			int space = (MAX_X - MARGIN * 2 - COBSTACLE::SYMBOL_PER_LANE*symbol.length()) / (COBSTACLE::SYMBOL_PER_LANE - 1);
			temp[j]->setX(0);
			temp[j]->setY(0);
			temp[j]->setSymbol(symbol);
			temp[j]->Move(MARGIN + j*(space)+j*symbol.length(), LANE_HEIGHT*i + LANE_HEIGHT / 2);

		}
	}
	
	pp->setY(MAX_Y);
	pp->setX(MAX_X / 2);
}
void CGAME::startGame(){
	CCONSOLE::GoToXY(0, 0);
	for (int i = 0; i <= LANE_COUNT; i++)
	{
		int execept = 0;
		if (i == LANE_COUNT)
		{
			execept = 1;
		}
		CCONSOLE::GoToXY(0, LANE_HEIGHT*i - execept);
		for (int j = 0; j <MAX_X; j++)
			cout << "-";
	}
	
	for (int i = 0; i < MAX_Y; i++)
	{
		CCONSOLE::GoToXY(MAX_X, i);
		cout << "|";
	}
	CCONSOLE::GoToXY(0, LANE_HEIGHT * 3 + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
	cout << ' ';
	CCONSOLE::GoToXY(0, LANE_HEIGHT * 2 + 1);
	cout << ' ';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
void CGAME::printInfo(){
	CCONSOLE::textcolor(15);
	CCONSOLE::GoToXY(MAX_X + 1, 0);
	cout << "LIFE:";
	CCONSOLE::textcolor(10);
	cout<< CPEOPLE::LIFE << ' ';
	CCONSOLE::GoToXY(MAX_X + 1, 2);
	CCONSOLE::textcolor(15);
	cout << "LEVEL:";
	CCONSOLE::textcolor(10);
	cout << LEVEL_COUNT;
	CCONSOLE::GoToXY(MAX_X + 1, 4);
	CCONSOLE::textcolor(15);
	cout << "DIFFCULTY:";
	CCONSOLE::textcolor(10);
	CCONSOLE::GoToXY(MAX_X + 1, 5);
	switch (SPEED)
	{
	case 50:cout << "HARD"; break;
	case 80:cout << "NORMAL"; break;
	case 100:cout << "EASY"; break;
	}
	cout << "   ";
	CCONSOLE::textcolor(15);
}
void CGAME::updatePosPeople(char m){
	if (m == 'W' || m == 'A' || m == 'S' || m == 'D')
	{	
		CCONSOLE::GoToXY(pp->getX(), pp->getY());
		if ((pp->getY() % LANE_HEIGHT == 0 && pp->getY()!=MAX_Y) ||pp->getY()==LANE_HEIGHT*LANE_COUNT-1)
			cout << '-';
		else
			cout << ' ';
	}
	switch (m)
	{
	case 'W':{pp->Up(1); break; }
	case 'A':{pp->Left(1); break; }
	case 'S':{pp->Down(1); break; }
	case 'D':{pp->Right(1); break; }
	}
		

}
void CGAME::updatePosVehicle(bool lt,bool lc){
	if (lt && lc) return;
	string s;
	for (int i = 0; i < COBSTACLE::SYMBOL_PER_LANE; i++)
	{
		if (!lt)
		{
			at[i]->Move(1, 0);
			s = at[i]->getSymbol();
			if (at[i]->getX() + s.length() >MAX_X)
			{
				if (at[i]->getX() > MAX_X)
				{
					at[i]->Move(-MAX_X, 0);
					at[i]->setSymbol(TRUCK_SYMBOL);
				}
				else
					at[i]->setSymbol(s.substr(0, s.length() - 1));
			}
		}

		if (!lc) {
			ac[i]->Move(-1, 0);
			s = ac[i]->getSymbol();
			if (ac[i]->getX() <0)
			{
				if (s.length()<= 0)
				{
					ac[i]->setSymbol(CAR_SYMBOL);
					ac[i]->Move(+MAX_X - CAR_SYMBOL.length(), 0);
					
				}
				else
				{
					ac[i]->setSymbol(s.substr(1, s.length() - 1));
					ac[i]->Move(1, 0);
				}
			}
		}
	}
}
void CGAME::updatePosAnimal(){
	string s,temp;
	for (int i = 0; i < COBSTACLE::SYMBOL_PER_LANE; i++)
	{
		ad[i]->Move(-1, 0);
		s = ad[i]->getSymbol();
		if (ad[i]->getX() <0)
		{
			if (s.length() < 1)
			{
				ad[i]->setSymbol(DINO_SYMBOL);
				ad[i]->Move(+MAX_X - DINO_SYMBOL.length(), 0);
				
			}
			else
			{

				ad[i]->setSymbol(s.substr(1, s.length() - 1));
				ad[i]->Move(1, 0);
			}
		}

		ab[i]->Move(1, 0);
		s = ab[i]->getSymbol();
		if (ab[i]->getX() + s.length() >MAX_X)
		{
			if (ab[i]->getX() > MAX_X)
			{
				ab[i]->Move(-MAX_X, 0);
				ab[i]->setSymbol(BIRD_SYMBOL);
			}
			else
				ab[i]->setSymbol(s.substr(0, s.length() - 1));
		}
	}
}
void CGAME::checkLight(int &timet,int &timec,bool ls){
	CCONSOLE::GoToXY(0, LANE_HEIGHT * 3+1);
	if (timec == 50 || (LIGHT_CAR && ls))
	{
		CGAME::LIGHT_CAR = true;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
		cout << ' ';
		
	}
	else if (timec == 75 || (!LIGHT_CAR && ls))
	{
		CGAME::LIGHT_CAR = false;
		timec = 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
		cout << ' ';
		
	}
	
	CCONSOLE::GoToXY(0, LANE_HEIGHT * 2+1);
	if (timet == 75 || (LIGHT_TRUCK && ls))
	{
		CGAME::LIGHT_TRUCK = true;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
		cout << ' ';
	}
	else if (timet == 100 || (!LIGHT_TRUCK && ls))
	{
		CGAME::LIGHT_TRUCK = false;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
		timet = 25;
		cout << ' ';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
void CGAME::enterSetting(){
	system("cls");
	bool quit = false;
	int number = 3;
	int line = 6;
	int x;
	CCONSOLE::printMenu(4, 3);
	CCONSOLE::printNameTable("SETTINGS");
	CCONSOLE::GoToXY(20, line);
	cout << (char)32;
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
					  if (line >= number + 6) line = 6;
					  break;

			}

			case 2:

			case 4:
			{
					  line--;
					  if (line < 6) line = number - 1 + 6;
					  break;
			}

			case 5:
			{
					  switch (line){
					  case 6: 
					  {
								if (SOUND == true)
								{
									CCONSOLE::setItem("SOUND:OFF", 4);
									SOUND = false;
								}
								else
								{
									SOUND = true;
									CCONSOLE::setItem("SOUND:ON", 4);
								}
								  break;
					  }
					  case 7:
					  {
								if (SPEED == 50)
								{
									CCONSOLE::setItem("DIFFCULTY:EASY", 5);
									SPEED = 100;
								}
								else if (SPEED==100)
								{
									CCONSOLE::setItem("DIFFCULTY:NORMAL", 5);
									SPEED = 80;
								}
								else if (SPEED == 80)
								{
									CCONSOLE::setItem("DIFFCULTY:HARD", 5);
									SPEED = 50;
								}
								break;
					  }
					  case 8:
					  {
								CCONSOLE::GoToXY(30, 8);
								cout << ' ';
								string x;
								cin >> x;
								HUMAN_SYMBOL = x;
								CCONSOLE::setItem("SYMBOL:" + x, 6);
								break;
					  }
					  case 9:
					  {
								quit = true;
								return;
					  }
					  }
					  system("cls");
					
					  CCONSOLE::printMenu(4, 3);
					  CCONSOLE::printNameTable("SETTINGS");
					  break;

			}

			case 8:
			{
					  quit = true;
			}
			}

			CCONSOLE::GoToXY(20, line);
			cout << (char)32;

		}

	}

}
bool CGAME::saveGame(){
	char fn[255];
	Sleep(30);
	cout << "Enter file name:";
	fflush(stdin);
	gets(fn);
	FILE* f = fopen(fn, "wb");
	COBSTACLE **temp = nullptr;
	fwrite(&COBSTACLE::SYMBOL_PER_LANE, sizeof(int), 1, f);
	for (int i = 0; i < LANE_COUNT; i++)
	{
		switch (i)
		{
		case 0:{temp = ab;  break; }
		case 1:{temp = ad;  break; }
		case 2:{temp = at;  break; }
		case 3:{temp = ac;  break; }
		}

		for (int j = 0; j < COBSTACLE::SYMBOL_PER_LANE; j++)
		{
			int x = temp[j]->getX();
			int y = temp[j]->getY();
			string symbol = temp[j]->getSymbol();
			fwrite(&x, sizeof(int), 1, f);
			fwrite(&y, sizeof(int), 1, f);
			fwrite(&symbol, sizeof(string), 1, f);

		}
	}
	int x = pp->getX();
	int y = pp->getY();
	fwrite(&x, sizeof(int), 1, f);
	fwrite(&y, sizeof(int), 1, f);
	fwrite(&SPEED, sizeof(int), 1, f);
	fwrite(&HUMAN_SYMBOL, sizeof(string), 1, f);
	fwrite(&CPEOPLE::LIFE, sizeof(int), 1, f);
	fwrite(&LEVEL_COUNT, sizeof(int), 1, f);
	fwrite(&LIGHT_CAR, sizeof(bool), 1, f);
	fwrite(&TIME_C, sizeof(int), 1, f);
	fwrite(&LIGHT_TRUCK, sizeof(bool), 1, f);
	fwrite(&TIME_T, sizeof(int), 1, f);
	cout << "SAVE SUCCESSFUL!" << endl;
	cout << "CONTINUE?(Y/N)" << endl;
	char t;
	fclose(f);
	while (1){
		cin >> t;
		if (t == 'Y')
			return true;
		else if (t == 'N')
			return false;
	}
	
}
int _x, _y;
string _symbol;
void CGAME::loadGame(){
	char fn[255];
	FILE* f;
	while (1)
	{
		cout << "Enter file name (Enter /N to cancel):";
		fflush(stdin);
		gets(fn);
		if (fn[0] == '/' && fn[1] == 'N')
			return;
		f= fopen(fn, "rb");
		if (f)
			break;
		else
			cout << "NO FILE EXIST!" << endl;
	}
	COBSTACLE **temp = nullptr;
	fread(&_x, sizeof(int), 1, f);

	COBSTACLE::SYMBOL_PER_LANE = _x;
	
	string symbol;
	for (int i = 0; i < LANE_COUNT; i++)
	{
		switch (i)
		{
		case 0:{temp = ab;  break; }
		case 1:{temp = ad;  break; }
		case 2:{temp = at;  break; }
		case 3:{temp = ac;  break; }
		}

		for (int j = 0; j < COBSTACLE::SYMBOL_PER_LANE; j++)
		{
			fread(&_x, sizeof(int), 1, f);
			fread(&_y, sizeof(int), 1, f);
			fread(&_symbol, sizeof(string), 1, f);
			temp[j]->setX(_x);
			temp[j]->setY(_y);
			temp[j]->setSymbol(_symbol);

		}
	}
	fread(&_x, sizeof(int), 1, f);
	fread(&_y, sizeof(int), 1, f);
	pp->setX(_x);
	pp->setY(_y);
	fread(&SPEED, sizeof(int), 1, f);
	fread(&HUMAN_SYMBOL, sizeof(string), 1, f);
	fread(&CPEOPLE::LIFE, sizeof(int), 1, f);
	fread(&LEVEL_COUNT, sizeof(int), 1, f);
	fread(&LIGHT_CAR, sizeof(bool), 1, f);
	fread(&TIME_C, sizeof(int), 1, f);
	fread(&LIGHT_TRUCK, sizeof(bool), 1, f);
	fread(&TIME_T, sizeof(int), 1, f);
	fclose(f);
	cout << "LOAD SUCCESFULLY!" << endl;
	Sleep(500);
	//return;
}
CGAME::~CGAME()
{
	for (int i = 0; i < DEFAULT + MAX_LEVEL; i++)
	{
		
		delete ac[i];
	}
	delete pp;
	delete[]ac;
	delete[]ad;
	delete[]at;
	delete[]ab;
}
