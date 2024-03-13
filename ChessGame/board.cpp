#include "board.h"

Board::Board()
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
            gameBoard[y][x] = ChessType::Empty;
    }
    //General
    gameBoard[0][4] = ChessType::bGeneral;
    gameBoard[9][4] = ChessType::rGeneral;

    //Advisor
    gameBoard[0][3] = ChessType::bAdvisor;
    gameBoard[0][5] = ChessType::bAdvisor;
    gameBoard[9][3] = ChessType::rAdvisor;
    gameBoard[9][5] = ChessType::rAdvisor;

    //elephant
    gameBoard[0][2] = ChessType::bElephant;
    gameBoard[0][6] = ChessType::bElephant;
    gameBoard[9][2] = ChessType::rElephant;
    gameBoard[9][6] = ChessType::rElephant;

    //horse
    gameBoard[0][1] = ChessType::bHorse;
    gameBoard[0][7] = ChessType::bHorse;
    gameBoard[9][1] = ChessType::rHorse;
    gameBoard[9][7] = ChessType::rHorse;

    //rook
    gameBoard[0][0] = ChessType::bRook;
    gameBoard[0][8] = ChessType::bRook;
    gameBoard[9][0] = ChessType::rRook;
    gameBoard[9][8] = ChessType::rRook;

    //cannon
    gameBoard[2][1] = ChessType::bCannon;
    gameBoard[2][7] = ChessType::bCannon;
    gameBoard[7][1] = ChessType::rCannon;
    gameBoard[7][7] = ChessType::rCannon;

    //pawn
    for(int x = 0; x < 9; x += 2)
    {
        gameBoard[3][x] = ChessType::bPawn;
        gameBoard[6][x] = ChessType::rPawn;
    }
}

Board::Board(ChessType **loadBoard)
{
    for(int x = 0; x < 9; x++)
        for(int y = 0; y < 10; y++)
        {
            gameBoard[y][x] = loadBoard[y][x];
        }
}

void Board::initValidPos()
{
    for(int y = 0; y < 10; y++)
    {
        for(int  x = 0; x < 9; x++)
            validPos[y][x] = false;
    }
    return;
}

void Board::classBoardInit()
{
    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 10; x++)
            validPos[y][x] = false;
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
            gameBoard[y][x] = ChessType::Empty;
    }
    //General
    gameBoard[0][4] = ChessType::bGeneral;
    gameBoard[9][4] = ChessType::rGeneral;

    //Advisor
    gameBoard[0][3] = ChessType::bAdvisor;
    gameBoard[0][5] = ChessType::bAdvisor;
    gameBoard[9][3] = ChessType::rAdvisor;
    gameBoard[9][5] = ChessType::rAdvisor;

    //elephant
    gameBoard[0][2] = ChessType::bElephant;
    gameBoard[0][6] = ChessType::bElephant;
    gameBoard[9][2] = ChessType::rElephant;
    gameBoard[9][6] = ChessType::rElephant;

    //horse
    gameBoard[0][1] = ChessType::bHorse;
    gameBoard[0][7] = ChessType::bHorse;
    gameBoard[9][1] = ChessType::rHorse;
    gameBoard[9][7] = ChessType::rHorse;

    //rook
    gameBoard[0][0] = ChessType::bRook;
    gameBoard[0][8] = ChessType::bRook;
    gameBoard[9][0] = ChessType::rRook;
    gameBoard[9][8] = ChessType::rRook;

    //cannon
    gameBoard[2][1] = ChessType::bCannon;
    gameBoard[2][7] = ChessType::bCannon;
    gameBoard[7][1] = ChessType::rCannon;
    gameBoard[7][7] = ChessType::rCannon;

    //pawn
    for(int x = 0; x < 9; x += 2)
    {
        gameBoard[3][x] = ChessType::bPawn;
        gameBoard[6][x] = ChessType::rPawn;
    }
}

void Board::putValid(stack< pair<int, int> > &pos)
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            if(validPos[y][x])
                pos.push({x, y});
        }
    }
}

void Board::copyGameBoard(ChessType board[10][9])
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
            board[y][x] = gameBoard[y][x];
    }
}
//Debug
void showValidPos()
{
    for(int y = 0; y < 10; y++)
    {
        QString temp = "";
        for(int x = 0; x < 9; x++)
        {
            if(Board::validPos[y][x])
               temp += "1";
            else
                temp += "0";
        }
        qDebug() <<temp;
    }
    qDebug() << "";
}

void showBoardType()
{
    for(int y = 0; y < 10; y++)
    {
        QString temp = "";
        for(int x = 0; x < 9; x++)
        {
            switch(Board::gameBoard[y][x])
            {
                case ChessType::bGeneral:
                    temp += "1 ";
                    break;
                case ChessType::bAdvisor:
                    temp += "2 ";
                    break;
                case ChessType::bElephant:
                    temp += "3 ";
                    break;
                case ChessType::bHorse:
                    temp += "4 ";
                    break;
                case ChessType::bRook:
                    temp += "5 ";
                    break;
                case ChessType::bCannon:
                    temp += "6 ";
                    break;
                case ChessType::bPawn:
                    temp += "7 ";
                    break;
                case ChessType::rGeneral:
                    temp += "8 ";
                    break;
                case ChessType::rAdvisor:
                    temp += "9 ";
                    break;
                case ChessType::rElephant:
                    temp += "10 ";
                    break;
                case ChessType::rHorse:
                    temp += "11 ";
                    break;
                case ChessType::rRook:
                    temp += "12 ";
                    break;
                case ChessType::rCannon:
                    temp += "13 ";
                    break;
                case ChessType::rPawn:
                    temp += "14 ";
                    break;
                case ChessType::Empty:
                    temp += "15 ";
                    break;
            }
        }
        qDebug() <<temp;
    }
    qDebug() << "";
}

ChessType Board::gameBoard[10][9] = {};

bool Board::validPos[10][9] = {};
