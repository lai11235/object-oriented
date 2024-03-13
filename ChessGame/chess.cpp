#include "chess.h"

#include <cmath>

pair<int, int> direction[8] =
{
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}
};

Chess::Chess(ChessType _type, int x, int y)
{
    type = _type;
    posX = x;
    posY = y;
}

void General::Move(ChessType board[][9], bool validPos[][9])
{
    pair<int, int> tPos[4] = {{posX, posY - 1}, {posX - 1, posY},
                              {posX, posY + 1}, {posX + 1, posY}};
    int t_X, t_Y;

    for(int i = 0; i < 4; i++)
    {
        t_X = tPos[i].first, t_Y = tPos[i].second;
        if(isValidindex(t_X, t_Y))
        {
            if(type == ChessType::bGeneral)
            {
                if(t_X < 3 || t_X > 5 || t_Y < 0 || t_Y > 2)// General can only move in the region of  3 <= x <= 5 && 0 <= y <= 1
                    continue;
            }

            else
            {
                if(t_X < 3 || t_X > 5 || t_Y < 7 || t_Y > 9)// General can only move in the region of  3 <= x <= 5 && 0 <= y <= 1
                    continue;
            }

            if(board[t_Y][t_X] == ChessType::Empty || isOpposite(this->type, board[t_Y][t_X]))
                validPos[t_Y][t_X] = true;
        }
    }

    if(type == ChessType::bGeneral)
    {
        for(int y = posY + 1; y < 10; y++)
        {
            if(board[y][posX] == ChessType::rGeneral)
            {
                validPos[y][posX] = true;
                break;
            }
            if(board[y][posX] != ChessType::Empty)
                break;
        }
    }
    else
    {
        for(int y = posY - 1; y >= 0; y--)
        {
            if(board[y][posX] == ChessType::bGeneral)
            {
                validPos[y][posX] = true;
                break;
            }
            if(board[y][posX] != ChessType::Empty)
                 break;
        }
    }
}

void Advisor::Move(ChessType board[][9], bool validPos[][9])
{
    pair<int, int> tPos[4] = {{posX + 1, posY - 1}, {posX - 1, posY - 1},
                              {posX - 1, posY + 1}, {posX + 1, posY + 1}};

    int t_X, t_Y;

    for(int i = 0; i < 4; i++)
    {
        t_X = tPos[i].first, t_Y = tPos[i].second;
        if(isValidindex(t_X, t_Y))
        {
            if(type == ChessType::bAdvisor)
            {
                if(t_X < 3 || t_X > 5 || t_Y < 0 || t_Y > 2)// Advisor can only move in the region of  3 <= x <= 5 && 0 <= y <= 1
                    continue;
            }

            else if(type == ChessType::rAdvisor)
            {
                if(t_X < 3 || t_X > 5 || t_Y < 7 || t_Y > 9)// Advisor can only move in the region of  3 <= x <= 5 && 0 <= y <= 1
                    continue;
            }

            if(board[t_Y][t_X] == ChessType::Empty || isOpposite(this->type, board[t_Y][t_X]))
                validPos[t_Y][t_X] = true;
        }
    }
}

void Elephant::Move(ChessType board[][9], bool validPos[][9])
{
    pair<int, int> tPos[4] = {{posX + 2, posY - 2}, {posX - 2, posY - 2},
                              {posX - 2, posY + 2}, {posX + 2, posY + 2}};

    bool obstacle[4];// UPRIGHT, UPLEFT, DOWNLEFT, DOWNRIGHT

    int t_X, t_Y;

    for(int i = 0, j = 7; i < 4; i++, j += 2)// 塞象眼
    {
        j %= 8;
        t_X = posX + direction[j].first;
        t_Y = posY + direction[j].second;
        if(isValidindex(t_X, t_Y))
        {
            if(board[t_Y][t_X] != ChessType::Empty)
                obstacle[i] = true;
            else
                obstacle[i] = false;
        }
        else
            obstacle[i] = false;
    }


    for(int i = 0; i < 4; i++)
    {
        if(obstacle[i])
            continue;

        t_X = tPos[i].first, t_Y = tPos[i].second;
        if(isValidindex(t_X, t_Y))
        {
            if(type == ChessType::bElephant)
            {
                if(t_Y > 4)// Elephant can only move in the same side
                    continue;

                if(board[t_Y][t_X] == ChessType::Empty || board[t_Y][t_X] >= ChessType::rGeneral)
                    validPos[t_Y][t_X] = true;

            }
            else
            {
                if(t_Y < 5)// Elephant can only move in the same side
                    continue;

                if(board[t_Y][t_X] == ChessType::Empty || board[t_Y][t_X] <= ChessType::bPawn)
                    validPos[t_Y][t_X] = true;
            }
        }
    }
}

void Horse::Move(ChessType board[][9], bool validPos[][9])
{
    pair<int, int> tPos[8] = {make_pair(posX + 2, posY - 1), make_pair(posX + 1, posY - 2),
                              make_pair(posX - 1, posY - 2), make_pair(posX - 2, posY - 1),
                              make_pair(posX - 2, posY + 1), make_pair(posX - 1, posY + 2),
                              make_pair(posX + 1, posY + 2), make_pair(posX + 2, posY + 1)};
    bool obstacle[8];// UP -> UPRIGHT Counterclockwise
    int t_X, t_Y;

    for(int i = 0; i < 8; i++)// 拐馬腳
    {
        t_X = posX + direction[i].first;
        t_Y = posY + direction[i].second;
        if(isValidindex(t_X, t_Y))
        {
            if(board[t_Y][t_X] != ChessType::Empty)
                obstacle[i] = true;
            else
                obstacle[i] = false;
        }
        else
            obstacle[i] = false;
    }


    for(int i = 0, p1 = 6, p2 = 7; i < 8; i++, p1++, p2++)
    {
        p1 %= 8, p2 %= 8;
        if(obstacle[p1] || obstacle[p2])
            continue;
        t_X = tPos[i].first, t_Y = tPos[i].second;
        if(isValidindex(t_X, t_Y))
        {
            if(board[t_Y][t_X] == ChessType::Empty || isOpposite(this->type, board[t_Y][t_X]))
                validPos[t_Y][t_X] = true;
        }
    }
}

void Rook::Move(ChessType board[][9], bool validPos[][9])
{
    for(int x = posX + 1; x < 9; x++) //RIGHT
    {
        if(board[posY][x] != ChessType::Empty)
        {
            if( isOpposite(this->type, board[posY][x]) )
                validPos[posY][x] = true;
            break;
        }
        validPos[posY][x] = true;
    }
    for(int x = posX - 1; x >= 0; x--) //LEFT
    {
        if(board[posY][x] != ChessType::Empty)
        {
            if( isOpposite(this->type, board[posY][x]) )
                validPos[posY][x] = true;
            break;
        }
        validPos[posY][x] = true;
    }
    for(int y = posY - 1; y >= 0; y--) //UP
    {
        if(board[y][posX] != ChessType::Empty)
        {
            if( isOpposite(this->type, board[y][posX]) )
                validPos[y][posX] = true;
            break;
        }
        validPos[y][posX] = true;
    }
    for(int y = posY + 1; y < 10; y++) //DOWN
    {
        if(board[y][posX] != ChessType::Empty)
        {
            if( isOpposite(this->type, board[y][posX]) )
                validPos[y][posX] = true;
            break;
        }
        validPos[y][posX] = true;
    }
}

void Cannon::Move(ChessType board[][9], bool validPos[][9])
{
    int chessQuan = 0;
    for(int x = posX + 1; x < 9; x++) //RIGHT
    {
        if(board[posY][x] != ChessType::Empty)
            chessQuan++;
        if(!chessQuan)
            validPos[posY][x] = true;
        if(chessQuan == 2)
        {
            if(isOpposite(this->type, board[posY][x]))
                validPos[posY][x] = true;
            break;
        }
    }
    chessQuan = 0;
    for(int x = posX - 1; x >= 0; x--) //LEFT
    {
        if(board[posY][x] != ChessType::Empty)
            chessQuan++;
        if(!chessQuan)
            validPos[posY][x] = true;
        if(chessQuan == 2)
        {
            if(isOpposite(this->type, board[posY][x]))
                validPos[posY][x] = true;
            break;
        }
    }
    chessQuan = 0;
    for(int y = posY - 1; y >= 0; y--) //UP
    {
        if(board[y][posX] != ChessType::Empty)
            chessQuan++;
        if(!chessQuan)
            validPos[y][posX] = true;
        if(chessQuan == 2)
        {
            if(isOpposite(this->type, board[y][posX]))
                validPos[y][posX] = true;
            break;
        }
    }
    chessQuan = 0;
    for(int y = posY + 1; y < 10; y++) //DOWN
    {
        if(board[y][posX] != ChessType::Empty)
            chessQuan++;
        if(!chessQuan)
            validPos[y][posX] = true;
        if(chessQuan == 2)
        {
            if(isOpposite(this->type, board[y][posX]))
                validPos[y][posX] = true;
            break;
        }
    }
}

void Pawn::Move(ChessType board[][9], bool validPos[][9])
{
    pair<int, int> tPos[2] = {{posX + 1, posY}, {posX - 1, posY}};
    int t_X, t_Y;
    if(type == ChessType::bPawn)
    {
       t_X = posX, t_Y = posY + 1;
       if(isValidindex(t_X, t_Y))
       {
           if(board[t_Y][t_X] == ChessType::Empty || isOpposite(this->type, board[t_Y][t_X]))
               validPos[t_Y][t_X] = true;
       }
       if(posY <= 4)
        return;
    }
    if(type == ChessType::rPawn)
    {
       t_X = posX, t_Y = posY - 1;
       if(isValidindex(t_X, t_Y))
       {
           if(board[t_Y][t_X] == ChessType::Empty || isOpposite(this->type, board[t_Y][t_X]))
               validPos[t_Y][t_X] = true;
       }
       if(posY >= 5)
        return;
    }

   for(int i = 0; i < 2; i++)
   {
       t_X = tPos[i].first, t_Y = tPos[i].second;
       if(isValidindex(t_X, t_Y))
       {
           if(board[t_Y][t_X] == ChessType::Empty || isOpposite(this->type, board[t_Y][t_X]))
               validPos[t_Y][t_X] = true;
       }
   }

}

void Empty::Move(ChessType board[][9], bool validPos[][9])
{
    Q_UNUSED(board);
    Q_UNUSED(validPos);
    return;
}

void Chess::isValidMove(ChessType board[][9], bool validPos[][9])
{
    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 9; x++)
            validPos[y][x] = false;
    this->Move(board, validPos);
}

bool Chess::side()
{
    return type <= ChessType::bPawn;
}

bool Chess::side(ChessType t)
{
    return t <= ChessType::bPawn;
}
