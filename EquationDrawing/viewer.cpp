#include "viewer.h"
#include "ui_viewer.h"

using namespace std;

string color[15] = {
"#F71204", "#1846C1", "#66769E", "#AE6DAE", "#5E191C",
"#A92E98", "#24824C", "#EC2954", "#9EA44C", "#251D63",
"#F9230E", "#6D207A", "#483F3F", "#D63DC0", "#2ACCA7"
};

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    ui->setupUi(this);
    setMaximumSize(1600,950);
    setUpPlot();
    setUpFuncArea();
    setUpVarArea();
    setWindowTitle("Equation Drawer");
    setWindowIcon(QIcon(":/main.ico"));
    funcQuan = 0;
    qDebug() << "hi";
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::setUpPlot()
{
    plot = ui->plot;
    plot->xAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setTickLabels(false);

    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
    QFont font = ui->plot->font();
    font.setPixelSize(20);
    plot->xAxis->setTickLabelFont(font);
    plot->yAxis->setTickLabelFont(font);
    plot->xAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0,100), 3, Qt::SolidLine));
    plot->yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0,100), 3, Qt::SolidLine));
    plot->xAxis->grid()->setPen(QPen(QColor(0,0,0,100), 2, Qt::DotLine));
    plot->yAxis->grid()->setPen(QPen(QColor(0,0,0,100), 2, Qt::DotLine));
    plot->xAxis->grid()->setSubGridPen(QPen(QColor(0,0,0,100), 1, Qt::DotLine));
    plot->yAxis->grid()->setSubGridPen(QPen(QColor(0,0,0,100), 1, Qt::DotLine));
    plot->xAxis->grid()->setSubGridVisible(true);
    plot->yAxis->grid()->setSubGridVisible(true);

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void Viewer::setUpFuncArea()
{
    func[0] = ui->func01, func[1] = ui->func02, func[2] = ui->func03;
    func[3] = ui->func04, func[4] = ui->func05, func[5] = ui->func06;
    func[6] = ui->func07, func[7] = ui->func08, func[8] = ui->func09;
    func[9] = ui->func10, func[10] = ui->func11, func[11] = ui->func12;
    func[12] = ui->func13, func[13] = ui->func14, func[14] = ui->func15;

    hide[0] = ui->hide1, hide[1] = ui->hide2, hide[2] = ui->hide3;
    hide[3] = ui->hide4, hide[4] = ui->hide5, hide[5] = ui->hide6;
    hide[6] = ui->hide7, hide[7] = ui->hide8, hide[8] = ui->hide9;
    hide[9] = ui->hide10, hide[10] = ui->hide11, hide[11] = ui->hide12;
    hide[12] = ui->hide13, hide[13] = ui->hide14, hide[14] = ui->hide15;

    del[0] = ui->delete1, del[1] = ui->delete2, del[2] = ui->delete3;
    del[3] = ui->delete4, del[4] = ui->delete5, del[5] = ui->delete6;
    del[6] = ui->delete7, del[7] = ui->delete8, del[8] = ui->delete9;
    del[9] = ui->delete10, del[10] = ui->delete11, del[11] = ui->delete12;
    del[12] = ui->delete13, del[13] = ui->delete14, del[14] = ui->delete15;

    funcText[0] = ui->funcText1, funcText[1] = ui->funcText2, funcText[2] = ui->funcText3;
    funcText[3] = ui->funcText4, funcText[4] = ui->funcText5, funcText[5] = ui->funcText6;
    funcText[6] = ui->funcText7, funcText[7] = ui->funcText8, funcText[8] = ui->funcText9;
    funcText[9] = ui->funcText10, funcText[10] = ui->funcText11, funcText[11] = ui->funcText12;
    funcText[12] = ui->funcText13, funcText[13] = ui->funcText14, funcText[14] = ui->funcText15;

    funcColor[0] = ui->funcColor1, funcColor[1] = ui->funcColor2, funcColor[2] = ui->funcColor3;
    funcColor[3] = ui->funcColor4, funcColor[4] = ui->funcColor5, funcColor[5] = ui->funcColor6;
    funcColor[6] = ui->funcColor7, funcColor[7] = ui->funcColor8, funcColor[8] = ui->funcColor9;
    funcColor[9] = ui->funcColor10, funcColor[10] = ui->funcColor11, funcColor[11] = ui->funcColor12;
    funcColor[12] = ui->funcColor13, funcColor[13] = ui->funcColor14, funcColor[14] = ui->funcColor15;

    for(int i = 0; i < 15; i++)
    {
        func[i]->installEventFilter(this);
        hide[i]->setVisible(false);
        del[i]->setVisible(false);
        func[i]->setVisible(false);
        isFuncHide[i] = true;
        colorUnused.push(color[i]);
    }
}

void Viewer::setUpVarArea()
{
    warnText[0] = ui->warnText1, warnText[1] = ui->warnText2, warnText[2] = ui->warnText3;
    warnText[3] = ui->warnText4, warnText[4] = ui->warnText5, warnText[5] = ui->warnText6, warnText[6] = ui->warnText7;
    varText[0] = ui->varText1, varText[1] = ui->varText2, varText[2] = ui->varText3;
    varText[3] = ui->varText4, varText[4] = ui->varText5, varText[5] = ui->varText6, varText[6] = ui->varText7;

    for(int i = 0; i < 7; i++)
    {
        warnText[i]->setStyleSheet("color: rgb(255,0,0); border: 1px solid red;");
        warnText[i]->setVisible(false);
    }
}

bool Viewer::formatText(int index, bool mode)
{
    QString temp = !mode ? funcText[index]->toPlainText() : varText[index]->toPlainText();
    if(!mode)
    {
        for(auto &it:temp)
        {
            if(it == '\n')
            {
                temp = temp.simplified();
                funcText[index]->setText(temp);
                function[index].funcText = temp.toStdString();
                return true;
            }
        }
    }

    else
    {
        for(auto &it:temp)
        {
            if(it == '\n')
            {
                temp = temp.simplified();
                varText[index]->setText(temp);
                return true;
            }
        }
    }

    return false;
}

bool Viewer::eventFilter(QObject *obj, QEvent *event)
{
        for(int i = 0; i < 15; i++)
        {
            if(obj == func[i])
            {
                if(event->type() == QEvent::Enter)
                {
                    hide[i]->setVisible(true);
                    del[i]->setVisible(true);
                    funcText[i]->setFrameShape(QFrame::Box);
                    return true;
                }
                else if(event->type() == QEvent::Leave)
                {
                    hide[i]->setVisible(false);
                    del[i]->setVisible(false);
                    funcText[i]->setFrameShape(QFrame::NoFrame);
                    return true;
                }
                else
                    return false;
            }
        }

        return QMainWindow::eventFilter(obj,event);
}

void Viewer::on_creatFunc_clicked()
{
    if(funcQuan <= 0 || funcQuan > 15)
        funcQuan = 0;
    if(funcQuan == 15)
        return;
    else
    {
        funcQuan++;
        function.push_back(Function(function.size(), colorUnused.top()));

        QCPCurve* tCurve = new QCPCurve(plot->xAxis, plot->yAxis);
        curve.push_back(tCurve);
        (*curve.rbegin())->setPen( QPen( QColor( function[funcQuan - 1].funcColor.c_str() ),2 ) );

        if(colorUnused.size())
            colorUnused.pop();

        string temp = "background-color:";
        temp += function[funcQuan - 1].funcColor;
        temp += ";";
        funcColor[funcQuan - 1]->setStyleSheet(QString::fromStdString(temp));

        func[function.size() - 1]->setVisible(true);
        isFuncHide[function.size() - 1] = false;
    }
}
