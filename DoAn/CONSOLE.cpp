#include "CONSOLE.h"

void CCONSOLE::FixConsoleWindow(){
	HWND  CCONSOLEWindow = GetConsoleWindow();

	LONG style = GetWindowLong(CCONSOLEWindow, GWL_STYLE);
	style = style &~(WS_THICKFRAME)&~(WS_MAXIMIZEBOX);
	SetWindowLong(CCONSOLEWindow, GWL_STYLE, style);


}
void CCONSOLE::GoToXY(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void CCONSOLE::textcolor(int x){
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	
}
CCONSOLE::CCONSOLE()
{
	mWidth = 1000;
	mHeight = 400;
	HWND  CCONSOLEWindow = GetConsoleWindow();
	RECT r;
	GetWindowRect(CCONSOLEWindow, &r);
	MoveWindow(CCONSOLEWindow, r.left, r.top, mWidth, mHeight, TRUE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
	}
	else
	{
		mMaxY = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		mMaxX = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
	mMaxX -= 15;
	mMaxY -= 1;
	FixConsoleWindow();
	mitem[0] = "New Game";

	mitem[1] = "Load";

	mitem[2] = "Settings";

	mitem[3] = "Exit";

	mitem[4] = "SOUND:ON";

	mitem[5] = "DIFFCULTY:EASY";

	mitem[6] = "SYMBOL:Y";
}
void CCONSOLE::printNameTable(char *s)
{
	int n = strlen(s);
	n = 12 - n / 2;
	GoToXY(19 + n, 4);
	textcolor(12);
	printf("%s", s);
	GoToXY(0, 0);
}
void CCONSOLE::printMenu(int start,int number) {
	
	
	CCONSOLE::textcolor(5);
	CCONSOLE::GoToXY(19, 3);
	int n = number;
	int m = 30;
	printf("%c", 201);
	for (int i = 0; i <m; ++i)
		printf("%c", 205);
	printf("%c", 187);
	for (int i = 4; i < 5 + n + 3; ++i)
	{
		CCONSOLE::GoToXY(20 + m, i);
		printf("%c", 186);
	}
	CCONSOLE::GoToXY(m + 19 + 1, 5 + n + 3);
	printf("%c", 188);
	for (int i = 20 + m - 1; i >= 19; --i)
	{
		CCONSOLE::GoToXY(i, 5 + n + 3);
		printf("%c", 205);
	}
	CCONSOLE::GoToXY(19, 5 + n + 3);
	printf("%c", 200);

	for (int i = 5 + n + 2; i > 3; --i)
	{
		CCONSOLE::GoToXY(19, i);
		printf("%c", 186);
	}
	CCONSOLE::GoToXY(20, 5);
	for (int i = 0; i <m; ++i)
		printf("%c", 205);
	CCONSOLE::textcolor(10);
	for (int i = 0; i < number; i++) {

		CCONSOLE::GoToXY(3 + 20, i + 6);

		cout << mitem[start + i];

		Sleep(10); //Tạm dừng 100ms

	}
	CCONSOLE::textcolor(15);
}

int CCONSOLE::move() {

	char c = _getch();

	if ((int)c == -32) c = _getch();

	switch ((int)c) {

	case 80:
		return 1; //cout << "Xuong";

	case 72:
		return 2; //cout << "Len";

	case 77:
		return 3; //cout << "Phai";       

	case 75:
		return 4; //cout << "Trai";

	case 27:
		return 8; //Nut ESC thoat

	case 13:
		return 5; //Nut Enter

	default:
		return 0; //cout << "Sai";

	}

}

CCONSOLE::~CCONSOLE()
{
}
