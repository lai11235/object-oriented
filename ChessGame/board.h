#ifndef BOARD_H
#define BOARD_H
#include "setting.h"
#include "chess.h"
#include <stack>
#include <vector>
#include <utility>

using namespace std;

class Board
{
    private:
        static ChessType gameBoard[10][9];// Storing the status of the board ontime
        static bool validPos[10][9];// Storing the valid position the seleted chess can move
        static void putValid(stack< pair<int, int> > &pos);
        static void copyGameBoard(ChessType board[10][9]);

    public:
        Board();
        Board(ChessType **loadBoard);
        static void initValidPos();
        static void classBoardInit();
        friend class GameManger;
        friend class Viewer;
        //Debug
        friend void showValidPos();
        friend void showBoardType();
};

#endif // GAMEMANGER_H
