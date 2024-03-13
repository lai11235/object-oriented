#include "viewer.h"
#include "ui_viewer.h"

void Viewer::gameMode()
{
    if(GameManger::gameStatus != GameSataus::Menu) //From winer interface
    {
        ui->winer->setVisible(false);
        ui->oneMore->setVisible(false);
        ui->returnMenu->setVisible(false);
        ui->winBackground->setVisible(false);
        ui->title->setVisible(true);
        ui->menuBackground->setVisible(true);
    }
    ui->check->setVisible(false);
    ui->startButton->setVisible(false);
    ui->loadRecord->setVisible(false);
    ui->exit->setVisible(false);
    ui->normalMode->setVisible(true);
    ui->limitMode->setVisible(true);
    ui->actionSave->setVisible(true);
    ui->danceGif->setVisible(true);
    ui->danceGif2->setVisible(true);
    danceGif->start();
    danceGif2->start();

    ui->actionSave->setText("Back");
    GameManger::gameStatus = GameSataus::SelectMode;
}

void Viewer::gameStart()
{
    /**Timer setting**/
    QString text;
    processTimer->start(1000);

    if(GameManger::gameStatus != GameSataus::Loading) //gameStatus == SelectMode
    {
        initTime();
        text = "00:00:00";
        GameManger::currentSide = 0;
    }
    else //gameStatus == Loading
        text = processTimeText();

    ui->processTime->display(text);

    if(mode)//Limit Time mode
    {
        ui->redTime->display(sideTimerText(0));//red
        ui->blackTime->display(sideTimerText(1));//black

        ui->redTime->setVisible(true);
        ui->blackTime->setVisible(true);
        ui->redFrame->setVisible(true);
        ui->blackFrame->setVisible(true);

        if(GameManger::currentSide % 2)
            blackTimer->start(1000);
        else
            redTimer->start(1000);
    }

    if(GameManger::currentSide % 2)
        ui->sideManifest->setPixmap(QPixmap(":/src/blackSide.png"));
    else
        ui->sideManifest->setPixmap(QPixmap(":/src/Redside.png"));

    ui->sideManifest->setVisible(true);
    ui->processTime->setVisible(true);
    ui->blackGiveUp->setVisible(true);
    ui->redGiveUp->setVisible(true);

    if(GameManger::gameStatus == GameSataus::Loading)
        ui->actionSave->setVisible(true);
    else if(GameManger::gameStatus == GameSataus::SelectMode)
        ui->actionSave->setText("Save");

    /**Hide the menu**/
    ui->title->setVisible(false);
    ui->menuBackground->setVisible(false);
    ui->startButton->setVisible(false);
    ui->loadRecord->setVisible(false);
    ui->exit->setVisible(false);
    ui->normalMode->setVisible(false);
    ui->limitMode->setVisible(false);
    ui->danceGif->setVisible(false);
    ui->danceGif2->setVisible(false);
    danceGif2->stop();
    danceGif->stop();

    openLogFile();

    GameManger::gameStatus = GameSataus::Playing;
}

void Viewer::gameStop()
{
    /**Recording the time into logFile**/
    logFile << "@" << processTimeText().toStdString(); //Recording the time into logFile
    if(mode)
    {
        logFile << " " << sideTimerText(0).toStdString() << " ";
        logFile << sideTimerText(1).toStdString();
    }
    logFile << "\n";
    logFile.close();

    GameManger::gameStatus = GameSataus::Stop;
    close();
}

void Viewer::gameSave()
{
    if(GameManger::gameStatus == GameSataus::Playing)
    {
        /**Recording the time into logFile**/
        logFile << "@" << processTimeText().toStdString();
        if(mode)
        {
            logFile << " " << sideTimerText(0).toStdString() << " ";
            logFile << sideTimerText(1).toStdString();
        }
        logFile << "\n";

        /**Timer setting**/
        initTime();
        processTimer->stop();
        redTimer->stop();
        blackTimer->stop();

        /**Hide the playing stuff**/
        ui->sideManifest->setVisible(false);
        ui->processTime->setVisible(false);
        ui->redTime->setVisible(false);
        ui->blackTime->setVisible(false);
        ui->redFrame->setVisible(false);
        ui->blackFrame->setVisible(false);
        ui->actionSave->setVisible(false);
        ui->blackGiveUp->setVisible(false);
        ui->redGiveUp->setVisible(false);

        Board::classBoardInit();
        GameManger::classGameMangerInit();
    }

    else if(GameManger::gameStatus == GameSataus::SelectMode)
    {
        ui->limitMode->setVisible(false);
        ui->normalMode->setVisible(false);
    }

    /**Display the menu**/
    Menu();

    mode = 0;//normal mode

    logFile.close();
    GameManger::gameStatus = GameSataus::Menu; //Click save option will return to menu
}

void Viewer::gameOver()
{
    processTimer->stop();
    redTimer->stop();
    blackTimer->stop();

    /**Hide the playing stuff**/
    ui->check->setVisible(false);
    ui->sideManifest->setVisible(false);
    ui->processTime->setVisible(false);
    ui->redTime->setVisible(false);
    ui->blackTime->setVisible(false);
    ui->redFrame->setVisible(false);
    ui->blackFrame->setVisible(false);
    ui->actionSave->setVisible(false);
    ui->blackGiveUp->setVisible(false);
    ui->redGiveUp->setVisible(false);

    //ui->menuBackground->setVisible(true);
    ui->returnMenu->setVisible(true);
    ui->oneMore->setVisible(true);
    ui->winer->setVisible(true);
    ui->winBackground->setVisible(true);

    if(GameManger::gameStatus == GameSataus::RedWin)
    {
         ui->winer->setPixmap(QPixmap(":/src/redWin.png"));
    }
    else if(GameManger::gameStatus == GameSataus::BlackWin)
    {
         ui->winer->setPixmap(QPixmap(":/src/blackWin.png"));
    }
    logFile.close();

    Board::classBoardInit();
    GameManger::classGameMangerInit();
}

void Viewer::Menu()
{
    if(GameManger::gameStatus == GameSataus::RedWin || GameManger::gameStatus == GameSataus::BlackWin)
    {
        ui->returnMenu->setVisible(false);
        ui->oneMore->setVisible(false);
        ui->winer->setVisible(false);
        ui->winBackground->setVisible(false);
    }

    ui->check->setVisible(false);
    ui->title->setVisible(true);
    ui->menuBackground->setVisible(true);
    ui->startButton->setVisible(true);
    ui->loadRecord->setVisible(true);
    ui->exit->setVisible(true);
    ui->danceGif->setVisible(true);
    ui->danceGif2->setVisible(true);
    danceGif->start();
    danceGif2->start();

    ui->blackGiveUp->setVisible(false);
    ui->redGiveUp->setVisible(false);
}

/**Time Procession**/
void Viewer::updateProcessTime()
{
    time[0]++;
    if(time[0] >= 60)
    {
        time[1]++;
        time[0] %= 60;

        if(time[1] >= 60)
        {
            time[2]++;
            time[1] %= 60;
        }
    }

    ui->processTime->display(processTimeText());
}

void Viewer::updateRedTime()
{
    redTime[0]--;
    if(redTime[0] < 0)
    {
        redTime[1]--;
        redTime[0] += 60;
    }

    if(!redTime[0] && redTime[1] <= 0)
    {
        GameManger::gameStatus = GameSataus::BlackWin;
        gameOver();
    }
    ui->redTime->display(sideTimerText(0));
}

void Viewer::updateBlackTime()
{
    blackTime[0]--;
    if(blackTime[0] < 0)
    {
        blackTime[1]--;
        blackTime[0] += 60;
    }

    if(!blackTime[0] && blackTime[1] <= 0)
    {
        GameManger::gameStatus = GameSataus::RedWin;
        gameOver();
    }
    ui->blackTime->display(sideTimerText(1));
}

void Viewer::limitTimeManage()
{
    if(!GameManger::currentSide) //Red
    {
        redTimer->stop();
        blackTimer->start(1000);
    }
    else //Black
    {
        blackTimer->stop();
        redTimer->start(1000);
    }
}

void Viewer::initTime()
{
    time[0] = time[1] = time[2] = 0;
    redTime[0] = blackTime[0] = LIMITSEC;
    redTime[1] = blackTime[1] = LIMITMIN;
}
