#pragma once
#include <utility>
#include <string>

using namespace std;

int SIZE_X = 31;
int SIZE_Y = 31;

#define WIN_X 800
#define WIN_Y 600

#define DIS_X 20
#define DIS_Y 10

#define ENEMY_QUAN 5
#define ITEM_QUAN 5
#define SPEED 16

#define P_BLOOD 10

enum direction {
	UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, ULEFT = 4, URIGHT = 5,
	LLEFT = 6, LRIGHT = 7
};

enum Color {
	BLUE, CYAN_BLUE, LBLUE, GREEN, LGREEN, RED, LRED,
	WHITE, PURPLE, MAGENTA, YELLO, CYAN, BLACK, GRAY
};

enum Object
{
	PLAYER, WALL, ROAD, BLANK, HP, TRAY, ENEMY, DEMON, GOBLIN
};

bool isValidMove(short e)
{
	return e == ROAD || e == HP || e == TRAY;
}

pair <string, Color> playerLook( "«i", LBLUE);
pair <string, Color> demonLook( "Å]" , GRAY);
pair <string, Color> goblinLook( "­ô" , GREEN);
pair <string, Color> wallLook("¡¼", LGREEN);
pair <string, Color> hpLook("¦å", LRED);
pair <string, Color> trayLook("¨ë", PURPLE);