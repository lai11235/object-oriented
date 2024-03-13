#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QFrame>
#include <QTextEdit>
#include <QVector>
#include <QString>
#include <vector>
#include <string>
#include <stack>

#include "qcustomplot.h"
#include "function.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

class Viewer : public QMainWindow
{
    Q_OBJECT

    public:
        Viewer(QWidget *parent = nullptr);
        ~Viewer();
        void setUpPlot();
        void setUpFuncArea();
        void setUpVarArea();

    private:
        Ui::Viewer *ui;
    private slots:
        void on_hide1_clicked();
        void on_hide2_clicked();
        void on_hide3_clicked();
        void on_hide4_clicked();
        void on_hide5_clicked();
        void on_hide6_clicked();
        void on_hide7_clicked();
        void on_hide8_clicked();
        void on_hide9_clicked();
        void on_hide10_clicked();
        void on_hide11_clicked();
        void on_hide12_clicked();
        void on_hide13_clicked();
        void on_hide14_clicked();
        void on_hide15_clicked();

        void on_delete1_clicked();
        void on_delete2_clicked();
        void on_delete3_clicked();
        void on_delete4_clicked();
        void on_delete5_clicked();
        void on_delete6_clicked();
        void on_delete7_clicked();
        void on_delete8_clicked();
        void on_delete9_clicked();
        void on_delete10_clicked();
        void on_delete11_clicked();
        void on_delete12_clicked();
        void on_delete13_clicked();
        void on_delete14_clicked();
        void on_delete15_clicked();

        void on_funcText1_textChanged();
        void on_funcText2_textChanged();
        void on_funcText3_textChanged();
        void on_funcText4_textChanged();
        void on_funcText5_textChanged();
        void on_funcText6_textChanged();
        void on_funcText7_textChanged();
        void on_funcText8_textChanged();
        void on_funcText9_textChanged();
        void on_funcText10_textChanged();
        void on_funcText11_textChanged();
        void on_funcText12_textChanged();
        void on_funcText13_textChanged();
        void on_funcText14_textChanged();
        void on_funcText15_textChanged();

        void on_varText1_textChanged();
        void on_varText2_textChanged();
        void on_varText3_textChanged();
        void on_varText4_textChanged();
        void on_varText5_textChanged();
        void on_varText6_textChanged();
        void on_varText7_textChanged();

        void on_creatFunc_clicked();
        void on_clear1_clicked();
        void on_clear2_clicked();
        void on_clear3_clicked();
        void on_clear4_clicked();
        void on_clear5_clicked();
        void on_clear6_clicked();
        void on_clear7_clicked();

protected:
        QCustomPlot *plot;
        QFrame* func[15];
        QPushButton* del[15];
        QPushButton* hide[15];
        QTextEdit* funcText[15];
        QLabel* funcColor[15];
        QTextEdit* varText[7];
        QTextBrowser* warnText[7];
        bool varError[5];
        VariableSet varSet;

        std::vector<QCPCurve*> curve;
        std::vector<Function> function;
        std::stack<std::string> colorUnused;
        bool isFuncHide[15];
        int funcQuan;

        bool eventFilter(QObject *obj, QEvent *event);
        void clickDel(int index);
        void clickHide(int index);
        void addGraph(int index);
        void setVar(int index);
        void clearVar(int index);
        bool formatText(int index, bool mode);// If read the '\n' in text, it will return true regarding as a signal of input finished
};
#endif // VIEWER_H
