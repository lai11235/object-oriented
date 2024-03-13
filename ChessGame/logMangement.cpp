#include "viewer.h"

void Viewer::openLogFile()
{
    if(GameManger::gameStatus == GameSataus::SelectMode) //The the logFile is new file
        GameManger::creatLogName();

    string name = GameManger::logName;
    if(GameManger::gameStatus == GameSataus::SelectMode)//If the file is new file, the the file name will not add ".txt"
        name += ".txt";
    logFile.open(name, ios::out | ios::app);
}

void Viewer::recordLog(pair<int, int> start, pair<int, int> end, ChessType type)
{
    string logText = "Player: ";
    logText += GameManger::currentSide % 2 ? "2" : "1";
    logText += ", Action: ";

    switch(type)
    {
        case ChessType::bGeneral: case ChessType::rGeneral:
            logText += "General (";
            break;
        case ChessType::bAdvisor: case ChessType::rAdvisor:
            logText += "Advisor (";
            break;
        case ChessType::bElephant: case ChessType::rElephant:
            logText += "Elephant (";
            break;
        case ChessType::bHorse: case ChessType::rHorse:
            logText += "Horse (";
            break;
        case ChessType::bRook: case ChessType::rRook:
            logText += "Chariot (";
            break;
        case ChessType::bCannon: case ChessType::rCannon:
            logText += "Cannon (";
            break;
        case ChessType::bPawn: case ChessType::rPawn:
            logText += "Soldier (";
            break;
        default:
            break;
    }
    logText += char('0' + start.first);
    logText += ", ";
    logText += char('0' + start.second);
    logText += ") -> (";
    logText += char('0' + end.first);
    logText += ", ";
    logText += char('0' + end.second);
    logText += ")";
    logFile << logText << "\n";
}

void Viewer::followLog(pair<int, int> start, pair<int, int> end, ChessType type)
{
    Board::gameBoard[start.second][start.first] = ChessType::Empty;
    Board::gameBoard[end.second][end.first] = type;

    Chess *temp = GameManger::onBoard[{start.first, start.second}]; //Store the chess moved temperately
    temp->posX = end.first, temp->posY = end.second;
    GameManger::onBoard.erase({start.first, start.second});
    GameManger::onBoard[{end.first, end.second}] = temp;
}
