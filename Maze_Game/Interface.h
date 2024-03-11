#pragma once
#include <iostream>
#include "Operation.h"
#include "Sprite.h"
#include "Maze.h"

using namespace std;

void canvas(int sizeX, int sizeY)
{
	textColor(CYAN_BLUE);
	for (int i = 1; i < sizeY - 1; i++)
	{
		moveCursor(DIS_X, i + DIS_Y);
		cout << "□";
		moveCursor(DIS_X + (sizeX - 1) * 2, i + DIS_Y);
		cout << "□";
	}

	for (int i = 1; i < sizeX - 1; i++)
	{
		moveCursor(i * 2 + DIS_X, DIS_Y);
		cout << "■";
		moveCursor(i * 2 + DIS_X, DIS_Y + sizeY - 1);
		cout << "■";
	}

	moveCursor(DIS_X, DIS_Y);
	cout << "◢";
	moveCursor((sizeX - 1) * 2 + DIS_X, DIS_Y);
	cout << "◣";
	moveCursor(DIS_X, DIS_Y + sizeY - 1);
	cout << "◥";
	moveCursor((sizeX - 1) * 2 + DIS_X, DIS_Y + sizeY - 1);
	cout << "◤";
}

void drawRead() //Read record menu
{
	showConsoleCursor(false);
	int x = 31, y = 31;
	canvas(x, y);
	textColor(YELLO);
	moveCursor(x + DIS_X - 24, y / 2 + DIS_Y);
	cout << "Whether playing the previous record? Yes(Y) No(N)";
	colorReset();
	return;
}

void drawInputSize()
{
	showConsoleCursor(true);
	int x = 31, y = 31;
	canvas(x, y);

	textColor(YELLO);
	moveCursor(x + DIS_X - 21, y / 2 + DIS_Y - 1);
	cout << "Input the x and y direction size of the Maze";
	moveCursor(x + DIS_X - 9, y / 2 + DIS_Y + 1);
	cout << "Seperated by Space";
	moveCursor(x + DIS_X - 13, y / 2 + DIS_Y);
	cout << "(Highly recommand 31 * 31):";
	colorReset();
	return;
}

void drawMenu()
{
	canvas(SIZE_X, SIZE_Y);
	
	backgroundColor(WHITE);
	for (int i = 1; i < SIZE_Y - 1; i++)
		for (int j = 1; j < SIZE_X - 1; j++)
		{
			moveCursor(j * 2 + DIS_X, i + DIS_Y);
			cout << "  ";
		}
	
	moveCursor(SIZE_X + DIS_X - 11, SIZE_Y / 2 + DIS_Y - 3);
	cout << "Press Enter to begin!\n";
	moveCursor(SIZE_X + DIS_X - 8, SIZE_Y / 2 + DIS_Y - 1);
	cout << "W↑ A← S↓ D→";
	moveCursor(SIZE_X + DIS_X - 6, SIZE_Y / 2 + DIS_Y  + 1);
	cout << "F: Attack";
	moveCursor(SIZE_X + DIS_X - 10, SIZE_Y / 2 + DIS_Y + 3);
	cout << "Z:Type Mode Q: Exit";

	cursorReset(make_pair(0, 1));
	colorReset();
	return;
}

void drawBloodBar(Player &player, int full_blood)
{
	moveCursor(DIS_X, DIS_Y - 1);
	
	textColor(RED);
	for (int i = 0; i < player.getPlayerBlood(); i++)
		cout << "■";
	for (int i = player.getPlayerBlood(); i < full_blood; i++)
		cout << "  ";
	colorReset();
	cursorReset(player.getPlayerPos());
}

void drawUpgrade(Player& player)
{
	moveCursor(DIS_X + P_BLOOD * 2 + 4, DIS_Y - 1);
	textColor(LBLUE);
	cout << "Lv : " << player.getPlayerLv() << "     " << "Exp : " << player.getPlayerExp() << "/" << player.getPlayerLv() * 2;
	cout << "      Atk:" << player.getPlayerAtk();
	cursorReset(player.getPlayerPos());
	return;
}

void drawWinScene()
{
	canvas(SIZE_X, SIZE_Y);

	moveCursor(SIZE_X + DIS_X - 4, SIZE_Y / 2 + DIS_Y);
	cout << "Victory!\n";
	colorReset();
	moveCursor(0, SIZE_Y + DIS_Y + 1);
	return;
}

void drawLoseScene()
{
	canvas(SIZE_X, SIZE_Y);

	moveCursor(SIZE_X + DIS_X - 6, SIZE_Y / 2 + DIS_Y);
	cout << "Loser, LoL!\n";
	colorReset();
	moveCursor(0, SIZE_Y + DIS_Y + 1);
	return;
}

void drawStatusBar()
{
	for (int y = 1; y <= 10; y++)
	{
		moveCursor(2 * SIZE_X + DIS_X + 2, DIS_Y + y);
		cout << "◇";
		moveCursor(2 * SIZE_X + DIS_X + 44, DIS_Y + y);
		cout << "◇";
	}

	for (int x = 1; x <= 20; x++)
	{
		moveCursor(2 * (SIZE_X + x + 1) + DIS_X, DIS_Y + 1);
		cout << "◇";
		moveCursor(2 * (SIZE_X + x + 1) + DIS_X, DIS_Y + 10);
		cout << "◇";
	}
	return;
}

void drawExitMenu()
{
	system("cls");
	canvas(SIZE_X, SIZE_Y);
	textColor(YELLO);
	moveCursor(SIZE_X + DIS_X - 4, SIZE_Y / 2 + DIS_Y - 1);
	cout << "Save(S)";
	moveCursor(SIZE_X + DIS_X - 5, SIZE_Y / 2 + DIS_Y + 1);
	cout << "Resotre(R)";
	colorReset();
}

void drawSavedMenu()
{
	system("cls");
	canvas(SIZE_X, SIZE_Y);
	textColor(YELLO);
	moveCursor(SIZE_X + DIS_X - 23, SIZE_Y / 2 + DIS_Y);
	cout << "If you want to contiune reopen the game again!";
	colorReset();
}

void drawPlayScene(Player& player)
{
	drawStatusBar();

	backgroundColor(GRAY);
	moveCursor(DIS_X + (SIZE_X - 9), DIS_Y - 4);
	cout << "Click ESC to Save";
	moveCursor(DIS_X + (SIZE_X - 17), DIS_Y - 3);
	cout << "Kill all enemies and find the exit";

	drawBloodBar(player, player.getPlayerBlood());
	drawUpgrade(player);
	colorReset();
	cursorReset(make_pair(0, 1));
}

void drawPlayModeOnBar()
{
	moveCursor(2 * SIZE_X + DIS_X + 2, DIS_Y);
	backgroundColor(GRAY);
	cout << "Type Mode is opened";
	colorReset();
	moveCursor(DIS_X + 6, SIZE_Y + DIS_Y);
	string blank(50, ' ');
	showConsoleCursor(true);
	moveCursor(DIS_X + 6, SIZE_Y + DIS_Y);
	cout << blank;
	moveCursor(DIS_X + 6, SIZE_Y + DIS_Y);
}

void drawPlayModeChoice(bool typeMode)
{
	moveCursor(DIS_X + SIZE_X - 24, DIS_Y + SIZE_Y);
	backgroundColor(RED);
	cout << "Warning: If type mode is opend, you can just move";
	colorReset();
	cursorReset(make_pair(0,0));

	if (!typeMode)
	{
		backgroundColor(GRAY);
		moveCursor(DIS_X + SIZE_X - 9, DIS_Y - 1);
		cout << "Type Mode is closed";
		cursorReset(make_pair(0, 0));
		colorReset();
	}
	else
	{
		backgroundColor(GRAY);
		moveCursor(DIS_X + SIZE_X - 9, DIS_Y - 1);
		cout << "Type Mode is opened";
		cursorReset(make_pair(0, 0));
		colorReset();
	}
}

void clearStatusBar(int x, int y)
{
	for (int y = 2; y <= 9; y++)
	{
		for (int x = 2; x <= 19; x++)
		{
			moveCursor(2 * (SIZE_X + x + 1) + DIS_X, DIS_Y + y);
			cout << "  ";
		}
	}

	cursorReset(make_pair(x, y));
}

void showPlayerDir(Player &player,Maze &maze ,vector<Creature *> &monster, short hurted) // Showing the player direction in respect to enemies
{
	
	int player_x = player.getPlayerPos().first;
	int  player_y = player.getPlayerPos().second;

	clearStatusBar(player_x, player_y);
	short dir;
	int times = 1;

	int e_x, e_y;
	for (int i = 0; i < monster.size(); i++)
	{
		e_x = monster[i]->getEnemyPos().first;
		e_y = monster[i]->getEnemyPos().second;
		dir = monster[i]->detect(player_x, player_y);

		if (dir == -2)// Player is not near the enemy
		{
			moveCursor(2 * e_x + DIS_X, e_y + DIS_Y);
			if (monster[i]->enemyType() == DEMON)
			{
				modifyObjOutlook(monster[i]->enemyType(), GRAY);
			}
			else
			{
				modifyObjOutlook(monster[i]->enemyType(), GREEN);
			}
			
			showObject(monster[i]->enemyType());
		}
			
		else
		{			
			moveCursor(2 * e_x + DIS_X, e_y + DIS_Y);
			if (hurted == 1)
				modifyObjOutlook(monster[i]->enemyType(), YELLO);
			else
				modifyObjOutlook(monster[i]->enemyType(), RED);
			showObject(monster[i]->enemyType());

			moveCursor(2 * SIZE_X + DIS_X + 6, DIS_Y + 1 + times);
			cout << "The player is on the";
			switch (dir)
			{
				case RIGHT:
					cout << " right";
					monster[i]->EnemyMove(maze, RIGHT);
					break;
				case LEFT:
					cout << " left";
					monster[i]->EnemyMove(maze, LEFT);
					break;
				case UP:
					cout << " up";
					monster[i]->EnemyMove(maze, UP);
					break;
				case DOWN:
					cout << " down";
					monster[i]->EnemyMove(maze, DOWN);
					break;
				case ULEFT:
					cout << " upper left";
					break;
				case URIGHT:
					cout << " upper right";
					break;
				case LLEFT:
					cout << " lower left";
					break;
				case LRIGHT:
					cout << " lower right";
					break;
			}

			times++;
		}
		
	}

	cursorReset(make_pair(player_x, player_y));
	
	return;
}

void reDrawMaze(Maze& maze) //draw the empty maze
{
	int sizeX = maze.size_x, sizeY = maze.size_y;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			textColor(LGREEN);
			moveCursor(DIS_X - 2, DIS_Y + 1);
			cout << "門";
			moveCursor(DIS_X + SIZE_X * 2, DIS_Y + SIZE_Y - 2);
			cout << "門";
			colorReset();

			for (int i = 0; i < sizeY; i++)
			{
				for (int j = 0; j < sizeX; j++)
				{
					if (maze.visited[i][j] == WALL)
					{
						moveCursor(j * 2 + DIS_X, i + DIS_Y);
						showObject(WALL);
					}

					else if (maze.visited[i][j] == PLAYER)
					{
						moveCursor(j * 2 + DIS_X, i + DIS_Y);
						showObject(PLAYER);
					}

					else
					{
						moveCursor(j * 2 + DIS_X, i + DIS_Y);
						cout << "  ";
					}
				}
				cout << endl;
			}
			textColor(WHITE);
			return;
		}
	}
}