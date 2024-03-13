#ifndef CHESS_H
#define CHESS_H

#include "setting.h"

using namespace std;

class Chess
{
    protected:
        int posX, posY; //The posoition of the chess
        ChessType type; //The type of the chess
        virtual void Move(ChessType board[][9], bool validPos[][9]) = 0; //Set the rule of chess moving seperately
    public:
        Chess(ChessType _type = ChessType::Empty, int x = 0, int y = 0);

        /**Finding the valid position where the chess can acheive and store into the validPos array**/
        void isValidMove(ChessType board[][9], bool validPos[][9]);
        bool side();// return 0 if the chess is red side, otherwise return 1
        static bool side(ChessType _type);

        friend bool isOpposite(const Chess &a, const Chess &b);// Determine if two chess are opposite side
        friend class  GameManger;
        friend class Viewer;
};

class General:public Chess
{
    private:
    public:
        General(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Pawn:public Chess
{
    private:
    public:
        Pawn(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Horse:public Chess
{
    private:
    public:
        Horse(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Rook:public Chess
{
    private:
    public:
        Rook(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Advisor:public Chess
{
    private:
    public:
        Advisor(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Cannon:public Chess
{
    private:
    public:
        Cannon(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Elephant:public Chess
{
    private:
    public:
        Elephant(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};
class Empty: public Chess
{
    private:
    public:
        Empty(ChessType _type, int x, int y)
        {
            posX = x, posY = y;
            type = _type;
        }
        virtual void Move(ChessType board[][9], bool validPos[][9]);
};

#endif // CHESS_H
