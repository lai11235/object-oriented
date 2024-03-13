#include "VariableSet.h"
#include <QtDebug>

void VariableSet::add(Variable var, Expression exp) {
	if (varEquations.count(var)) {
        logic_error ex(("Variable \"" + var + "\" have joined this set.\n").c_str());
        throw ex;
	}
	for (auto& equation : varEquations) {
		if (usedVar[equation.first].count(var)) {
            logic_error ex(("Variable \"" + var + "\" failed to join. Circular difinition may occured.\n").c_str());
            throw ex;
		}
	}
	for (auto& equation : varEquations) {
		equation.second.substitute(var, exp);
		usedVar[equation.first].insert(var);
	}
	for (auto& equation : varEquations) {
		usedVar[var].insert(equation.first);
		exp.substitute(equation.first, equation.second);
	}
	varEquations[var] = exp;
}

void VariableSet::clear()
{
    varEquations.clear();
    usedVar.clear();
}

void VariableSet::eraseVar(string target)
{
    varEquations.erase(target);
    usedVar.erase(target);
}

void VariableSet::operator+= (string equationStr) {
	auto varEquation = toVarEquation(equationStr);
	add(varEquation.first, varEquation.second);
}

Expression VariableSet::subExpWithThisSet(Expression exp) {
	Expression result = exp;
	for (auto& equation : varEquations) {
		result.substitute(equation.first, equation.second);
	}
	return result;
}
