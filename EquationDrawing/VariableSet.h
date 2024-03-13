#ifndef VARIABLESET_H
#define VARIABLESET_H

#include <iostream>
#include <set>
#include <map>
#include <exception>
#include "Expression.h"

class VariableSet {

friend class Expression;

protected:
	map<Variable, Expression> varEquations;
	map<Variable, set<Variable>> usedVar;

public:
	void add(Variable var, Expression exp);

    void clear();

    void eraseVar(string target);

	void operator+= (string equationStr);

	Expression subExpWithThisSet(Expression exp);

	friend ostream& operator<< (ostream& strm, VariableSet& varSet) {
		for (auto& equation : varSet.varEquations) {
			cout << equation.first << " = " << equation.second << endl;
		}
		return strm;
	}
};

#endif
