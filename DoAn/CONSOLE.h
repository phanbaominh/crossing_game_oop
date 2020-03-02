#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;
class CCONSOLE
{
private:
	int mWidth, mHeight,mMaxX,mMaxY;
	
public:
	static string mitem[10];
	void FixConsoleWindow();
	void createWindow();
	int getMaxX(){ return mMaxX; }
	int getMaxY(){ return mMaxY; }
	int getWidth(){ return mWidth; }
	int getHeight(){ return mHeight; }
	void setMaxX(int v){ mMaxX = v; }
	void setMaxY(int v){ mMaxY = v; }
	void setWidth(int v){ mWidth = v; }
	void seHeight(int v){ mHeight = v; }
	static void setItem(string s, int i){ mitem[i] = s; }
	static void GoToXY(int x, int y);
	static void textcolor(int x);
	static void printMenu(int start,int number);
	static void printSetting();
	static int move();
	static void printNameTable(char *s);
	
	CCONSOLE();
	~CCONSOLE();
};

