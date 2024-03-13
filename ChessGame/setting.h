#ifndef SETTING_H
#define SETTING_H
#define LIMITSEC 0
#define LIMITMIN 30

#include <QtDebug>
#include <QTime>
#include <vector>
#include <utility>
#include <string>
#include <QCoreApplication>

using namespace std;

enum class ChessType
{
    bGeneral, bAdvisor, bElephant, bCannon, bHorse, bRook, bPawn\
    , rGeneral, rAdvisor, rElephant, rCannon, rHorse, rRook, rPawn, Empty
};

enum class GameSataus
{
    Menu, Playing, Pause, Stop, BlackWin, RedWin, Loading, SelectMode
};

bool isOpposite(const ChessType &a, const ChessType &b);// Determine if two chess are opposite side
bool isValidindex(int x, int y);
ChessType strToType(string typeStr, int side);
void delay(int time);
//Debug
QString showTypeString(ChessType type);

#endif // SETTING_H
