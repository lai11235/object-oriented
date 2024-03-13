#include "Expression.h"

map<Operator, int> Expression::operatorPriority = {
    { Operator("("), 0 },
    { Operator(")"), 0 },
    { Operator("+"), 1 },
    { Operator("-"), 1 },
    { Operator("*"), 2 },
    { Operator("/"), 2 },
    { Operator("^"), 3 },
    { Operator("cos"), 4 },
    { Operator("sin"), 4 },
    { Operator("tan"), 4 },
    { Operator("#"), 5 }
};
set<string> binaryOperatorSet{ "+", "-", "*", "/", "^" };
set<string> unaryOepratorSet{ "#", "sin", "cos", "tan" };

Expression::Expression(string expStr) {
	stringstream ss;
	ss << expStr;

	while (ss.peek() != -1) {
		// Encountering a digit, catch a double number.
		if (isdigit(ss.peek()) || ss.peek() == '.') {
			string numStr;
			while (isdigit(ss.peek()) || ss.peek() == '.') {
				numStr.push_back(ss.get());
			}
			Operand op;
			op.t1() = stod(numStr);
			this->push_back(op);
		}
		// Encounter an operator character.
		else if (operatorPriority.count(Operator(1, ss.peek()))) {
			Operand op;
			op.t3() = Operator(1, ss.get());
			this->push_back(op);
		}
		// Encountering an alphabet, catch the whole word and process it.
		else if (isalpha(ss.peek()) || ss.peek() == '_') {
			Variable var;
			while (isalpha(ss.peek()) || ss.peek() == '_' || isdigit(ss.peek())) {
				var.push_back(ss.get());
			}
			// Figure out whether the word is a variable or operator.
			Operand op;
			if (operatorPriority.count(var)) {
				op.t3() = var;
			}
			else {
				op.t2() = var;
			}
			this->push_back(op);
		}
		// Encountering an exception, skip it.
		else {
			ss.get();
		}
	}

	// turn unary operator "-" into "#"
	auto& self = *this;
	for (int i = 0; i < self.size(); i++) {
		if (self[i].type() == OPERATOR && self[i].t3() == "-") {
			if (i == 0) {
				self[i].t3() = "#";
			}
            else if (self[i - 1].type() == OPERATOR && self[i - 1].t3() != ")") {
				self[i].t3() = "#";
			}
		}
	}
}

void Expression::substitute(Variable var, Expression exp) {
	auto& self = *this;

	// wrap the variable with brackets.
	Operand leftBracket, rightBracket;
	leftBracket.t3() = "(";
	rightBracket.t3() = ")";

	for (int i = 0; i < self.size(); i++) {
		if (self[i].type() == 2 && self[i].t2() == var) {
			self.erase(self.begin() + i);
			self.insert(self.begin() + i, leftBracket);
			self.insert(self.begin() + i + 1, exp.begin(), exp.end());
			self.insert(self.begin() + i + 1 + exp.size(), rightBracket);
			i += exp.size();
		}
	}
}

void Expression::substitute(Variable var, double val) {
	for (auto& op : *this) {
		if (op.type() == VARIABLE) {
			if (op.t2() == var)
				op.t1() = val;
		}
	}
}

Expression Expression::toPostfix(void) {
	Expression postfix;
	stack<Operand> opStack;

	for (auto& op : *this) {

        if (op.type() == t_DOUBLE || op.type() == VARIABLE) {
			postfix += op;
		}

		else {
			if (op.t3() == "(") {
				opStack.push(op);
			}

			else if (op.t3() == ")") {
				while (opStack.top().t3() != "(") {
					postfix += opStack.top();
					opStack.pop();
					if (opStack.empty()) {
                        logic_error ex("Brackets is not in pair.\n");
                        throw ex;
					}
				}
				opStack.pop();
			}

			else {
				while (!opStack.empty() && operatorPriority[opStack.top().t3()] >= operatorPriority[op.t3()]) {
					postfix += opStack.top();
					opStack.pop();
				}
				opStack.push(op);
			}
		}
	}

	while (!opStack.empty()) {
		if (opStack.top().t3() == "(" || opStack.top().t3() == ")") {
            logic_error ex("Brackets is not in pair.\n");
            throw ex;
		}
		else {
			postfix += opStack.top();
			opStack.pop();
		}
	}
	return postfix;
}

double Expression::eval(void) {
	stack<double> ansStack;
	Expression postfix = this->toPostfix();
	for (auto& op : postfix) {
        if (op.type() == t_DOUBLE) {
			ansStack.push(op.t1());
		}
		if (op.type() == VARIABLE) {
            logic_error ex(("Variable \"" + op.t2() + "\" is not defined.\n").c_str());
            throw ex;
		}
		if (op.type() == OPERATOR) {
			if (binaryOperatorSet.count(op.t3())) {
				if (ansStack.empty()) {
                    logic_error ex(("Operator \"" + op.t3() + "\" failed to operate.\n").c_str());
                    throw ex;
				}
				auto num2 = ansStack.top();
				ansStack.pop();
                if (ansStack.empty()) {
                    logic_error ex(("Operator \"" + op.t3() + "\" failed to operate.\n").c_str());
                    throw ex;
				}
				auto num1 = ansStack.top();
				ansStack.pop();
				ansStack.push(binaryOperate(num1, op.t3(), num2));
			}
			else if (unaryOepratorSet.count(op.t3())) {
				if (ansStack.empty()) {
                    logic_error ex(("Operator \"" + op.t3() + "\" failed to operate.\n").c_str());
                    throw ex;
				}
				auto num = ansStack.top();
				ansStack.pop();
				ansStack.push(unaryOperate(op.t3(), num));
			}
		}
	}
	return ansStack.top();
}

double Expression::subVarAndEval(Variable subVar, double withVal) {
	Expression exp = *this;
	exp.substitute(subVar, withVal);
	return exp.eval();
}

vector<Coord> Expression::getCoordinates(Variable var, double start, double end, double jump) {
	vector<Coord> coords;
	for (double now = start; now <= end; now += jump) {
		coords.push_back({ now, this->subVarAndEval(var, now) });
	}
	return coords;
}

void Expression::wrapByBrackets(void) {
	Operand leftBracket;
	leftBracket.t3() = "(";
	Operand rightBracket;
	rightBracket.t3() = ")";
	this->insert(this->begin(), leftBracket);
	this->push_back(rightBracket);
}

void Expression::operator-= (Expression exp) {
	this->wrapByBrackets();
	exp.wrapByBrackets();
	Operand minus;
	minus.t3() = "-";
	this->push_back(minus);
	for (auto& op : exp) {
		this->push_back(op);
	}
}

void Expression::operator*= (Expression exp) {
	this->wrapByBrackets();
	exp.wrapByBrackets();
	Operand multiply;
	multiply.t3() = "*";
	this->push_back(multiply);
	for (auto& op : exp) {
		this->push_back(op);
	}
}

void Expression::operator/= (Expression exp) {
	this->wrapByBrackets();
	exp.wrapByBrackets();
	Operand divide;
	divide.t3() = "/";
	this->push_back(divide);
	for (auto& op : exp) {
		this->push_back(op);
	}
}

VarEquation toVarEquation(string equationStr) {
    int equalSymbolIndex = equationStr.find('=');
    if (equalSymbolIndex == string::npos) {
        logic_error ex("\"=\" cannot be found.\n");
        throw ex;
    }
    Variable var = equationStr.substr(0, equalSymbolIndex);
    while (var.back() == ' ') var.pop_back();
    while (var.front() == ' ') var.erase(0);
    if (isdigit(var[0])) {
        logic_error ex("Invalid variable name.\n");
        throw ex;
    }
    for (auto& c : var) {
        string cStr(1, c);
        if (Expression::operatorPriority.count(cStr)) {
            logic_error ex("Invalid variable name.\n");
            throw ex;
        }
    }
    Expression exp = equationStr.substr(equalSymbolIndex + 1, string::npos);
    return { var, exp };
}

template<typename T>
T binaryOperate(T data1, Operator op, T data2) {
	if (op == "+") {
		return data1 + data2;
	}
	if (op == "-") {
		return data1 - data2;
	}
	if (op == "*") {
		return data1 * data2;
	}
	if (op == "/") {
		return data1 / data2;
	}
	if (op == "^") {
		return pow(data1, data2);
	}
}

template<typename T>
T unaryOperate(Operator op, T data) {
	if (op == "#") {
		return -data;
	}
	if (op == "sin") {
		return sin(data);
	}
	if (op == "cos") {
		return cos(data);
	}
	if (op == "tan") {
		return tan(data);
	}
}
