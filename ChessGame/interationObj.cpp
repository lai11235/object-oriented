#include "viewer.h"
#include "QFileDialog"

#include <sstream>

void Viewer::on_startButton_clicked()
{
    gameMode();
}

void Viewer::on_exit_clicked()
{
    mode = 0;
    gameStop();
}

void Viewer::on_loadRecord_clicked()
{
    QFileDialog myFileDialog (this);

    /**Open the window to select the record(*.txt)**/
    QString itemPath = myFileDialog.getOpenFileName (this, tr ("Open File"), QDir::currentPath (), tr ("All txt files (*.txt)"));
    string logpath = itemPath.toStdString();

    ifstream selectLog;
    selectLog.open(logpath, ios::in);

    if(selectLog.is_open())
    {
        GameManger::gameStatus = GameSataus::Loading;

        string inform; //Store the line in file temperately
        ChessType selectChess; //The chess in the record each line
        int x1, y1, x2, y2; //The position of selectChess move
        int side = 0; //0: Red, 1: Black
        stringstream ss; //Seperating the line
        string temp; //Store section flow from ss
        bool isReadTime = false;

        while(getline(selectLog, inform))
        {
            if(!inform.size())
                break;

            /**Time read**/
            if(inform[0] == '&') // the symbol '&' represent the time text is previous record
                continue;
            if(inform[0] == '@') //read the time text
            {
                for(int i = 1, j = 2; i <= 7; i+= 3, j--) //Reading total playing time
                {
                    time[j] = inform[i] - '0';
                    time[j] = (time[j] << 1) + (time[j] << 3) + (inform[i + 1] - '0');
                }

                if(inform.size() > 9) // If the mode is limit time then the time text will excess 9
                {
                    for(int i = 10, j = 1; i <= 13; i+=3, j--) //Red time
                    {
                        redTime[j] = inform[i] - '0';
                        redTime[j] = (redTime[j] << 1) + (redTime[j] << 3) + (inform[i + 1] - '0');
                    }
                    for(int i = 16, j = 1; i <= 19; i+=3, j--) //Black time
                    {
                        blackTime[j] = inform[i] - '0';
                        blackTime[j] = (blackTime[j] << 1) + (blackTime[j] << 3) + (inform[i + 1] - '0');
                    }
                    mode = 1;
                }
                isReadTime = true;
                break;
            }

            ss << inform;

            for(int i = 0; i < 9; i++) // Seperating the log
            {
                ss >> temp;

                if(i == 0 || i == 1 || i == 2 || i == 6)
                    continue;

                if(i == 3) //ChessType(String)
                    selectChess = strToType(temp, side);

                else if(i == 4) //Start point
                    x1 = temp[1] - '0';
                else if(i == 5)
                    y1 = temp[0] - '0';

                else if(i == 7) //Destination
                    x2 = temp[1] - '0';
                else if(i == 8)
                    y2 = temp[0] - '0';
            }

            if(selectChess == ChessType::bGeneral)
                GameManger::bGeneralPos = {x2, y2};
            else if(selectChess == ChessType::rGeneral)
                GameManger::rGeneralPos = {x2, y2};

            followLog({x1, y1}, {x2, y2}, selectChess);
            side++, side %= 2;
            ss.str(""),  ss.clear();
        }

        /**Record the file name is opened**/
        size_t pos = logpath.find(".txt");
        while(logpath[pos] != '/')
            pos--;
        logpath = logpath.substr(pos + 1);
        strcpy_s(GameManger::logName, logpath.size() + 1,logpath.c_str());

        /**To mark the time text in logFile is read**/
        if(isReadTime)
        {
            fstream file;
            file.open(GameManger::logName, ios::out | ios::in);
            if(mode)
                file.seekp(-23L, ios::end);
            else
                file.seekp(-11L, ios::end);
            file << '&';
            file.close();
        }

        GameManger::currentSide = side ? 1 : 0;

        this->repaint();
        gameStart();
    }

    selectLog.close();
}

void Viewer::on_normalMode_clicked()
{
    mode = 0;
    gameStart();
}

void Viewer::on_limitMode_clicked()
{
    mode = 1;
    gameStart();
}

void Viewer::on_oneMore_clicked()
{
    gameMode();
}

void Viewer::on_returnMenu_clicked()
{
    Menu();
}

void Viewer::on_blackGiveUp_clicked()
{
    if(!GameManger::currentSide)
        return;
    GameManger::gameStatus = GameSataus::RedWin;
    gameOver();
}

void Viewer::on_redGiveUp_clicked()
{
    if(GameManger::currentSide)
        return;
    GameManger::gameStatus = GameSataus::BlackWin;
    gameOver();
}
/**The menu bar**/
void Viewer::on_actionExit_triggered()
{
    gameStop();
}

void Viewer::on_actionSave_triggered()
{
    gameSave();
}

void Viewer::closeEvent(QCloseEvent *)
{
    if(GameManger::gameStatus == GameSataus::Playing)
    {
        /**Recording the time into logFile**/
        logFile << "@" << processTimeText().toStdString();
        if(mode) //Limit time mode
        {
            logFile << " " << sideTimerText(0).toStdString() << " ";
            logFile << sideTimerText(1).toStdString();
        }
        logFile << "\n";
        logFile.close();
    }
}
