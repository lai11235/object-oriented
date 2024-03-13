#include "viewer.h"

void Viewer::clickDel(int index)
{
    if(!funcQuan)
        return;

    plot->removePlottable(index);
    plot->replot();

    colorUnused.push(function[index].funcColor);
    function.erase(function.begin() + index);

    funcColor[index]->setText("");
    for(int i = index + 1; i < function.size(); i++)
    {
        if(funcColor[i]->text() != "")
        {
            if(i)
            {
                funcColor[i - 1]->setText(funcColor[i]->text());
                funcColor[i]->setText("");
            }
        }
    }

    curve.erase(curve.begin() + index);

    for(int i = 0; i < function.size(); i++)
    {
        function[i].index = i;

        string temp = "background-color:";
        temp += function[i].funcColor;
        temp += ";";
        funcColor[i]->setStyleSheet(QString::fromStdString(temp));
        funcText[i]->setText(QString::fromStdString(function[i].funcText));
    }

    funcQuan--;
    funcText[funcQuan]->setText("");
    func[funcQuan]->setVisible(false);
    isFuncHide[funcQuan] = true;
}

void Viewer::on_delete1_clicked()
{
    clickDel(0);
}

void Viewer::on_delete2_clicked()
{
    clickDel(1);
}

void Viewer::on_delete3_clicked()
{
    clickDel(2);
}

void Viewer::on_delete4_clicked()
{
    clickDel(3);
}

void Viewer::on_delete5_clicked()
{
    clickDel(4);
}

void Viewer::on_delete6_clicked()
{
    clickDel(5);
}

void Viewer::on_delete7_clicked()
{
    clickDel(6);
}

void Viewer::on_delete8_clicked()
{
    clickDel(7);
}

void Viewer::on_delete9_clicked()
{
    clickDel(8);
}

void Viewer::on_delete10_clicked()
{
    clickDel(9);
}

void Viewer::on_delete11_clicked()
{
    clickDel(10);
}

void Viewer::on_delete12_clicked()
{
    clickDel(11);
}

void Viewer::on_delete13_clicked()
{
    clickDel(12);
}

void Viewer::on_delete14_clicked()
{
    clickDel(13);
}

void Viewer::on_delete15_clicked()
{
    clickDel(14);
}
