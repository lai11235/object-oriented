#include "viewer.h"
#include "gameManger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameManger manger;
    manger.gameStart();
    return a.exec();
}
