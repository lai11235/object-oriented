#include "viewer.h"
#include "Expression.h"
#include "P2_Of_Y.h"

void Viewer::addGraph(int index)
{
    try
    {
        vector<Coord> coord;
        function[index].x.clear(), function[index].y.clear();

        int pos = function[index].funcText.find('=');
        string tfuncText = function[index].funcText;
        bool flag = false, flag2 = false;

        if(pos != string::npos)
        {
            int textSize = 0;
            int ySize = 0;
            int xSize = 0;
            for(int i = 0; i < pos; i++)
            {
               if(tfuncText[i] == ' ')
                   continue;


               if(tfuncText[i] == 'x')
                   xSize++;
               else if(tfuncText[i] == 'y')
                   ySize++;
               textSize++;
            }

            if(textSize == 1)
                flag = true;
            if(!flag && !xSize && ySize)
                flag2 = true;
        }

        if(flag2)
        {
            string t = tfuncText.substr(0, pos);
            string t2 = tfuncText.substr(pos + 1);
            for(int i = t.size() - 1; i >= 0; i--)
            {
                if(t[i] != ' ')
                    break;
                t.erase(i);
            }
            for(int i = 0; i < t2.size(); i++)
            {
                if(t2[i] != ' ')
                    t2 = t2.substr(i);
            }
            tfuncText = t2;
            tfuncText += "=";
            tfuncText += t;
            flag = true;
        }

        if(flag & tfuncText[0] == 'y')
        {
            VarEquation varEquation = toVarEquation(tfuncText);
            Expression exp(varEquation.second);
            exp = varSet.subExpWithThisSet(exp);
            coord = exp.getCoordinates("x", -1000, 1000, 0.1);
            for(auto &it: coord)
            {
                function[index].x.push_back(it.first);
                function[index].y.push_back(it.second);
            }
        }

        else if(flag & tfuncText[0] == 'x')
        {
            VarEquation varEquation = toVarEquation(tfuncText);
            Expression exp(varEquation.second);
            exp = varSet.subExpWithThisSet(exp);
            coord = exp.getCoordinates("y", -1000, 1000, 0.1);
            for(auto &it: coord)
            {
                function[index].y.push_back(it.first);
                function[index].x.push_back(it.second);
            }
        }

        else
        {
            Expression exp = toFunctionOfX(tfuncText);
            exp = varSet.subExpWithThisSet(exp);
            coord = exp.getCoordinates("x", -1000, 1000, 0.1);
            for(auto &it: coord)
            {
                function[index].x.push_back(it.first);
                function[index].y.push_back(it.second);
            }
        }

        if(funcColor[index]->text() == "E")
            funcColor[index]->setText("");
        curve[index]->data()->clear();
        curve[index]->addData(function[index].x , function[index].y);
        plot->replot();
    }
    catch (exception &e)
    {
         curve[index]->data()->clear();
        plot->replot();
        funcColor[index]->setText("E");
    }
}

void Viewer::on_funcText1_textChanged()
{
    if(formatText(0, 0))
        addGraph(0);
}

void Viewer::on_funcText2_textChanged()
{
    if(formatText(1, 0))
        addGraph(1);
}

void Viewer::on_funcText3_textChanged()
{
    if(formatText(2, 0))
        addGraph(2);
}

void Viewer::on_funcText4_textChanged()
{
    if(formatText(3, 0))
        addGraph(3);
}

void Viewer::on_funcText5_textChanged()
{
    if(formatText(4, 0))
        addGraph(4);
}

void Viewer::on_funcText6_textChanged()
{
    if(formatText(5, 0))
        addGraph(5);
}

void Viewer::on_funcText7_textChanged()
{
    if(formatText(6, 0))
        addGraph(6);
}

void Viewer::on_funcText8_textChanged()
{
    if(formatText(7, 0))
        addGraph(7);
}

void Viewer::on_funcText9_textChanged()
{
    if(formatText(8, 0))
        addGraph(8);
}

void Viewer::on_funcText10_textChanged()
{
    if(formatText(9, 0))
        addGraph(9);
}

void Viewer::on_funcText11_textChanged()
{
    if(formatText(10, 0))
        addGraph(10);
}

void Viewer::on_funcText12_textChanged()
{
    if(formatText(11, 0))
        addGraph(11);
}

void Viewer::on_funcText13_textChanged()
{
    if(formatText(12, 0))
        addGraph(12);
}

void Viewer::on_funcText14_textChanged()
{
    if(formatText(13, 0))
        addGraph(13);
}

void Viewer::on_funcText15_textChanged()
{
    if(formatText(14, 0))
        addGraph(14);
}
