#include "viewer.h"

void Viewer::clearVar(int index)
{
    if(!varError[index])
    {
        string temp = varText[index]->toPlainText().toStdString();
        int pos = temp.find("=");
        if(pos != string::npos)
        {
            string target = "";
            for(int i = 0; i < pos; i++) //Retrive the variable name
                if(temp[i] != ' ')
                    target += temp[i];

            varSet.eraseVar(target);

            for(int i = 0; i < curve.size(); i++)
            {
                if(!function[i].funcText.size())
                    continue;
                addGraph(i);
            }
        }
    }

    varError[index] = false;
    varText[index]->setText("");
    warnText[index]->setText("");
    warnText[index]->setVisible(false);
}

void Viewer::on_clear1_clicked()
{
    if(varText[0]->toPlainText().size())
        clearVar(0);
}

void Viewer::on_clear2_clicked()
{
    if(varText[1]->toPlainText().size())
        clearVar(1);
}

void Viewer::on_clear3_clicked()
{
    if(varText[2]->toPlainText().size())
        clearVar(2);
}

void Viewer::on_clear4_clicked()
{
    if(varText[3]->toPlainText().size())
        clearVar(3);
}

void Viewer::on_clear5_clicked()
{
    if(varText[4]->toPlainText().size())
        clearVar(4);
}

void Viewer::on_clear6_clicked()
{
    if(varText[5]->toPlainText().size())
        clearVar(5);
}

void Viewer::on_clear7_clicked()
{
    if(varText[6]->toPlainText().size())
        clearVar(6);
}
