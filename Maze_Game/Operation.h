#pragma once
#include <windows.h>
#include <utility>
#include "Setting.h"

using namespace std;

int rollDice(int size)
{
	int chosen = rand() % size;
	return chosen;
}

void moveCursor(int x, int y)
{
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	destCoord.X = x;
	destCoord.Y = y;

	SetConsoleCursorPosition(hStdout, destCoord);

	return;
}

void showConsoleCursor(bool show)
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(stdOut, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(stdOut, &cursorInfo);
	
	return;
}

void textColor(int type)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (type)
	{
		case RED:
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			break;

		case LRED:
			SetConsoleTextAttribute(hOut,12);
			break;

		case BLUE:
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;

		case CYAN_BLUE:
			SetConsoleTextAttribute(hOut, 3);
			break;

		case LBLUE:
			SetConsoleTextAttribute(hOut, 9);
			break;

		case GREEN:
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
			break;

		case LGREEN:
			SetConsoleTextAttribute(hOut, 10);
			break;

		case PURPLE:
			SetConsoleTextAttribute(hOut, 5);
			break;

		case MAGENTA:
			SetConsoleTextAttribute(hOut, 13);
			break;

		case CYAN:
			SetConsoleTextAttribute(hOut, 6);
			break;

		case YELLO:
			SetConsoleTextAttribute(hOut, 14);
			break;
		case WHITE:
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			break;
		case BLACK:
			SetConsoleTextAttribute(hOut, 0);
			break;
		case GRAY:
			SetConsoleTextAttribute(hOut, 8);
			break;
	}
	return;
}

void backgroundColor(int type)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	switch (type)
	{
		case RED:
			SetConsoleTextAttribute(hOut, 64);
			break;

		case LRED:
			SetConsoleTextAttribute(hOut, 192);
			break;

		case BLUE:
			SetConsoleTextAttribute(hOut, 16);
			break;

		case CYAN_BLUE:
			SetConsoleTextAttribute(hOut, 3);
			break;

		case LBLUE:
			SetConsoleTextAttribute(hOut, 144);
			break;

		case GREEN:
			SetConsoleTextAttribute(hOut, 32);
			break;

		case LGREEN:
			SetConsoleTextAttribute(hOut, 150);
			break;

		case PURPLE:
			SetConsoleTextAttribute(hOut, 80);
			break;

		case MAGENTA:
			SetConsoleTextAttribute(hOut, 208);
			break;

		case CYAN:
			SetConsoleTextAttribute(hOut, 96);
			break;

		case YELLO:
			SetConsoleTextAttribute(hOut, 224);
			break;
		case WHITE:
			SetConsoleTextAttribute(hOut, 112);
			break;
		case BLACK:
			SetConsoleTextAttribute(hOut, 0);
			break;
		case GRAY:
			SetConsoleTextAttribute(hOut, 128);
			break;
	}
	return;
}

void colorReset()
{
	textColor(WHITE);
	return;
}

void cursorReset(pair<int, int> player_pos) //According the position of the player
{
	if (SIZE_Y < 41)
	{
		moveCursor(0, SIZE_Y + 12);
		return;
	}
		
	int player_x = player_pos.first;
	int player_y = player_pos.second;
	if (player_y <= SIZE_Y / 3)
		moveCursor(player_x * 2 + DIS_X - 10, DIS_Y);
	else if (player_y > SIZE_Y / 3 && player_y <= SIZE_Y * 2 / 3)
		moveCursor(SIZE_X * 2 + DIS_X - 10, SIZE_Y / 3 + DIS_Y);
	else
		moveCursor(player_x * 2 + DIS_X - 10, 2 * SIZE_Y / 3 + DIS_Y);
	
	return;
}

void showObject(Object a)
{
	switch (a)
	{
		case PLAYER:
			textColor(playerLook.second);
			cout << playerLook.first;
			break;
		case WALL:
			textColor(wallLook.second);
			cout << wallLook.first;
			break;
		case ENEMY:
			textColor(demonLook.second);
			cout << demonLook.first;
			break;
		case DEMON:
			textColor(demonLook.second);
			cout << demonLook.first;
			break;
		case GOBLIN:
			textColor(goblinLook.second);
			cout << goblinLook.first;
			break;
		case HP:
			textColor(hpLook.second);
			cout << hpLook.first;
			break;
		case TRAY:
			textColor(trayLook.second);
			cout << trayLook.first;
			break;
	}

	colorReset();
}

void showObject(Object a, Color change)
{
	switch (a)
	{
		case PLAYER:
			textColor(change);
			cout << playerLook.first;
			break;
		case WALL:
			textColor(change);
			cout << wallLook.first;
			break;
		case ENEMY:
			textColor(change);
			cout << demonLook.first;
			break;
		case DEMON:
			textColor(change);
			cout << demonLook.first;
			break;
		case GOBLIN:
			textColor(change);
			cout << goblinLook.first;
			break;
		case HP:
			textColor(change);
			cout << hpLook.first;
			break;
		case TRAY:
			textColor(change);
			cout << trayLook.first;
			break;
	}

	colorReset();
}

void modifyObjOutlook(Object a, Color change) //changing the color
{
	switch (a)
	{
		case PLAYER:
			playerLook.second = change;
			break;
		case WALL:
			wallLook.second = change;
			break;
		case ENEMY:
			demonLook.second = change;
			break;
		case DEMON:
			demonLook.second = change;
			break;
		case GOBLIN:
			goblinLook.second = change;
			break;
		case HP:
			hpLook.second = change;
			break;
		case TRAY:
			trayLook.second = change;
			break;
	}

	return;
}

void modifyObjOutlook(Object a, string change) //Chaging the text
{
	switch (a)
	{
		case PLAYER:
			playerLook.first = change;
			break;
		case WALL:
			wallLook.first = change;
			break;
		case ENEMY:
			demonLook.first = change;
			break;
		case DEMON:
			demonLook.first = change;
			break;
		case GOBLIN:
			goblinLook.first = change;
			break;
		case HP:
			hpLook.first = change;
			break;
		case TRAY:
			trayLook.first = change;
			break;
	}

	return;
}

void modifyObjOutlook(Object a, string change1, Color change2) //text and color change
{
	switch (a)
	{
		case PLAYER:
			playerLook.first = change1;
			playerLook.second = change2;
			break;
		case WALL:
			wallLook.first = change1;
			wallLook.second = change2;
			break;
		case ENEMY:
			demonLook.first = change1;
			demonLook.second = change2;
			break;
		case DEMON:
			demonLook.first = change1;
			demonLook.second = change2;
			break;
		case GOBLIN:
			goblinLook.first = change1;
			goblinLook.second = change2;
			break;
		case HP:
			hpLook.first = change1;
			hpLook.second = change2;
			break;
		case TRAY:
			trayLook.first = change1;
			trayLook.second = change2;
			break;
	}

	return;
}

void getMazeSize(string tar, int& sizeX, int& sizeY) //Seperating the string in to two direction length
{
	tar += ' ';
	int size[2] = { 31, 31 };
	int pos = 0;
	if (!tar.size())
	{
		sizeX = 31;
		sizeY = 31;
	}

	else
	{
		string temp = "";
		int i = 0;
		int pos = 0;
		for (; i < tar.size(); i++)
		{
			if (pos == 2)
				break;

			if (tar[i] >= '0' && tar[i] <= '9')
				temp += tar[i];
			else
			{
				int num = 0;
				for (int j = 0; j < temp.size(); j++)
				{
					num = (num << 1) + (num << 3) + (temp[j] - '0');
				}

				while ((tar[i] < '0' || tar[i] > '9') && i < tar.size())
					i++;
				i--;

				if (!(num % 2))
					num += 1;
				size[pos] = num;
				pos++;
				temp = "";
			}
		}

		sizeX = size[0];
		sizeY = size[1];
	}
}

void endGame()
{
	moveCursor(0, SIZE_Y + DIS_Y);
	exit(0);
}
