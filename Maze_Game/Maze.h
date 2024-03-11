#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <utility>
#include <fstream>
#include "Operation.h"
#include "Setting.h"

using namespace std;

class Maze
{
	private:
		int pos_x, pos_y;
		int size_x, size_y;
		short** visited;

	public:
		
		Maze(int _pos_x = 0, int _pos_y = 0, int _size_x = SIZE_X, int _size_y = SIZE_Y)
		{
			pos_x = _pos_x, pos_y = _pos_y;
			size_x = _size_x, size_y = _size_y;

			visited = new short* [_size_y];
			for (int i = 0; i < _size_y; i++)
				visited[i] = new short[_size_x];

			for (int i = 0; i < _size_y; i++)
				for (int j = 0; j < _size_x; j++)
					visited[i][j] = WALL;
		}

		~Maze()
		{
			for (int i = 0; i < size_y; i++)
				delete visited[i];
			
			delete[] visited;
		}

		void traversal(int x, int y, int quan, bool flag, stack<pair<int, int> > &path) //Use dfs to creat random maze
		{
			if (flag || !quan)
			{
				flag = true;
				return;
			}
				
			vector<pair<int, int>> is_go;//indicate the point having visited
			vector<int> dir;//store the available direction generator can visit

			int cur_x = path.top().first;
			int cur_y = path.top().second;

			//find the directon available
			for (int i = 0; i < 4; i++)
			{
				switch (i)
				{
					case UP:
						if (cur_y - 2 >= 1 && visited[cur_y - 2][cur_x] == WALL)
						{
							is_go.push_back(make_pair(cur_x, cur_y - 2));
							dir.push_back(UP);
						}

						break;
					case LEFT:
						if (cur_x - 2 >= 1 && visited[cur_y][cur_x - 2] == WALL)
						{
							is_go.push_back(make_pair(cur_x - 2, cur_y));
							dir.push_back(LEFT);
						}
						break;
					case DOWN:
						if (cur_y + 2 < y && visited[cur_y + 2][cur_x] == WALL)
						{
							is_go.push_back(make_pair(cur_x, cur_y + 2));
							dir.push_back(DOWN);
						}
						break;
					case RIGHT:
						if (cur_x + 2 < x && visited[cur_y][cur_x + 2] == WALL)
						{
							is_go.push_back(make_pair(cur_x + 2, cur_y));
							dir.push_back(RIGHT);
						}
						break;
				}
			}

			if (is_go.empty())//if it is empty, finding previous point's qualification
			{
				path.pop();
				traversal(x, y, quan, flag, path);
			}

			else
			{
				int choice = rollDice(is_go.size());//select the direction to move randomly
				int choice_x = is_go[choice].first, choice_y = is_go[choice].second;

				visited[choice_y][choice_x] = ROAD;
				path.push(make_pair(is_go[choice].first, is_go[choice].second));

				switch (dir[choice])
				{
					case UP:
						visited[choice_y + 1][choice_x] = ROAD;
						break;
					case LEFT:
						visited[choice_y][choice_x + 1] = ROAD;
						break;
					case DOWN:
						visited[choice_y - 1][choice_x] = ROAD;
						break;
					case RIGHT:
						visited[choice_y][choice_x - 1] = ROAD;
						break;
				}

				quan--;
				traversal(x, y, quan, flag, path);
			}
		}

		void generateMaze() //draw the origin maze
		{
			bool flag = false;
			int quan = (size_x / 2) * (size_y / 2) - 1;
			pair<int, int> dot;
			stack<pair<int, int> > path;//store the path the generator had passed (x, y)
			path.push(make_pair(1, 1));

			visited[1][1] = ROAD; //The postion the generator start move
			visited[1][0] = ROAD; //Enterance
			visited[size_y - 2][size_x - 1] = ROAD; //Exitence

			traversal(size_x, size_y, quan, flag, path);

			textColor(LGREEN);
			moveCursor(DIS_X - 2, DIS_Y + 1);
			cout << "ªù";
			moveCursor(DIS_X + SIZE_X * 2, DIS_Y + SIZE_Y - 2);
			cout << "ªù";
			colorReset();

			for (int i = 0; i < size_y; i++)
			{
				for (int j = 0; j < size_x; j++)
				{
					if (visited[i][j] == WALL)
					{
						moveCursor(j * 2 + pos_x, i + pos_y);
						showObject(WALL);
					}

					else
					{
						moveCursor(j * 2 + pos_x, i + pos_y);
						cout << "  ";
					}
				}
				cout << endl;
			}
			textColor(WHITE);
			return;
		}

		int visitedVal(int x, int y) //return the value on the maze
		{
			if (x < 0 || y < 0 || x >= SIZE_X || y >= SIZE_Y)
				return -1;
			return visited[y][x];
		}

		void modify(int x, int y, int value) //Modify the value on the maze
		{
			visited[y][x] = value;
			return;
		}

		void store() //Storing the maze into the maze.txt
		{
			fstream file;
			file.open("maze.txt",ios::out);
			file << SIZE_X << " " << SIZE_Y << "\n";
			for (int i = 0; i < SIZE_Y; i++)
			{
				for (int j = 0; j < SIZE_X; j++)
				{
					file << visited[i][j];
				}
				file << "\n";
			}
			return;
		}

		friend void reDrawMaze(Maze &maze);
};


