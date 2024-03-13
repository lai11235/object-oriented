#pragma once
#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <utility>
#include <exception>
#include "MyVector.h"
#include "Union.h"
using namespace std;

typedef pair<double, double> Coord;
typedef string Operator;
typedef string Variable;
typedef Union<double, Variable, Operator> Operand;
enum {
    NONE, t_DOUBLE, VARIABLE, OPERATOR
};


template<typename T>
T binaryOperate(T data1, Operator op, T data2);

template<typename T>
T unaryOperate(Operator op, T data);

class Expression : public MyVector<Operand> {
protected:
	Expression toPostfix(void);

public:
    static map<Operator, int> operatorPriority;

	Expression(string expStr = "");

	void substitute(Variable var, Expression exp);

	void substitute(Variable var, double val);
	
	double eval(void);

	double subVarAndEval(Variable subVar, double withVal);

	vector<Coord> getCoordinates(Variable var, double start, double end, double jump);

	friend ostream& operator<< (ostream& strm, Expression exp) {
		for (auto& op : exp) {
			strm << op << ' ';
		}
		return strm;
	};

	void wrapByBrackets(void);

	void operator-= (Expression exp);

	void operator*= (Expression exp);

	void operator/= (Expression exp);
};
typedef pair<Variable, Expression> VarEquation;
VarEquation toVarEquation(string equationStr);





