#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <QDebug>
#include <QVector>
#include <vector>
#include "VariableSet.h"

class Function
{
    public:
        vector<Coord> coord;
        QVector<double> x, y;
        std::string funcText;
        std::string funcColor;
        int index;

        Function(int _index = 0, std::string color = "", std::string str = "")
        {
            index = _index;
            funcText = str;
            funcColor = color;
        }
};

#endif // FUNCTION_H
