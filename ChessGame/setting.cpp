#include "setting.h"

bool isOpposite(const ChessType &a, const ChessType &b)
{
    return (a <= ChessType::bPawn && b >= ChessType::rGeneral) || \
            (a >= ChessType::rGeneral && b <= ChessType::bPawn);
}

bool isValidindex(int x, int y)
{
    return x >= 0 && x < 9 && y >= 0 && y < 10;
}

ChessType strToType(string typeStr, int side)
{
    if(!side) //Red
    {
        if(typeStr == "General")
            return ChessType::rGeneral;
        else if(typeStr == "Advisor")
            return ChessType::rAdvisor;
        else if(typeStr == "Elephant")
            return ChessType::rElephant;
        else if(typeStr == "Horse")
            return ChessType::rHorse;
        else if(typeStr == "Chariot")
            return ChessType::rRook;
        else if(typeStr == "Cannon")
            return ChessType::rCannon;
        else if(typeStr == "Soldier")
            return ChessType::rPawn;
    }

    else //Black
    {
        if(typeStr == "General")
            return ChessType::bGeneral;
        else if(typeStr == "Advisor")
            return ChessType::bAdvisor;
        else if(typeStr == "Elephant")
            return ChessType::bElephant;
        else if(typeStr == "Horse")
            return ChessType::bHorse;
        else if(typeStr == "Chariot")
            return ChessType::bRook;
        else if(typeStr == "Cannon")
            return ChessType::bCannon;
        else if(typeStr == "Soldier")
            return ChessType::bPawn;
    }

    return ChessType::Empty;
}

QString showTypeString(ChessType type)
{
    QString temp = "";
    switch(type)
    {
        case ChessType::bGeneral:
            temp += "bGeneral";
            break;
        case ChessType::bAdvisor:
            temp += "bAdvisor";
            break;
        case ChessType::bElephant:
            temp += "bElephant";
            break;
        case ChessType::bHorse:
            temp += "bHorse";
            break;
        case ChessType::bRook:
            temp += "bRook";
            break;
        case ChessType::bCannon:
            temp += "bCannon";
            break;
        case ChessType::bPawn:
            temp += "bPawn";
            break;
        case ChessType::rGeneral:
            temp += "rGeneral";
            break;
        case ChessType::rAdvisor:
            temp += "rAdvisor";
            break;
        case ChessType::rElephant:
            temp += "rElephant";
            break;
        case ChessType::rHorse:
            temp += "rHorse";
            break;
        case ChessType::rRook:
            temp += "rRook";
            break;
        case ChessType::rCannon:
            temp += "rCannon";
            break;
        case ChessType::rPawn:
            temp += "rPawn";
            break;
        case ChessType::Empty:
            temp += "Empty";
            break;
    }

    return temp;
}

void delay(int time)
{
    QTime dieTime= QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
