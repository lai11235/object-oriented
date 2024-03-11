#pragma once
#include "libraries.h"

enum class dataType;
enum class Symbol;
enum class errorType;

Symbol symbolType(string);

class Expression;

class Calculator
{
	protected:
		static map<string, BigNum> Variables;
		static string Accuracy;
	public:
		Calculator()
		{
			Accuracy = "0.";
			for (int i = 0; i < 99; i++)
				Accuracy += "0";
			Accuracy += '1';
		}
		friend void evaluate();
		friend BigNum sqrt(BigDouble);
		friend BigNum power(BigNum num1, BigNum num2, Expression& exp);
		friend BigNum abs(BigNum num);
};

class Expression:public Calculator
{
	private:
		string expression;
		queue<string> postOrder;
		int priority(string);
		bool isValidExpression;
		static errorType error;
	public:
		Expression(string);
		bool Prioritycomp(char, char);// return 1 if first is bigger or equal
		bool isNum(char);
		bool isPreSym(char, char);
		void show()
		{
			while (postOrder.size())
			{
				cout << postOrder.front() << " ";
				postOrder.pop();
			}
		}
		BigNum calculate();
		friend void evaluate();
		friend BigNum fact(BigNum num, Expression& exp);
		friend BigNum power(BigNum num1, BigNum num2, Expression& exp);
		friend BigNum errorExpression(errorType _error);
};

void evaluate();