#include "viewer.h"

void Viewer::clickHide(int index)
{
    if(!isFuncHide[index])
    {
        funcColor[index]->setText("X");
        curve[index]->setVisible(false);
        isFuncHide[index] = true;
        plot->replot();
    }
    else if(isFuncHide[index])
    {
        funcColor[index]->setText("");
        curve[index]->setVisible(true);
        isFuncHide[index] = false;
        plot->replot();
    }
}

void Viewer::on_hide1_clicked()
{
    clickHide(0);
}

void Viewer::on_hide2_clicked()
{
    clickHide(1);
}

void Viewer::on_hide3_clicked()
{
    clickHide(2);
}

void Viewer::on_hide4_clicked()
{
    clickHide(3);
}

void Viewer::on_hide5_clicked()
{
    clickHide(4);
}

void Viewer::on_hide6_clicked()
{
    clickHide(5);
}

void Viewer::on_hide7_clicked()
{
    clickHide(6);
}

void Viewer::on_hide8_clicked()
{
    clickHide(7);
}

void Viewer::on_hide9_clicked()
{
    clickHide(8);
}

void Viewer::on_hide10_clicked()
{
    clickHide(9);
}

void Viewer::on_hide11_clicked()
{
    clickHide(10);
}

void Viewer::on_hide12_clicked()
{
    clickHide(11);
}

void Viewer::on_hide13_clicked()
{
    clickHide(12);
}

void Viewer::on_hide14_clicked()
{
    clickHide(13);
}

void Viewer::on_hide15_clicked()
{
    clickHide(14);
}
