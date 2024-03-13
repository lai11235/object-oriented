#include "viewer.h"
#include "ui_viewer.h"

#include <QImage>
#include <QString>
#include <QPixmap>

#include <cmath>

using namespace std;

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    this->setFixedSize(1000,700);
    ui->setupUi(this);
    ui->sideManifest->setVisible(false);
    ui->winer->setVisible(false);
    ui->winBackground->setVisible(false);

    /**Time**/
    ui->processTime->setVisible(false);
    ui->redTime->setVisible(false);
    ui->blackTime->setVisible(false);
    ui->blackFrame->setVisible(false);
    ui->redFrame->setVisible(false);

    /**Button**/
    ui->actionSave->setVisible(false);
    ui->normalMode->setVisible(false);
    ui->limitMode->setVisible(false);
    ui->oneMore->setVisible(false);
    ui->returnMenu->setVisible(false);
    ui->blackGiveUp->setVisible(false);
    ui->redGiveUp->setVisible(false);

    ui->check->setVisible(false);

    clickX = 0;
    clickY = 0;
    isSelected = false;
    mode = 0;

    /**Time setting**/
    time[0] = time[1] = time[2] = 0;
    redTime[0] = blackTime[0] = LIMITSEC;
    redTime[1] = blackTime[1] = LIMITMIN;
    processTimer = new QTimer(this);
    redTimer = new QTimer(this);
    blackTimer = new QTimer(this);
    connect( processTimer, SIGNAL(timeout()), this, SLOT(updateProcessTime()) );
    connect( redTimer, SIGNAL(timeout()), this, SLOT(updateRedTime()) );
    connect( blackTimer, SIGNAL(timeout()), this, SLOT(updateBlackTime()) );

    checkLable = new QGraphicsOpacityEffect(this);
    checkLable->setOpacity(1);
    ui->check->setGraphicsEffect(checkLable);
    danceGif = new QMovie(":/src/yooooo.gif");
    danceGif2 = new QMovie(":/src/yooooo.gif");
    ui->danceGif->setMovie(danceGif);
    ui->danceGif2->setMovie(danceGif2);
    danceGif->start();
    danceGif2->start();

    checkLableAnimation = new QPropertyAnimation(checkLable,"opacity");
    checkLableAnimation->setDuration(1000);
    checkLableAnimation->setStartValue(1);
    checkLableAnimation->setEndValue(0);
}

Viewer::~Viewer()
{
    delete ui;
}

/**Control the scence on screen**/
void Viewer::mousePressEvent(QMouseEvent *event)
{
    if(GameManger::gameStatus != GameSataus::Playing)
            return;
    int x = event->pos().x(), y = event->pos().y();

    if (x < 143 || x > 681 || y < 62 || y > 661) return;
    int indexX = (x - 143) / 61;
    int indexY = (y - 62) / 61;
    int SquaredDistance = pow((x - (61 * indexX + 168)), 2) + pow((y - (61 * indexY + 87)), 2);
    if (SquaredDistance > 625)
    {
        isSelected = false; // make the red path disappear
    }

    else if (!isSelected && Board::gameBoard[indexY][indexX] != ChessType::Empty
             && GameManger::currentSide % 2 != !GameManger::onBoard[{indexX, indexY}]->side())
    {

        /**Finding the valid position can move on the board**/
        GameManger::onBoard[{indexX, indexY}]->isValidMove(Board::gameBoard, Board::validPos);
        clickX = indexX, clickY = indexY;
        isSelected = true;
    }

    else if(isSelected && Board::gameBoard[indexY][indexX] != ChessType::Empty
            && Chess::side(Board::gameBoard[indexY][indexX]) == GameManger::currentSide)
    {
        GameManger::onBoard[{indexX, indexY}]->isValidMove(Board::gameBoard, Board::validPos);
        clickX = indexX, clickY = indexY;
        isSelected = true;
    }

    else if (isSelected && Board::validPos[indexY][indexX])
    {
        /**gameBoard change**/
        ChessType selectType = Board::gameBoard[clickY][clickX];
        ChessType destination = Board::gameBoard[indexY][indexX];
        Board::gameBoard[clickY][clickX] = ChessType::Empty;
        Board::gameBoard[indexY][indexX] = selectType;

        /**onBoard change**/
        Chess *temp = GameManger::onBoard[{clickX, clickY}]; //Store the chess moved temperately
        temp->posX = indexX, temp->posY = indexY;
        GameManger::onBoard.erase({clickX, clickY});
        GameManger::onBoard[{indexX, indexY}] = temp;

        /**Recording the position of general**/
        if(selectType == ChessType::bGeneral)
            GameManger::bGeneralPos = {indexX, indexY};
        else if(selectType == ChessType::rGeneral)
            GameManger::rGeneralPos = {indexX, indexY};

        if(destination == ChessType::bGeneral)
        {
            GameManger::gameStatus = GameSataus::RedWin;
            isSelected = false;
            this->repaint();
            gameOver();
            return;
        }
        else if(destination == ChessType::rGeneral)
        {
            GameManger::gameStatus = GameSataus::BlackWin;
            isSelected = false;
            this->repaint();
            gameOver();
            return;
        }

        short isCheck = GameManger::check();
        if(isCheck)
        {
            ui->check->setVisible(true);
            short isCheckMate = GameManger::checkMate(isCheck);
            if(isCheckMate)
            {
                if(isCheckMate == 1) //Red Lose
                {
                    GameManger::gameStatus = GameSataus::BlackWin;
                    ui->check->setPixmap(QPixmap(":/src/redCheckMate.png"));
                    isSelected = false;
                    this->repaint();
                    checkLableAnimation->start();
                    delay(1);
                    gameOver();
                }
                else
                {
                    GameManger::gameStatus = GameSataus::RedWin;
                    ui->check->setPixmap(QPixmap(":/src/blackCheckMate.png"));
                    checkLableAnimation->start();
                    isSelected = false;
                    this->repaint();
                    delay(1);
                    gameOver();
                }
                return;
            }
            if(isCheck == 1)
               ui->check->setPixmap(QPixmap(":/src/redCheck.png"));
            else
               ui->check->setPixmap(QPixmap(":/src/blackCheck.png"));
            checkLableAnimation->start();
        }

        recordLog({clickX, clickY}, {indexX, indexY}, selectType);

        if(mode)
            limitTimeManage();

        GameManger::currentSide++; // Change the side(0: red, 1: black)
        GameManger::currentSide %= 2;

        if(GameManger::currentSide)
            ui->sideManifest->setPixmap(QPixmap(":/src/blackSide.png"));
        else
            ui->sideManifest->setPixmap(QPixmap(":/src/Redside.png"));

        isSelected = false; // make the red path disappear
    }

    else
    {
        isSelected = false;
    }

    this->repaint();
    return;
}

void Viewer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int posX, posY;

    painter.drawImage(QRect(0, 24, 1252, 700),QImage(":/src/backcolor.png"));
    painter.drawImage(QRect(165, 84, 495, 556),QImage(":/src/chessBoard-3.png"));

    if(isSelected)
    {
         posX = 143 + 61 * clickX - 1, posY = 62 + 61 * clickY -1;
         painter.drawImage(QRect(posX, posY, 52, 52),QImage(":/src/selected.png"));
    }

    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            posX = 143 + 61 * x, posY = 62 + 61 * y;
            switch(Board::gameBoard[y][x])
            {
                case ChessType::bGeneral:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_01.png"));
                    break;
                case ChessType::bAdvisor:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_02.png"));
                    break;
                case ChessType::bElephant:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_03.png"));
                    break;
                case ChessType::bHorse:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_05.png"));
                    break;
                case ChessType::bRook:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_04.png"));
                    break;
                case ChessType::bCannon:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_06.png"));
                    break;
                case ChessType::bPawn:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/blackChess_07.png"));
                    break;
                case ChessType::rGeneral:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_01.png"));
                    break;
                case ChessType::rAdvisor:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_02.png"));
                    break;
                case ChessType::rElephant:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_03.png"));
                    break;
                case ChessType::rHorse:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_06.png"));
                    break;
                case ChessType::rRook:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_05.png"));
                    break;
                case ChessType::rCannon:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_04.png"));
                    break;
                case ChessType::rPawn:
                    painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/redChess_07.png"));
                    break;
                case ChessType::Empty:
                    break;
            }

            if(isSelected && Board::validPos[y][x])// If a chess is seleted then show the position it can achieve
            {
                painter.drawImage(QRect(posX, posY, 50, 50),QImage(":/src/Chess/validPos.png"));
            }
        }
    }
}

QString Viewer::processTimeText()
{
    QString text = "";
    if(time[2] < 10)
        text += "0";

    text += QString::number(time[2]) + ":";

    if(time[1] < 10)
        text += "0";

    text += QString::number(time[1]) + ":";

    if(time[0] < 10)
        text += "0";
    text += QString::number(time[0]);

    return text;
}

QString Viewer::sideTimerText(bool _side)
{
    QString text = "";
    if(!_side) //Red
    {
        if(redTime[1] < 10)
            text += "0";
        text += QString::number(redTime[1]) + ":";

        if(redTime[0] < 10)
            text += "0";
        text += QString::number(redTime[0]);
    }
    else
    {
        if(blackTime[1] < 10)
            text += "0";
        text += QString::number(blackTime[1]) + ":";

        if(blackTime[0] < 10)
            text += "0";
        text += QString::number(blackTime[0]);
    }

    return text;
}
