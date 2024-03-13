#include "viewer.h"

void Viewer::setVar(int index)
{
    string temp = varText[index]->toPlainText().toStdString();
    try{
        varSet += temp;
        warnText[index]->setText("");
        warnText[index]->setVisible(false);
        for(int i = 0; i < curve.size(); i++)
        {
            if(!function[i].funcText.size())
                continue;
            addGraph(i);
        }
    }
    catch(exception &e)
    {
        QString temp = QString::fromStdString(e.what());
        temp.simplified();
        warnText[index]->setVisible(true);
        warnText[index]->setText(temp);
    }
}

void Viewer::on_varText1_textChanged()
{
    if(formatText(0, 1))
        setVar(0);
}

void Viewer::on_varText2_textChanged()
{
    if(formatText(1, 1))
        setVar(1);
}

void Viewer::on_varText3_textChanged()
{
    if(formatText(2, 1))
        setVar(2);
}

void Viewer::on_varText4_textChanged()
{
    if(formatText(3, 1))
        setVar(3);
}

void Viewer::on_varText5_textChanged()
{
    if(formatText(4, 1))
        setVar(4);
}

void Viewer::on_varText6_textChanged()
{
    if(formatText(5, 1))
        setVar(5);
}

void Viewer::on_varText7_textChanged()
{
    if(formatText(6, 1))
        setVar(6);
}
