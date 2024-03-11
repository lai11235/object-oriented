#pragma once
#include <utility>
#include <vector>
#include <time.h>
#include <cmath>
#include <fstream>
#include "Maze.h"
#include "Setting.h"
#include "Operation.h"
#include "Error.h"
#include "Item.h"

using namespace std;

class Creature
{
	protected:
		int blood;
		int attack;
		int x, y;
		Object type;
	public:
		bool move = false;

		Creature(int _blood = 4, int _attack = 2, int _x = 1, int _y = 1, Object _type = DEMON)
		{
			blood = _blood;
			attack = _attack;
			x = _x;
			y = _y;
			type = _type;
		}

		pair<int, int> getEnemyPos()
		{
			return make_pair(x, y);
		}

		short detect(int player_x, int player_y)
		{

			if (abs(player_x - x) <= 2 && abs(player_y - y) <= 2)
			{
				if (player_x == x)
					return player_y > y ? DOWN : UP;

				else if (player_y == y)
					return player_x > x ? RIGHT : LEFT;

				else if (player_x > x)
					return player_y > y ? LRIGHT : URIGHT;

				else
					return player_y > y ? LLEFT : ULEFT;
			}
			else
				return -2;
		}

		bool atkTar(int player_x, int player_y)
		{
			if ((abs(player_x - x) == 1 && abs(player_y - y) == 0) || (abs(player_x - x) == 0 && abs(player_y - y) == 1))
				return true;

			return false;
		}

		int enemyBlood()
		{
			return blood;
		}

		void generateEnemy(Maze& maze)
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

		void EnemyMove(Maze& maze)
		{
			int runTimes = 0;
			int index = rollDice(4);//Chosing a direction to move if the directino is avalible
			int plus = rollDice(5) % 2 ? 3 : 1;//if the direction chosen isn't avalible add some step to another direction
			bool flag = true;//if found a avalible direction then set the flag false
			int pre_x = x, pre_y = y;
			int temp;

			do
			{
				runTimes++;
				switch (index % 4)
				{
					case UP:
						temp = maze.visitedVal(pre_x, pre_y - 1);
						if (temp == ROAD)
						{
							y--;
							flag = false;
						}
						else if (temp == TRAY)
						{
							maze.modify(pre_x, pre_y - 1, ROAD);
							y--;
							flag = false;
							blood -= 1;
						}
						else if (temp == HP)
						{	
							maze.modify(pre_x, pre_y - 1, ROAD);
							y--;
							flag = false;
							blood += 2;
						}
						break;
					case LEFT:
						temp = maze.visitedVal(pre_x - 1, pre_y);
						if (temp == ROAD)
						{
							x--;
							flag = false;
						}
						else if (temp == TRAY)
						{
							maze.modify(pre_x - 1, pre_y, ROAD);
							x--;
							flag = false;
							blood -= 1;
						}
						else if (temp == HP)
						{
							maze.modify(pre_x - 1, pre_y, ROAD);
							x--;
							flag = false;
							blood += 2;
						}
						break;
					case DOWN:
						temp = maze.visitedVal(pre_x, pre_y + 1);
						if (temp == ROAD)
						{
							y++;
							flag = false;
						}
						else if (temp == TRAY)
						{
							maze.modify(pre_x, pre_y + 1, ROAD);
							y++;
							flag = false;
							blood -= 1;
						}
						else if (temp == HP)
						{
							maze.modify(pre_x, pre_y + 1, ROAD);
							y++;
							flag = false;
							blood += 2;
						}
						break;
					case RIGHT:
						temp = maze.visitedVal(pre_x + 1, pre_y);
						if (maze.visitedVal(pre_x + 1, pre_y) == ROAD)
						{
							x++;
							flag = false;
						}
						else if (temp == TRAY)
						{
							maze.modify(pre_x + 1, pre_y, ROAD);
							x++;
							flag = false;
							blood -= 1;
						}
						else if (temp == HP)
						{
							maze.modify(pre_x + 1, pre_y, ROAD);
							x++;
							flag = false;
							blood += 2;
						}
					break;
				}

				index += plus;

			} while (flag && runTimes <= 4);

			maze.modify(pre_x, pre_y, ROAD);//the previous block the enemy standed
			maze.modify(x, y, type);//enemey move to this block

			moveCursor(2 * pre_x + DIS_X, pre_y + DIS_Y);
			cout << "  ";
			moveCursor(2 * x + DIS_X, y + DIS_Y);
			showObject(type);

			return;
		}

		void EnemyMove(Maze& maze, direction dir)
		{
			short fir, sec;
			move = false;
			switch (dir)
			{
				case UP:
					fir = maze.visitedVal(x, y - 1), sec = maze.visitedVal(x, y - 2);
					if(isValidMove(fir) && isValidMove(sec))
					{
						for(int i = 0; i < 2; i++)
						{
							Sleep(40);
							moveCursor(x * 2 + DIS_X, y + DIS_Y - i);
							cout << "  ";
							moveCursor(x * 2 + DIS_X, y + DIS_Y - i - 1);
							showObject(type);
							maze.modify(x, y, ROAD);
							if (maze.visitedVal(x, y - 1) == TRAY)
							{
								blood -= 1;
								if (blood < 0)
									blood = 0;
							}
							else if (maze.visitedVal(x, y - 1) == HP)
							{
								blood += 2;
							}
							maze.modify(x, y - 1, type);
							y--;
						}
						move = true;
					}
					else if (isValidMove(fir))
					{
						Sleep(40);
						moveCursor(x * 2 + DIS_X, y + DIS_Y);
						cout << "  ";
						moveCursor(x * 2 + DIS_X, y + DIS_Y - 1);
						showObject(type);
						maze.modify(x, y, ROAD);
						if (maze.visitedVal(x, y - 1) == TRAY)
						{
							blood -= 1;
							if (blood < 0)
								blood = 0;
						}
						else if (maze.visitedVal(x, y - 1) == HP)
						{
							blood += 2;
						}
						maze.modify(x, y - 1, type);
						y--;
						move = true;
					}
					break;
				case LEFT:
					fir = maze.visitedVal(x - 1, y), sec = maze.visitedVal(x - 2, y);
					if (isValidMove(fir) && isValidMove(sec))
					{
						for (int i = 0; i < 2; i++)
						{
							Sleep(40);
							moveCursor((x - i) * 2 + DIS_X, y + DIS_Y);
							cout << "  ";
							moveCursor((x - i - 1) * 2 + DIS_X, y + DIS_Y);
							showObject(type);
							maze.modify(x, y, ROAD);
							if (maze.visitedVal(x - 1, y) == TRAY)
							{
								blood -= 1;
								if (blood < 0)
									blood = 0;
							}
							else if (maze.visitedVal(x - 1, y) == HP)
							{
								blood += 2;
							}
							maze.modify(x - 1, y, type);
							x--;
						}
						move = true;
					}
					else if (isValidMove(fir))
					{
						Sleep(40);
						moveCursor(x * 2 + DIS_X, y + DIS_Y);
						cout << "  ";
						moveCursor((x - 1) * 2 + DIS_X, y + DIS_Y);
						showObject(type);
						maze.modify(x, y, ROAD);
						if (maze.visitedVal(x - 1, y) == TRAY)
						{
							blood -= 1;
							if (blood < 0)
								blood = 0;
						}
						else if (maze.visitedVal(x - 1, y) == HP)
						{
							blood += 2;
						}
						maze.modify(x - 1, y, type);
						x--;
						move = true;
					}
					break;
				case DOWN:
					fir = maze.visitedVal(x, y + 1), sec = maze.visitedVal(x, y + 2);
					if (isValidMove(fir) && isValidMove(sec))
					{
						for (int i = 0; i < 2; i++)
						{
							Sleep(40);
							moveCursor(x * 2 + DIS_X, y + DIS_Y + i);
							cout << "  ";
							moveCursor(x * 2 + DIS_X, y + DIS_Y + i + 1);
							showObject(type);
							maze.modify(x, y, ROAD);
							if (maze.visitedVal(x, y + 1) == TRAY)
							{
								blood -= 1;
								if (blood < 0)
									blood = 0;
							}
							else if (maze.visitedVal(x, y + 1) == HP)
							{
								blood += 2;
							}
							maze.modify(x, y + 1, type);
							y++;
						}
						move = true;
					}
					else if (isValidMove(fir))
					{
						Sleep(40);
						moveCursor(x * 2 + DIS_X, y + DIS_Y);
						cout << "  ";
						moveCursor(x * 2 + DIS_X, y + DIS_Y + 1);
						showObject(type);
						maze.modify(x, y, ROAD);
						if (maze.visitedVal(x, y + 1) == TRAY)
						{
							blood -= 1;
							if (blood < 0)
								blood = 0;
						}
						else if (maze.visitedVal(x, y + 1) == HP)
						{
							blood += 2;
						}
						maze.modify(x, y + 1, type);
						y++;
						move = true;
					}
					break;
				case RIGHT:
					fir = maze.visitedVal(x + 1, y), sec = maze.visitedVal(x + 2, y);
					if (isValidMove(fir) && isValidMove(sec))
					{
						for (int i = 0; i < 2; i++)
						{
							Sleep(40);
							moveCursor((x + i) * 2 + DIS_X, y + DIS_Y);
							cout << "  ";
							moveCursor((x + i + 1) * 2 + DIS_X, y + DIS_Y);
							showObject(type);
							maze.modify(x, y, ROAD);
							if (maze.visitedVal(x + 1, y) == TRAY)
							{
								blood -= 1;
								if (blood < 0)
									blood = 0;
							}
							else if (maze.visitedVal(x + 1, y) == HP)
							{
								blood += 2;
							}
							maze.modify(x + 1, y, type);
							x++;
						}
						move = true;
					}
					else if (isValidMove(fir))
					{
						Sleep(40);
						moveCursor(x * 2 + DIS_X, y + DIS_Y);
						cout << "  ";
						moveCursor((x + 1) * 2 + DIS_X, y + DIS_Y);
						showObject(type);
						maze.modify(x, y, ROAD);
						if (maze.visitedVal(x + 1, y) == TRAY)
						{
							blood -= 1;
							if (blood < 0)
								blood = 0;
						}
						else if (maze.visitedVal(x + 1, y) == HP)
						{
							blood += 2;
						}
						maze.modify(x + 1, y, type);
						x++;
						move = true;
					}
					break;
			}
		}

		void enemyHurt(int loss)
		{
			blood -= loss;
			return;
		}

		bool enemyAttack(int player_x, int player_y)
		{	
			cursorReset(make_pair(0, 1));
			if (atkTar(player_x, player_y))
			{
				return true;
			}
			return false;
		}

		Object enemyType()
		{
			return type;
		}

		friend class Demon;
		friend class Goblin;
};

class Demon : public Creature
{
	public:
		Demon(int _blood = 4, int atk = 2, int _x = 1, int _y = 1): Creature(_blood, atk, _x, _y, DEMON){}
		Demon(Creature temp)
		{
			blood = temp.blood;
			attack = temp.attack;
			x = temp.x;
			y = temp.y;
			type = DEMON;
		}
};

class Goblin : public Creature
{
	public:
		Goblin(int _blood = 6, int atk = 1, int _x = 1, int _y = 1) : Creature(_blood, atk, _x, _y, GOBLIN){}
		Goblin(Creature temp)
		{
			blood = temp.blood;
			attack = temp.attack;
			x = temp.x;
			y = temp.y;
			type = GOBLIN;
		}
};


/********************Player********************/
class Player
{
	private:
		int blood;
		int attack;
		int direction;
		int x, y;
		int Exp, Lv;
		int weaponPos[2];
		bool isWall;
		short Attack(Maze &maze, vector<class Creature*>& monster)
		{
			modifyObjOutlook(PLAYER, CYAN);
			bool flag = 0;
			short _type = 0;

			switch (direction)
			{
				case UP:
					if (maze.visitedVal(x, y - 1) != WALL)
					{
						if (maze.visitedVal(x, y - 1) == TRAY)
							maze.modify(x, y - 1, ROAD);
						else if (maze.visitedVal(x, y - 1) == HP)
						{
							maze.modify(x, y - 1, ROAD);
							blood += 2;
						}
 						flag = 1;
						weaponPos[0] = x;
						weaponPos[1] = y - 1;
					}

					break;

				case LEFT:
					if (maze.visitedVal(x - 1, y) != WALL)
					{
						if (maze.visitedVal(x - 1, y) == TRAY)
							maze.modify(x - 1, y, ROAD);
						else if (maze.visitedVal(x - 1, y) == HP)
						{
							maze.modify(x - 1, y, ROAD);
							blood += 2;
						}
						flag = 1;
						weaponPos[0] = x - 1;
						weaponPos[1] = y;
					}
					break;

				case DOWN:
					if (maze.visitedVal(x, y + 1) != WALL)
					{
						if (maze.visitedVal(x, y + 1) == TRAY)
							maze.modify(x, y + 1, ROAD);
						else if (maze.visitedVal(x, y + 1) == HP)
						{
							maze.modify(x, y + 1, ROAD);
							blood += 2;
						}
						flag = 1;
						weaponPos[0] = x;
						weaponPos[1] = y + 1;
					}
					break;

				case RIGHT:
					if (maze.visitedVal(x + 1, y) != WALL)
					{
						if (maze.visitedVal(x + 1, y) == TRAY)
							maze.modify(x + 1, y, ROAD);
						else if (maze.visitedVal(x + 1, y) == HP)
						{
							maze.modify(x + 1, y, ROAD);
							blood += 2;
						}
						flag = 1;
						weaponPos[0] = x + 1;
						weaponPos[1] = y;
					}
					break;
			}
			moveCursor(2 * x + DIS_X, y + DIS_Y);
			showObject(PLAYER);
			cursorReset(make_pair(x, y));

			if (flag)//if flag is true then the attack direction is avalible(air and enemy)
			{
				if (maze.visitedVal(weaponPos[0], weaponPos[1]) >= ENEMY)//The situaion player attack on enemy
				{
					int e_x, e_y;

					for (int i = 0; i < monster.size(); i++)
					{
						e_x = monster[i]->getEnemyPos().first;
						e_y = monster[i]->getEnemyPos().second;

						if (e_x == weaponPos[0] && e_y == weaponPos[1])
						{
							monster[i]->enemyHurt(attack);
							moveCursor(e_x * 2 + DIS_X, e_y + DIS_Y);
							showObject(monster[i]->enemyType(), YELLO);

							if (monster[i]->enemyBlood() <= 0)
							{
								upgrade(2);
								maze.modify(e_x, e_y, ROAD);
								moveCursor(e_x * 2 + DIS_X, e_y + DIS_Y);
								cout << "  ";
								monster.erase(monster.begin() + i);
								break;
							}

							break;
						}
					}

					_type = 1;
				}

				else //Attacking on air
				{
					moveCursor(2 * weaponPos[0] + DIS_X, weaponPos[1] + DIS_Y);
					textColor(CYAN);
					switch (direction)
					{
						case UP:
							cout << "★";
							break;
						case LEFT:
							cout << "★";
							break;
						case DOWN:
							cout << "★";
							break;
						case RIGHT:
							cout << "★";
							break;
					}

					_type = 2;
					colorReset();
				}

				cursorReset(make_pair(x, y));
			}

			else
				_type = 0;

			return _type;
		}
		
	public:
		Player(int _blood = 10, int _attack = 2, int dir = 3, int _x = 0, int _y = 1)
		{
			blood = _blood, attack = _attack;
			direction = dir, x = _x, y = _y;
			weaponPos[0] = -1, weaponPos[1] = -1;
			Exp = 0, Lv = 1;
		}

		int getPlayerBlood()
		{
			return blood;
		}

		int getPlayerLv()
		{
			return Lv;
		}

		int getPlayerExp()
		{
			return Exp;
		}

		int getPlayerAtk()
		{
			return attack;
		}

		pair<int, int> getPlayerPos()
		{
			return make_pair(x, y);
		}

		void upgrade(int exp)
		{
			int limit = Lv * 2;
			Exp += exp;
			if (Exp >= limit)
			{
				Lv += 1;
				Exp -= limit;
				attack += 1;
				blood += 1;
				blood = blood > 10 ? 10 : blood;
			}
		}

		void playerMove(char key, Maze &maze)
		{
			int pre_x = x, pre_y = y;
			isWall = false;
			int temp;
			switch (key)
			{
				case 72: case 'w': case 'W'://UP
					temp = maze.visitedVal(x, y - 1);
					if (temp == ROAD)
						y -= 1;
					else if (temp == WALL)
						isWall = true;
					else if (temp == TRAY)
					{
						maze.modify(x, y - 1, ROAD);
						y -= 1;
						blood -= 1;
					}
					else if (temp == HP)
					{
						maze.modify(x, y - 1, ROAD);
						y -= 1;
						blood += 2;
						if (blood > 10)
							blood = 10;
					}					
					direction = UP;
					break;
				case 75: case 'a': case 'A'://LEFT
					temp = maze.visitedVal(x - 1, y);
					if (temp == ROAD)
						x -= 1;
					else if (temp == WALL)
						isWall = true;
					else if (temp == TRAY)
					{
						maze.modify(x - 1, y, ROAD);
						x -= 1;
						blood -= 1;
					}
					else if (temp == HP)
					{
						maze.modify(x - 1, y, ROAD);
						x -= 1;
						blood += 2;
						if (blood > 10)
							blood = 10;
					}
						
					direction = LEFT;
					break;
				case 80: case 's': case 'S'://DOWN
					temp = maze.visitedVal(x, y + 1);
					if (temp == ROAD)
						y += 1;
					else if (temp == WALL)
						isWall = true;
					else if (temp == TRAY) 
					{
						maze.modify(x, y + 1, ROAD);
						y += 1;
						blood -= 1;
					}
					else if (temp == HP)
					{
						maze.modify(x, y + 1, ROAD);
						y += 1;
						blood += 2;
						if (blood > 10)
							blood = 10;
					}
						
					direction = DOWN;
					break;
				case 77: case 'd': case 'D'://RIGHT
					temp = maze.visitedVal(x + 1, y);
					if (temp == ROAD)
						x += 1;
					else if (temp == WALL)
						isWall = true;
					else if (temp == TRAY)
					{
						maze.modify(x + 1, y, ROAD);
						x += 1;
						blood -= 1;
					}					
					else if (temp == HP)
					{
						maze.modify(x + 1, y, ROAD);
						x += 1;
						blood += 2;
						if (blood > 10)
							blood = 10;
					}
					
					direction = RIGHT;
					break;
				default:
					throw InvalidInput();
			}

			if (isWall)
				throw CollideWall();

			if (pre_x == x && pre_y == y)
				return;

			maze.modify(pre_x, pre_y, ROAD); // the road passed before set 1 to show it is empty
			maze.modify(x, y, PLAYER); // the position player standing set 2

			moveCursor(2 * pre_x + DIS_X, pre_y + DIS_Y);
			cout << "  ";

			moveCursor(2 * x + DIS_X, y + DIS_Y);
			showObject(PLAYER);

			cursorReset(make_pair(x, y));
		}

		void playerMove(string command, Maze& maze)
		{
			int _x, _y;
			int pre_x = x, pre_y = y;

			if (command.substr(0, 4) == "Move")
			{
				if (command[5] != ' ')
					command.insert(5, " ");
				int i = 6;
				_x = 0; _y = 0;
				while (command[i] != ',')
				{
					_x = (_x << 1) + (_x << 3) + (command[i] - '0');
					i++;
				}
				i++;
				while (command[i] != ')')
				{
					_y = (_y << 1) + (_y << 3) + (command[i] - '0');
					i++;
				}

				if (abs(_x - x) == 1 || abs(_y - y) == 1)
				{
					if (maze.visitedVal(_x, _y) == ROAD)
					{
						maze.modify(x, y, ROAD);
						x = _x, y = _y;
						maze.modify(_x, _y, PLAYER);

						moveCursor(2 * pre_x + DIS_X, pre_y + DIS_Y);
						cout << "  ";
						moveCursor(2 * x + DIS_X, y + DIS_Y);
						showObject(PLAYER);
						moveCursor(DIS_X + 6, SIZE_Y + DIS_Y);
					}
					else if ((maze.visitedVal(_x, _y) == WALL))
						throw CollideWall();
					else if ((maze.visitedVal(_x, _y) == HP))
					{
						blood += 2;
						maze.modify(_x, _y, ROAD);
					}
					else if ((maze.visitedVal(_x, _y) == TRAY))
					{
						blood -= 1;
						maze.modify(_x, _y, ROAD);
					}
				}
			}

			else if (command.substr(0, 4) == "Jump")
			{
				
				if (command[5] != ' ')
					command.insert(5, " ");
				int i = 6;
				_x = 0; _y = 0;
				while (command[i] != ',')
				{
					_x = (_x << 1) + (_x << 3) + (command[i] - '0');
					i++;
				}
				i++;
				while (command[i] != ')')
				{
					_y = (_y << 1) + (_y << 3) + (command[i] - '0');
					i++;
				}

				if (maze.visitedVal(_x, _y) == ROAD)
				{
					cout << _x << " " << _y << endl;
					maze.modify(x, y, ROAD);
					x = _x, y = _y;
					maze.modify(_x, _y, PLAYER);

					moveCursor(2 * pre_x + DIS_X, pre_y + DIS_Y);
					cout << "  ";
					moveCursor(2 * x + DIS_X, y + DIS_Y);
					showObject(PLAYER);
					moveCursor(DIS_X + 6, SIZE_Y + DIS_Y);

				}
				else if ((maze.visitedVal(_x, _y) == WALL))
					throw CollideWall();
			}

			else
			{
				if (command.size())
				{
					switch (*(command.end() - 1))
					{
						case 'a': case 'A':
							playerMove('a', maze);
							break;
						case 's': case 'S':
							playerMove('s', maze);
							break;
						case 'd': case 'D':
							playerMove('d', maze);
							break;
						case 'w': case 'W':
							playerMove('w', maze);
							break;
					}
				}
			}
		}

		short playerAttack(char key, Maze &maze, vector<class Creature*> &monster)
		{
			/*
			 -1 : No any action
			  0 : attack on wall
			  1 : attack on enemy
			  2 : attack on air
			*/
			short flag;
			
			switch(key)
			{
				case 'f': case 'F':
					flag = (Attack)(maze, monster);
				break;

				default:
					flag = -1;
			}
			return flag;
		}

		void playerHurt(int hurt)
		{
			blood -= hurt;
			return;
		}

		bool attackState(short type)
		{
			
			switch (type)
			{
				case -1:
					return false;
					break;
				case 0: case 1:
					Sleep(40); 
					moveCursor(x * 2 + DIS_X, y + DIS_Y);
					modifyObjOutlook(PLAYER, LBLUE);
					showObject(PLAYER);
					break;
				case 2:
					Sleep(40);
					moveCursor(x * 2 + DIS_X, y + DIS_Y);
					modifyObjOutlook(PLAYER, LBLUE);
					showObject(PLAYER);
					moveCursor(weaponPos[0] * 2 + DIS_X, weaponPos[1] + DIS_Y);
					cout << "  ";
					cursorReset(make_pair(x, y));
					break;
			}

			return true;
		}

		void modifyPlayerPos(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
};

void init_sprite(vector<class Creature *> &monster, Maze &maze)
{
	int goblinQuan = ENEMY_QUAN / 2;
	int demonQuan = ENEMY_QUAN - goblinQuan;

	for (int i = 0; i < goblinQuan; i++)
	{
		Goblin *goblin = new Goblin;
		goblin->generateEnemy(maze);
		monster.push_back(goblin);
	}
	for (int i = 0; i < demonQuan; i++)
	{
		Demon *demon = new Demon;
		demon->generateEnemy(maze);
		monster.push_back(demon);
	}

	maze.modify(0, 1, PLAYER); // the initial position of player
	moveCursor(DIS_X, DIS_Y + 1);
	showObject(PLAYER);
	cursorReset(make_pair(0, 1));
	return;
}

void enemyStore(vector<Creature *> &monster) //stroing the enemy into the binary file "enemy.dat"
{
	fstream file;
	file.open("enemy.dat", ios::binary | ios::out);
	for (int i = 0; i < monster.size(); i++)
	{
		Creature temp = *monster[i];
		file.write((char*)&temp, sizeof(temp));
	}
	file.close();
	return;
}

void playerStore(Player& player) //stroing the enemy into the binary file "player.dat"
{
	fstream file;
	file.open("player.dat", ios::binary | ios::out);
	file.write((char*)&player, sizeof(player));
	file.close();
	return;
}