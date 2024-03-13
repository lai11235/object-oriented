#include "viewer.h"

#include <ctime>
#include <stdlib.h>
#include <stack>
#include <utility>

void showBoard(ChessType board[10][9])
{
    for(int y = 0; y < 10; y++)
    {
        QString temp = "";
        for(int x = 0; x < 9; x++)
        {
            switch(board[y][x])
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

GameManger::GameManger()
{
    onBoard[{4, 0}] = new General(ChessType::bGeneral, 4, 0);
    onBoard[{3, 0}] = new Advisor(ChessType::bAdvisor, 3, 0), onBoard[{5, 0}] = new Advisor(ChessType::bAdvisor, 5, 0);
    onBoard[{2, 0}] = new Elephant(ChessType::bElephant, 2, 0), onBoard[{6, 0}] = new Elephant(ChessType::bElephant, 6, 0);
    onBoard[{1, 0}] = new Horse(ChessType::bHorse, 1, 0), onBoard[{7, 0}] = new Horse(ChessType::bHorse, 7, 0);
    onBoard[{0, 0}] = new Rook(ChessType::bRook, 0, 0), onBoard[{8, 0}] = new Rook(ChessType::bRook, 8, 0);
    onBoard[{1, 2}] = new Cannon(ChessType::bCannon, 1, 2), onBoard[{7, 2}] = new Cannon(ChessType::bCannon, 7, 2);
    for(int x = 0; x < 9; x+=2)  onBoard[{x, 3}] = new Pawn(ChessType::bPawn, x, 3);
    onBoard[{4, 9}] = new General(ChessType::rGeneral, 4, 9);
    onBoard[{3, 9}] = new Advisor(ChessType::rAdvisor, 3, 9), onBoard[{5, 9}] = new Advisor(ChessType::rAdvisor, 5, 9);
    onBoard[{2, 9}] = new Elephant(ChessType::rElephant, 2, 9), onBoard[{6, 9}] = new Elephant(ChessType::rElephant, 6, 9);
    onBoard[{1, 9}] = new Horse(ChessType::rHorse, 1, 9), onBoard[{7, 9}] = new Horse(ChessType::rHorse, 7, 9);
    onBoard[{0, 9}] = new Rook(ChessType::rRook, 0, 9), onBoard[{8, 9}] = new Rook(ChessType::rRook, 8, 9);
    onBoard[{1, 7}] = new Cannon(ChessType::rCannon, 1, 7), onBoard[{7, 7}] = new Cannon(ChessType::rCannon, 7, 7);
    for(int x = 0; x < 9; x+=2)  onBoard[{x, 6}] = new Pawn(ChessType::rPawn, x, 6);

    bGeneralPos = {4, 0};
    rGeneralPos = {4, 9};
}

void GameManger::creatLogName()
{
    time_t sec;
    sec = time(NULL);
    itoa(sec, logName, 10);
}

void GameManger::gameStart()
{
    w.show();
}

void GameManger::classGameMangerInit()
{
    currentSide = 0;
    onBoard.clear();
    onBoard[{4, 0}] = new General(ChessType::bGeneral, 4, 0);
    onBoard[{3, 0}] = new Advisor(ChessType::bAdvisor, 3, 0), onBoard[{5, 0}] = new Advisor(ChessType::bAdvisor, 5, 0);
    onBoard[{2, 0}] = new Elephant(ChessType::bElephant, 2, 0), onBoard[{6, 0}] = new Elephant(ChessType::bElephant, 6, 0);
    onBoard[{1, 0}] = new Horse(ChessType::bHorse, 1, 0), onBoard[{7, 0}] = new Horse(ChessType::bHorse, 7, 0);
    onBoard[{0, 0}] = new Rook(ChessType::bRook, 0, 0), onBoard[{8, 0}] = new Rook(ChessType::bRook, 8, 0);
    onBoard[{1, 2}] = new Cannon(ChessType::bCannon, 1, 2), onBoard[{7, 2}] = new Cannon(ChessType::bCannon, 7, 2);
    for(int x = 0; x < 9; x+=2)  onBoard[{x, 3}] = new Pawn(ChessType::bPawn, x, 3);
    onBoard[{4, 9}] = new General(ChessType::rGeneral, 4, 9);
    onBoard[{3, 9}] = new Advisor(ChessType::rAdvisor, 3, 9), onBoard[{5, 9}] = new Advisor(ChessType::rAdvisor, 5, 9);
    onBoard[{2, 9}] = new Elephant(ChessType::rElephant, 2, 9), onBoard[{6, 9}] = new Elephant(ChessType::rElephant, 6, 9);
    onBoard[{1, 9}] = new Horse(ChessType::rHorse, 1, 9), onBoard[{7, 9}] = new Horse(ChessType::rHorse, 7, 9);
    onBoard[{0, 9}] = new Rook(ChessType::rRook, 0, 9), onBoard[{8, 9}] = new Rook(ChessType::rRook, 8, 9);
    onBoard[{1, 7}] = new Cannon(ChessType::rCannon, 1, 7), onBoard[{7, 7}] = new Cannon(ChessType::rCannon, 7, 7);
    for(int x = 0; x < 9; x+=2)  onBoard[{x, 6}] = new Pawn(ChessType::rPawn, x, 6);

    bGeneralPos = {4, 0};
    rGeneralPos = {4, 9};
}

short GameManger::check()//Without check: 0, Red check: 1, Black check: 2
{
    Board::initValidPos();

    int bX = bGeneralPos.first, bY = bGeneralPos.second;
    int rX = rGeneralPos.first, rY = rGeneralPos.second;
    ChessType type;


    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            type = Board::gameBoard[y][x];
            if(type == ChessType::Empty)
                continue;
            if(Board::validPos[bY][bX] && type >= ChessType::rGeneral)
                continue;
            if(Board::validPos[rY][rX] && type <= ChessType::bPawn)
                continue;

            onBoard[{x, y}]->Move(Board::gameBoard, Board::validPos);
        }
    }

    if(!currentSide) //Red
    {
        if(Board::validPos[bY][bX] && Board::validPos[rY][rX])//Black check
            return 2;
        if(Board::validPos[bY][bX])
            return 1;
        if(Board::validPos[rY][rX])
            return 2;
        return 0;
    }
    else
    {
        if(Board::validPos[bY][bX] && Board::validPos[rY][rX])//Red check
            return 1;
        if(Board::validPos[bY][bX])
            return 1;
        if(Board::validPos[rY][rX])
            return 2;
        return 0;
    }

    Board::initValidPos();
}

bool GameManger::check(ChessType board[10][9], pair<int, int> GeneralPos)//for checkmate circumstance, 0: Without check, 1: Still check
{
    Board::initValidPos();

    int gX = GeneralPos.first, gY = GeneralPos.second;
    ChessType type;

    if(!currentSide)//Red check, examinate black whether is still checkmated
    {
        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x < 9; x++)
            {
                type = board[y][x];
                if(type == ChessType::Empty || type <= ChessType::bPawn)
                    continue;
                onBoard[{x, y}]->Move(board, Board::validPos);
                if(Board::validPos[gY][gX])
                {
                    Board::initValidPos();
                    return true;
                }
            }
        }

        Board::initValidPos();
        return false;
    }

    else//Black check, examinate red whether is still checkmated
    {
        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x < 9; x++)
            {
                type = board[y][x];
                if(type == ChessType::Empty || type >= ChessType::rGeneral)
                    continue;
                onBoard[{x, y}]->Move(board, Board::validPos);
                if(Board::validPos[gY][gX])
                {
                    Board::initValidPos();
                    return true;
                }
            }
        }

        Board::initValidPos();
        return false;
    }
}

short GameManger::checkMate(short checkSide) // 0: Without chechmate, 1: red is checkmated, 2: black is checkmated
{
    if(checkSide == 2 && !currentSide)
        return 1;
    else if(checkSide == 1 && currentSide)
        return 2;

    ChessType board[10][9];
    stack< pair<int, int> > movePos;
    ChessType type;
    int GeneralX, GeneralY;

    if(checkSide == 1) //Red
    {
        Board::copyGameBoard(board);

        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x < 9; x++)
            {
                type = Board::gameBoard[y][x];
                if(type == ChessType::Empty || type >= ChessType::rGeneral)
                    continue;
                onBoard[{x, y}]->isValidMove(Board::gameBoard, Board::validPos);
                Board::putValid(movePos);

                ChessType temp;
                while(movePos.size())
                {
                    if(type == ChessType::bGeneral)
                        GeneralX = movePos.top().first, GeneralY = movePos.top().second;
                    else
                        GeneralX = bGeneralPos.first, GeneralY = bGeneralPos.second;

                    board[y][x] = ChessType::Empty;
                    temp = board[movePos.top().second][movePos.top().first];
                    board[movePos.top().second][movePos.top().first] = type;

                    if(!check(board, {GeneralX, GeneralY}))
                        return 0;

                    board[movePos.top().second][movePos.top().first] = temp;
                    board[y][x] = type;

                    movePos.pop();
                }
            }
        }

        return 2;
    }

    else if(checkSide == 2) //Black
    {
        Board::copyGameBoard(board);

        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x < 9; x++)
            {
                type = Board::gameBoard[y][x];
                if(type == ChessType::Empty || type <= ChessType::bPawn)
                    continue;
                onBoard[{x, y}]->isValidMove(Board::gameBoard, Board::validPos);
                Board::putValid(movePos);

                ChessType temp;
                while(movePos.size())
                {
                    if(type == ChessType::rGeneral)
                        GeneralX = movePos.top().first, GeneralY = movePos.top().second;
                    else
                        GeneralX = rGeneralPos.first, GeneralY = rGeneralPos.second;

                    board[y][x] = ChessType::Empty;
                    temp = board[movePos.top().second][movePos.top().first];
                    board[movePos.top().second][movePos.top().first] = type;

                    if(!check(board, {GeneralX, GeneralY}))
                        return 0;

                    board[movePos.top().second][movePos.top().first] = temp;
                    board[y][x] = type;

                    movePos.pop();
                }
            }
        }

        return 1;
    }

    return 0;
}

map<pair<int, int>, Chess *> GameManger::onBoard = {};
pair<int, int> GameManger::bGeneralPos = {};
pair<int, int> GameManger::rGeneralPos = {};
int GameManger::currentSide = 0;
GameSataus GameManger::gameStatus = GameSataus::Menu;
char GameManger::logName[30] = {};
