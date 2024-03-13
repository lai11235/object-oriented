#ifndef VIEWER_H
#define VIEWER_H

#include "setting.h"
#include "board.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMovie>
#include <map>
#include <fstream>
#include <time.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

class Viewer : public QMainWindow
{
    Q_OBJECT

    public:
        Viewer(QWidget *parent = nullptr);
        ~Viewer();

        friend class GameManger;

    protected:
        void mousePressEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *);
        void closeEvent(QCloseEvent *); //If you press the X on upright



    private slots:

        /**Menu**/
        void on_startButton_clicked();
        void on_exit_clicked();
        void on_loadRecord_clicked();

        /**Game mode select**/
        void on_normalMode_clicked();
        void on_limitMode_clicked();

        /**Game over menu**/
        void on_oneMore_clicked();
        void on_returnMenu_clicked();

        /**Menu bar**/
        void on_actionExit_triggered();
        void on_actionSave_triggered();
        void limitTimeManage();
        void on_blackGiveUp_clicked();
        void on_redGiveUp_clicked();

        void updateProcessTime();
        void updateRedTime();
        void updateBlackTime();

private:
        Ui::Viewer *ui;
        int clickX, clickY; //Storing the previous click index on board
        bool isSelected; //If a chess is selected and the chess is about to move, the set isSelected to true, otherwise, false.
        int time[3]; //second, min, hour
        int redTime[2], blackTime[2]; //for limit time mode(second, min)
        bool mode; //0:normal 1:limit time

        QTimer *processTimer;
        QTimer *redTimer;
        QTimer *blackTimer;
        QString processTimeText();
        QString sideTimerText(bool _side);
        void initTime();

        /**logMangement**/
        ofstream logFile;
        void openLogFile();
        void recordLog(pair<int, int> start, pair<int, int> end, ChessType type); //Record the log text into the logFile
        void followLog(pair<int, int> start, pair<int, int> end, ChessType type);   //Read the log text and follow the command to change the board

        QGraphicsOpacityEffect *checkLable;
        QPropertyAnimation * checkLableAnimation;
        QMovie *danceGif;
        QMovie *danceGif2;

        /**gameProcess**/
        void gameMode();
        void gameStart();
        void gameStop();
        void gameSave();
        void gameOver();
        void Menu();
};

class GameManger
{
    private:
        static int currentSide;// even: Red, odd: Black
        static GameSataus gameStatus;// 0: begin, 1: playing, 2: pause, 3: black win, 4: red win
        Board Board;
        Viewer w;
        static map< pair<int, int>, Chess *> onBoard; //The chess on the board now
        static pair<int, int> bGeneralPos, rGeneralPos;
        static char logName[30];
        static bool check(ChessType Board[10][9], pair<int, int> generalPos);

    public:
        GameManger();
        void gameStart();
        static void creatLogName();
        static void classGameMangerInit();
        static short check();
        static short checkMate(short checkSide);

        friend class Viewer;
};

#endif // VIEWER_H

