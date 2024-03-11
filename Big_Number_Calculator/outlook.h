#pragma once
#include <windows.h>

enum class Color {
	BLUE, CYAN_BLUE, LBLUE, GREEN, LGREEN, RED, LRED,
	WHITE, PURPLE, MAGENTA, YELLO, CYAN, BLACK, GRAY
};

void backgroundColor(Color type)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (type)
	{
		case Color::RED:
			SetConsoleTextAttribute(hOut, 64);
			break;

		case Color::LRED:
			SetConsoleTextAttribute(hOut, 192);
			break;

		case Color::BLUE:
			SetConsoleTextAttribute(hOut, 16);
			break;

		case Color::CYAN_BLUE:
			SetConsoleTextAttribute(hOut, 3);
			break;

		case Color::LBLUE:
			SetConsoleTextAttribute(hOut, 144);
			break;

		case Color::GREEN:
			SetConsoleTextAttribute(hOut, 32);
			break;

		case Color::LGREEN:
			SetConsoleTextAttribute(hOut, 150);
			break;

		case Color::PURPLE:
			SetConsoleTextAttribute(hOut, 80);
			break;

		case Color::MAGENTA:
			SetConsoleTextAttribute(hOut, 208);
			break;

		case Color::CYAN:
			SetConsoleTextAttribute(hOut, 96);
			break;

		case Color::YELLO:
			SetConsoleTextAttribute(hOut, 224);
			break;
		case Color::WHITE:
			SetConsoleTextAttribute(hOut, 112);
			break;
		case Color::BLACK:
			SetConsoleTextAttribute(hOut, 0);
			break;
		case Color::GRAY:
			SetConsoleTextAttribute(hOut, 128);
			break;
	}
	return;
}

void colorReset()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	return;
}
