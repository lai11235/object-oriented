#include "Expression.h"

class P2_Of_Y {
private:
	Expression terms[2];

public:
	P2_Of_Y(Expression term0, Expression term1) {
		terms[0] = term0;
		terms[1] = term1;
	}

	P2_Of_Y(string polyStr) {
		for (auto iter = polyStr.begin(); iter != polyStr.end(); ) {
			if (*iter == ' ') {
				iter = polyStr.erase(iter);
			}
			else {
				iter++;
			}
		}

		int yPos = polyStr.find('y');
		if (yPos == string::npos) {
            logic_error ex("\"Y\" can not be found.");
            throw ex;
		}
		else if (yPos == 0) {
			terms[1] = Expression("1");
		}
		else if (polyStr[yPos - 1] == '*') {
			terms[1] = Expression(polyStr.substr(0, yPos - 1));
		}
		else {
			terms[1] = Expression(polyStr.substr(0, yPos));
		}

		int plusPos = polyStr.find('+', yPos + 1);
		if (plusPos == string::npos) {
			terms[0] = Expression("0");
		}
		else {
			terms[0] = polyStr.substr(plusPos + 1);
		}
	}

	Expression& term0(void) {
		return terms[0];
	}
	Expression& term1(void) {
		return terms[1];
	}
};

Expression toFunctionOfX(string equationStr) {
    int equalSymbolIndex = equationStr.find('=');
    if (equalSymbolIndex == string::npos) {
        logic_error ex("\"=\" cannot be found.\n");
        throw ex;
    }
    P2_Of_Y polyOfY = equationStr.substr(0, equalSymbolIndex);
    Expression expOfX = equationStr.substr(equalSymbolIndex + 1, string::npos);
    expOfX -= polyOfY.term0();
    expOfX /= polyOfY.term1();
    for (auto& op : expOfX) {
        if (op.type() == VARIABLE) {
            if (op.t2() == "y") {
                logic_error ex("Variable \"y\" cannot be in the right expression.\n");
                throw ex;
            }
        }
    }
    return expOfX;
}
