#pragma once
#include <vector>

#include "Setting.h"
#include "Maze.h"

class Item
{
	protected:
		Object type;
		int x, y;
		virtual void generateItem(Maze& maze) 
		{
			vector<pair<int, int> >::iterator it;
			int choice_x = rollDice(SIZE_X / 2);
			int choice_y = rollDice(SIZE_Y / 2);

			while (maze.visitedVal(choice_x * 2 + 1, choice_y * 2 + 1) != ROAD)
			{
				choice_x = rollDice(SIZE_X / 2);
				choice_y = rollDice(SIZE_Y / 2);
			}

			x = choice_x * 2 + 1;
			y = choice_y * 2 + 1;
			maze.modify(x, y, type);

			moveCursor(x * 2 + DIS_X, y + DIS_Y);
			showObject(type);
			return;
		}

	public:
		Item()
		{
			x = 0, y = 0, type = TRAY;
		}
		friend void addItem(vector<Item*> item, Maze& maze);
};

class bloodBottle:public Item
{
	public:
		void generateItem(Maze & maze)
		{
			vector<pair<int, int> >::iterator it;
			int choice_x = rollDice(SIZE_X / 2);
			int choice_y = rollDice(SIZE_Y / 2);

			while (maze.visitedVal(choice_x * 2 + 1, choice_y * 2 + 1) != ROAD)
			{
				choice_x = rollDice(SIZE_X / 2);
				choice_y = rollDice(SIZE_Y / 2);
			}

			x = choice_x * 2 + 1;
			y = choice_y * 2 + 1;
			maze.modify(x, y, type);

			moveCursor(x * 2 + DIS_X, y + DIS_Y);
			showObject(type);
			return;
		}

		bloodBottle(int _x, int _y)
		{
			type = HP;
			x = _x;
			y = _y;
		}
};

class Tray :public Item
{
	public:
		void generateItem(Maze& maze)
		{
			vector<pair<int, int> >::iterator it;
			int choice_x = rollDice(SIZE_X / 2);
			int choice_y = rollDice(SIZE_Y / 2);

			while (maze.visitedVal(choice_x * 2 + 1, choice_y * 2 + 1) != ROAD)
			{
				choice_x = rollDice(SIZE_X / 2);
				choice_y = rollDice(SIZE_Y / 2);
			}

			x = choice_x * 2 + 1;
			y = choice_y * 2 + 1;
			maze.modify(x, y, type);

			moveCursor(x * 2 + DIS_X, y + DIS_Y);
			showObject(type);
			return;
		}

		Tray(int _x, int _y)
		{
			type = TRAY;
			x = _x;
			y = _y;
		}
};

void addItem(vector<Item*> item, Maze& maze)
{
	int bloodQuan = ITEM_QUAN * 0.4;
	int trayQuan = ITEM_QUAN - bloodQuan;

	for (int i = 0; i < bloodQuan; i++)
	{
		Item* t = new Item;
		t->type = HP;
		t->generateItem(maze);
		moveCursor(DIS_X + (t->x * 2) ,DIS_Y + t->y);
		showObject(HP);
		item.push_back(t);
	}

	for (int i = 0; i < trayQuan; i++)
	{
		Item* t = new Item;
		t->type = TRAY;
		t->generateItem(maze);
		moveCursor(DIS_X + (t->x * 2), DIS_Y + t->y);
		showObject(TRAY);
		item.push_back(t);
	}
}