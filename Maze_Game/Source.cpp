#include <iostream>
#include <vector>
#include <utility>
#include <conio.h>
#include <ctime>
#include "Error.h"
#include "Maze.h"
#include "Operation.h"
#include "Sprite.h"
#include "Setting.h"
#include "Interface.h"
#include "Item.h"

using namespace std;

bool win(Player &, int);

int main()
{
	srand(time(NULL));

	char key;
	vector<Creature *> monster;
	vector<Item*> item;
	Player player;
	bool readRecord = false;

	drawRead(); //Drawing the meun to ask the player if read the record
	
	while (key = _getch())
	{
		if (key == 'y' || key == 'Y') //Reading the record
		{
			readRecord = true;
			Creature _monster;
			Player _player;

			ifstream ifile("enemy.dat", ios::binary);
			while (ifile.read((char*)&_monster, sizeof(_monster)))
			{
				if (_monster.enemyType() == DEMON)
				{
					Demon* demon = new Demon(_monster);
					monster.push_back(demon);
				}
				else
				{
					Goblin* goblin = new Goblin(_monster);
					monster.push_back(goblin);
				}
			}
				
			ifile.close();

			ifile.open("player.dat", ios::binary);
			ifile.read((char*)&_player, sizeof(_player));
			player = _player;
			ifile.close();

			ifile.open("maze.txt");
			ifile >> SIZE_X;
			ifile >> SIZE_Y;
			ifile.close();

			system("cls");
			break;
		}
		else if (key == 'n' || key == 'N') //Do not read the record
		{
			system("cls");
			break;
		}
	}

	if (!readRecord)
	{
		string size;
		drawInputSize();
		getline(cin, size);
		if (!size.size())
		{
			SIZE_X = 31, SIZE_Y = 31;
		}
		else
			getMazeSize(size, SIZE_X, SIZE_Y);
		system("cls");
		cursorReset(make_pair(0, 1));
	}

	Maze maze(DIS_X, DIS_Y, SIZE_X, SIZE_Y);

	if (readRecord)
	{
		ifstream ifile("maze.txt");
		string temp;
		ifile >> temp;
		ifile >> temp;
		int y = 0;

		while (ifile >> temp)
		{
			for (int x = 0; x < SIZE_X; x++)
			{
				maze.modify(x, y, (temp[x] - '0'));
			}
			y++;
		}
	}
	
	/*record the time have passed while game began to control the move speed of enemy*/
	clock_t moveFirst, moveLast;
	moveFirst = clock();	
	moveLast = moveFirst;

	clock_t attackFirst, attackLast;
	attackFirst = clock();
	attackLast = attackFirst;

	bool typeMode = false, first = true;
	showConsoleCursor(false);
	drawMenu();

	while (1)
	{
		key = _getch();
		
		if (key == 'q' || key == 'Q')//while the key is Q, then end the game
		{
			endGame();
		}

		if (key == 'z' || key == 'Z')// Switch of type mode
		{
			typeMode = !typeMode;
			drawPlayModeChoice(typeMode);
			
			continue;
		}

		if (key != 13)   //Player should push the Enter to begin the game
		{
			continue;
		}

		else
		{
			if(first)//Clear the warning of Menu
			{
				first = false;
				string blank(DIS_X + SIZE_X, ' ');
				moveCursor(DIS_X + 20, DIS_Y - 1);
				cout << blank;
				moveCursor(DIS_X + 7, DIS_Y + SIZE_Y);
				cout << blank;
				cursorReset(player.getPlayerPos());
			}

			if (!readRecord)
			{
				maze.generateMaze();
				init_sprite(monster, maze);
				addItem(item, maze);
			}
			else
			{
				system("cls");
				reDrawMaze(maze);
			}

			drawPlayScene(player);
			
			short playerAttack = -1;
			/*
			 -1 : No any action
			  0 : attack on wall
			  1 : attack on enemy
			  2 : attack on air
			*/
			bool enemyAttackFir = true;
			bool delay = false;
			int fullBlood = player.getPlayerBlood();

/*******************************************Game Loop*******************************************/
			while (player.getPlayerBlood())
			{
				delay = player.attackState(playerAttack);
				string command;

				if (typeMode)
				{
					drawPlayModeOnBar();
					getline(cin, command);
					
					if (command == "Win")
					{
						system("cls");
						drawWinScene();
						exit(0);
					}

					try
					{
						player.playerMove(command, maze);
					}
					
					catch (CollideWall& e)
					{
						int p_x = player.getPlayerPos().first, p_y = player.getPlayerPos().second;
						clearStatusBar(p_x, p_y);
						moveCursor(2 * SIZE_X + DIS_X + 6, DIS_Y + 2);
						cout << "Invalid location";
						Sleep(20);
						cursorReset({ p_x, p_y });
					}

					catch (InvalidInput& e)
					{
						int p_x = player.getPlayerPos().first, p_y = player.getPlayerPos().second;
						clearStatusBar(p_x, p_y);
						moveCursor(2 * SIZE_X + DIS_X + 6, DIS_Y + 2);
						cout << "Invalid input";
						Sleep(20);
						cursorReset({ p_x, p_y });
					}
				}
				
				else
				{
					if (_kbhit())
					{
						key = _getch();

						if (key == -32)
							key = _getch();
						if (key == 'Q' || key == 'q')
							endGame();
						if (key == 27)//Exit menu(Esc)
						{
							drawExitMenu();
							key = _getch();
							switch (key)
							{
								case 'R': case 'r':
									system("cls");
									reDrawMaze(maze);
									drawPlayScene(player);
									showPlayerDir(player, maze, monster, playerAttack);
									break;
								case 'S': case 's':
									maze.store();
									playerStore(player);
									enemyStore(monster);
									drawSavedMenu();
									moveCursor(0, DIS_Y + SIZE_Y + 1);
									return 0;
							}
						}

						playerAttack = player.playerAttack(key, maze, monster);

						if (playerAttack == 1)
							drawUpgrade(player);
						try
						{
							player.playerMove(key, maze);
						}

						catch (CollideWall& e)
						{
							int p_x = player.getPlayerPos().first, p_y = player.getPlayerPos().second;
							clearStatusBar(p_x, p_y);
							moveCursor(2 * SIZE_X + DIS_X + 6, DIS_Y + 2);
							cout << "Invalid location";
							Sleep(20); 
							cursorReset({ p_x, p_y });
						}

						catch (InvalidInput& e)
						{
							int p_x = player.getPlayerPos().first, p_y = player.getPlayerPos().second;
							clearStatusBar(p_x, p_y);
							moveCursor(2 * SIZE_X + DIS_X + 6, DIS_Y + 2);
							cout << "Invalid input";
							Sleep(20);
							cursorReset({ p_x, p_y });
						}
					}
				}


				/**************************** Above code is input key control ****************************/

				if ((attackLast - attackFirst) / (double)CLOCKS_PER_SEC  > 0.8 || enemyAttackFir)//Creature Attack
				{
					for (int i = 0; i < monster.size(); i++)
					{
						if (monster[i]->enemyAttack(player.getPlayerPos().first, player.getPlayerPos().second))
						{
							if (enemyAttackFir)
								enemyAttackFir = false;
							player.playerHurt(2);
						}
					}
					drawBloodBar(player, fullBlood);
					
					attackFirst = clock();
				}

				attackLast = clock();
				
				if (monster.size() && (moveLast - moveFirst) / (double)CLOCKS_PER_SEC > 2.0)//Creature Move
				{
					moveFirst = clock();
					for (int i = 0; i < monster.size(); i++)
					{
						if (monster[i]->move)
						{
							monster[i]->move = false;
							continue;
						}

						monster[i]->EnemyMove(maze);
					}
						
					cursorReset(player.getPlayerPos());
				}

				moveLast = clock();

				//show the information on the status bar and change the enemies color if you close to them
				showPlayerDir(player, maze, monster, playerAttack);
				
				if ( win(player, monster.size()) )
				{
					system("cls");
					drawWinScene();
					exit(0);
				}

				if (!delay)//if it doesn't occur attack then wait a specific time
					Sleep(SPEED);
			}

			if (!player.getPlayerBlood())
			{
				system("cls");
				drawLoseScene();
				exit(0);
			}
		}
	}

	return 0;
}

bool win(Player &player, int quan_enemy)
{
	int p_x = player.getPlayerPos().first;
	int p_y = player.getPlayerPos().second;
	return p_x == SIZE_X - 1 && p_y == SIZE_Y - 2 && !quan_enemy;
}