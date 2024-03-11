#include "Calculator.h"
#include "outlook.h"
#include <math.h>

BigInt digit[11] = { BigInt(0), BigInt(1), BigInt(2), BigInt(3), BigInt(4),BigInt(5),BigInt(6),BigInt(7),BigInt(8),BigInt(9),BigInt(10) };

enum class dataType
{
	Integer, Decimal, Null
};

enum class Symbol
{
	Null, Plus, Minus, Multiply, Divide, Power
};

enum class errorType 
{
	Null, Power, Factorial, varExist, varForm, divideZero, expForm
};

void errorMsg(errorType type)
{
	backgroundColor(Color::YELLO);
	switch (type)
	{
		case errorType::Null:
			break;
		case errorType::divideZero:
			cout << "The denominator can not be zero!\n";
			break;
		case errorType::Factorial:
			cout << "The number in factorial can not be decimal or negative!\n";
			break;
		case errorType::Power:
			cout << "The Radicand can not be negative number!\n";
			break;
		case errorType::varExist:
			break;
		case errorType::varForm:
			cout << "Input Error\n";
			break;
		case errorType::expForm:
			cout << "The expression form is wrong!\n";
			break;
	}
	colorReset();
}

BigNum errorExpression(errorType _error)
{
	BigInt msg;
	msg.setStrNum("Error");
	Expression::error = _error;
	return msg;
}

BigNum Sqrt(BigNum num1)
{
	int i, j;
	bool flag = false;
	short fir = 0;
	int dSize = num1.getRealDecimalSize();
	string num = num1.getNumberString();
	num += string(200 - dSize , 0);
	
	string temp = "";
	BigDouble Ans;
	BigInt a, b, remain, _remain;
	BigInt hundred;
	hundred = digit[10] * digit[10];
	
	if (num.size() % 2)
	{
		fir += (num[0]);
		i = 1;
	}
		
	else
	{
		fir += (num[0]);
		fir = (fir << 1) + (fir << 3) + (num[1]);
		i = 2;
	}

	int sqrtFir = sqrt(fir);
	a = digit[sqrtFir];
	Ans = Ans + a;
	remain = digit[fir - sqrtFir * sqrtFir];
	a = a * digit[2];
	
	for (; i < num.size(); i += 2)
	{
		flag = false;
		remain = remain.x10(2);

		temp = (num[i] + '0');
		temp += (num[i + 1] + '0');

		_remain.setStrNum(temp);
		remain = remain + _remain;

		a = a.x10(1);

		for (j = 0; j < 10; j++)
		{
			if ((a + digit[j]) * digit[j] > remain)
			{
				flag = true;
				break;
			}
		}
		j--;
		remain = remain - (a + digit[j]) * digit[j];
		a = a + digit[j] + digit[j];
		Ans = Ans.x10(1);
		Ans = Ans + digit[j];
	}

	Ans = Ans.x10(-100);
	return Ans;
}

BigNum power(BigNum num1, BigNum num2, Expression &exp)
{
	BigDouble Ans;
	if (!num2.isInteger() && !num1.isPositive())
	{
		Ans.setStrNum("Error");
		exp.isValidExpression = false;
		exp.error = errorType::Power;
		return Ans;
	}

	BigInt nPart = num2;
	BigInt zero, two;
	BigDouble base = (BigDouble)num1;
	BigInt remain;

	zero.setStrNum("0");
	two.setStrNum("2");
	Ans.setStrNum("1");

	while (nPart > zero)
	{
		remain = nPart % 2;
		if (remain > zero)
		{
			Ans *= base;
		}

		base *= base;
		nPart = nPart / two;
	}

	if (!num2.isInteger())//Sqrt
	{
		Ans = Ans * Sqrt(num1);
	}
	return Ans;
}

BigNum fact(BigNum num, Expression &exp)
{
	BigInt Ans;
	
	if (!num.isInteger() || !num.isPositive())
	{
		Ans.setStrNum("Error");
		exp.isValidExpression = false;
		exp.error = errorType::Factorial;
		
		return Ans;
	}

	BigInt N = num;
	BigInt zero;
	zero.setStrNum("0");
	Ans.setStrNum("1");

	while (N > zero)
	{
		Ans *= N;
		N--;
	}

	return Ans;
}

int Expression::priority(string sym)
{
	if (sym == "!")
		return 5;
	else if (sym == "^")
		return 4;
	else if (sym == "#" || sym == "_")
		return 3;
	else if (sym == "*" || sym == "/" || sym == "%")
		return 2;
	else if (sym == "-" || sym == "+")
		return 1;
	else
		return 0;
}

bool Expression::isNum(char t)
{
	return t != '+' && t != '-' && t != '*' && t != '/' && t != '%' && t != '^' \
		&& t != '(' && t != ')' && t != ' ' && t != '#' && t != '_' && t != '!';
}

bool Expression::isPreSym(char t, char type)
{
	if (!type)
		return t == '+' || t == '*' || t == '%' || t == '/' || t == '^' || t == '(';
	else
		return t == '-' || t == '*' || t == '%' || t == '/' || t == '^' || t == '(';
}

bool Expression::Prioritycomp(char a, char b)// Prioritycomp the priority of two symbol
{
	return priority(string(1, a)) >= priority(string(1, b));
}

bool isValidNum(string num)
{
	map<char, int> countSym;
	int symQuan = 0;//Recording the amount of non-number element
	int numQuan = 0;//Recording the amount of  number4

	for (int i = 0; i < num.size(); i++)//Recording the number of each number
	{
		countSym[num[i]]++;

		if ((num[i] > '9' || num[i] < '0'))
		{
			if (num[i] != '+' && num[i] != '-' && num[i] != '.')
				return false;
			symQuan++;
		}

		else if (num[i] <= '9' && num[i] >= '0')
			numQuan++;
	}

	if (symQuan > 2)//A valid form number symbol will not excess two
		return false;
	else
	{

		bool a = countSym.count('+'), b = countSym.count('-'), c = countSym.count('.');

		if (a || b || c || !symQuan)
		{
			if (a && b)
				return false;
			else if (num[0] == '+' && numQuan && countSym['+'] == 1 && countSym['.'] <= 1)
				return true;
			else if (num[0] == '-' && numQuan && countSym['-'] == 1 && countSym['.'] <= 1)
				return true;
			else if (numQuan && countSym['.'] == 1 && (countSym['+'] + countSym['-']) <= 1)//decimal point
				return true;
			else if (!symQuan)
				return true;
			else
				return false;
		}

		else
			return false;
	}
}

void toStandardFrom(string &num)
{
	int ZeroLen = 0;//Calculating the length of zero and erase redundant zero
	for (int i = 0; i < num.size(); i++)
	{
		if (num[i] == '0')
			ZeroLen++;
		else
			break;
	}

	num = num.substr(ZeroLen);

	if (num[0] == '.' || !num.size())
	{
		num.insert(num.begin(), '0');
	}

	else if (*num.rbegin() == '.')
		num += '0';
}

Expression::Expression(string exp)
{
	int posOfComma = exp.find(',');
	isValidExpression = true;

	/** Transfering the expression power symbol to readable form **/
	while (posOfComma != string::npos) {

		exp[posOfComma] = '^';
		exp.insert(exp.begin() + posOfComma, ')');
		exp.insert(exp.begin() + posOfComma + 2, '(');
		posOfComma = exp.find(',');
	}

	/** Erasing the "pow" word in expression **/
	int posOfPow = exp.find("pow");
	while (posOfPow != string::npos) {

		exp.erase(posOfPow, 3);
		posOfPow = exp.find("pow");
	}

	/** Nnary Operation **/

	string temp = "";
	for (int i = 0; i < exp.size(); i++)
	{
		if (isNum(exp[i]))
			temp += exp[i];
		else if (exp[i] == '-' || exp[i] == '+')
		{
			int nQuan = 0, pQuan = 0;
			while (exp[i] == '-' || exp[i] == '+' || exp[i] == ' ')
			{
				switch (exp[i])
				{
					case '-':
						nQuan++;
						break;
					case '+':
						pQuan++;
						break;
					case ' ':
						break;
				}
				i++;
			}

			if (nQuan % 2)
				temp += '-';
			else 
				temp += '+';
			i--;
		}
		else
			temp += exp[i];
	}

	exp = temp;

	for (int i = 0; i < exp.size(); i++)
	{
		if (!i)
		{
			if (exp[i] == '-')
				exp[i] = '_';
			else if (exp[i] == '+')
				exp[i] = '#';
		}

		else if (exp[i] == '-' && isPreSym(exp[i - 1], 0))
			exp[i] = '_';

		else if (exp[i] == '+' && isPreSym(exp[i - 1], 1))
			exp[i] = '#';
	}

	stack<char> tempStorage;
	string t = "";
	char preSym = ' ';

	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == ' ')
			continue;

		while (isNum(exp[i]) && i < exp.size()) 
		{
			t += exp[i];
			i++;
		}

		if (t.size()) 
		{
			bool isValid = isValidNum(t);
			bool isExist = Variables.count(t);

			if (isValid || isExist)
			{
				if(!isExist)// Number
					toStandardFrom(t);
				postOrder.push(t);
				i--;
				t = "";
			}

			else
			{
				while (postOrder.size())
					postOrder.pop();
				
				if (!isExist)
				{
					backgroundColor(Color::YELLO);
					Expression::error = errorType::varExist;
					cout << "The Varialbe " << t << " can not be found!\n";
					colorReset();
				}
				else
					Expression::error = errorType::varForm;

				isValidExpression = false;
				break;
			}
		}

		else 
		{
			if (tempStorage.empty()) 
			{
				tempStorage.push(exp[i]);
			}

			else if (exp[i] == ')') 
			{
				while (tempStorage.top() != '(')
				{
					postOrder.push(string(1, tempStorage.top()));
					tempStorage.pop();
				}
				tempStorage.pop();//erase the '('
			}

			else if (exp[i] == '(') 
			{
				tempStorage.push(exp[i]);
			}

			else if (Prioritycomp(tempStorage.top(), exp[i]) && tempStorage.size()) 
			{

				while (tempStorage.size() && Prioritycomp(tempStorage.top(), exp[i])) 
				{

					postOrder.push(string(1, tempStorage.top()));
					tempStorage.pop();
				}

				tempStorage.push(exp[i]);
			}

			else 
			{

				tempStorage.push(exp[i]);
			}
		}

		preSym = exp[i];
	}

	while (tempStorage.size() && isValidExpression) {

		postOrder.push(string(1, tempStorage.top()));
		tempStorage.pop();
	}
}

BigNum Expression::calculate()
{
	stack<BigNum> Ans;
	string Temp;
	bool isDouble = false;
	
	while (postOrder.size() && isValidExpression)
	{
		Temp = postOrder.front();
		if (Temp[0] >= '0' && Temp[0] <= '9')// Number
		{
			int pos = Temp.find('.');
			if (pos != string::npos)
			{
				NewBigDouble FNum;
				FNum.setNumerator(Temp);
				int length = FNum.numerator.getRealDecimalSize();
				FNum.numerator = FNum.numerator.x10(length);
				FNum.denominator = digit[1];
				FNum.denominator = FNum.denominator.x10(length);
				Ans.push(FNum);
				isDouble = true;
				//cout << FNum.numerator << " " << FNum.denominator << endl;
			}
			else
			{
				BigInt INum;
				INum.setStrNum(Temp);
				Ans.push(INum);
			}
		}

		else if (isNum(Temp[0]))// If it has possiblility defined
		{
			if (!Variables.count(Temp))
			{
				backgroundColor(Color::YELLO);
				isValidExpression = false;
				cout << "The Varialbe " << Temp << " can not be found!\n";
				colorReset();

				return errorExpression(errorType::varExist);
			}

			if (!Calculator::Variables[Temp].isInteger())
				isDouble = true;
			Ans.push(Calculator::Variables[Temp]);
		}

		else if (Temp[0] == '!')
		{
			if(Ans.size())
				Ans.top() = fact(Ans.top(), *this);
			else
			{
				isValidExpression = false;
				return errorExpression(errorType::expForm);
			}
		}

		else if (Temp[0] == '_' || Temp[0] == '#')
		{
			if (Ans.size())
			{
				switch (Temp[0])
				{
					case '_':
						Ans.top() = -Ans.top();
						break;
					case '#':
						break;
				}
			}
			
			else
			{
				isValidExpression = false;
				return errorExpression(errorType::expForm);
			}
		}

		else// Operation
		{
			BigNum Num1, Num2;
			if (Ans.size())
			{
				Num1 = Ans.top();
				Ans.pop();
			}
			else
			{
				isValidExpression = false;
				return errorExpression(errorType::expForm);
			}
			
			if (Ans.size())
			{
				Num2 = Ans.top();
				Ans.pop();
			}
			else
			{
				isValidExpression = false;
				return errorExpression(errorType::expForm);
			}

			switch (Temp[0])
			{
				case '+':
					Ans.push(Num2 + Num1);
					break;
				case '-':
					Ans.push(Num2 - Num1);
					break;
				case '*':
					Ans.push(Num2 * Num1);
					break;
				case '/':
					if (Num1 == digit[0])
					{
						isValidExpression = false;
						return errorExpression(errorType::divideZero);
					}
					Ans.push(Num2 / Num1);
					break;
				case '%':
					Ans.push(Num2 % Num1);
					break;
				case '^':
					isDouble = true;
					Ans.push(power(BigDouble(Num2), Num1, *this));
					break;
			}
		}

		postOrder.pop();
	}
	if (!isValidExpression)
	{
		BigInt Temp;
		Temp.setStrNum("Error");
		return Temp;
	}
	else if (isDouble)
	{
		return Ans.top();
	}
	else
		return (BigInt)Ans.top();
}

void evaluate()
{
	Calculator player;
	string command;

	while (getline(cin, command))
	{
		int pos = command.find("Set");

		if (pos == 0)//Set variable mode
		{
			vector<string> part;
			stringstream ss;
			string _part;
			dataType type;
			ss << command;
			int quan = 0;
			
			while (quan <= 3 && ss >> _part)
			{
				part.push_back(_part);
				quan++;
			}
			backgroundColor(Color::YELLO);
			if (part.size() != 4)
			{
				cout << "Command Error!\n";
				continue;
			}

			if (part[1] == "Integer")
				type == dataType::Integer;
			else if (part[1] == "Decimal")
				type == dataType::Decimal;
			else
			{
				cout << "DataType Error!\n";
				continue;
			}
			
			string varName = part[2];

			if (varName[0] >= '0' && varName[0] <= '9')
			{
				cout << "The begining of variable can not be number!\n";
				continue;
			}

			if(part[3] != "=")
			{
				cout << "Command Error!\n";
				continue;
			}
			colorReset();
			int pos = command.find('=');
			while (command[pos] == ' ' || command[pos] == '=')
				pos++;
			
			Expression exp(command.substr(pos));
					
			if (exp.isValidExpression)
			{
				BigNum Ans = exp.calculate();
						
				if(exp.isValidExpression)
					Calculator::Variables[varName] = Ans;
				else
					errorMsg(Expression::error);
			}

			else
				errorMsg(Expression::error);
		}

		else if (pos == string::npos)
		{
			pos = command.find('=');
			if (pos != string::npos)
			{
				pos--;
				while (pos >=0 && command[pos] == ' ')
					pos--;
				if (pos < 0)
				{
					errorMsg(errorType::expForm);
					continue;
				}
				string varName = command.substr(0, pos + 1);
				if (Calculator::Variables.count(varName))
				{
					pos++;

					while (pos != command.size() && (command[pos] == ' ' || command[pos] == '='))
						pos++;
					Expression exp(command.substr(pos));

					if (exp.isValidExpression)
					{
						BigNum Ans = exp.calculate();

						if (!exp.isValidExpression)
							errorMsg(Expression::error);
						else
							Calculator::Variables[varName] = Ans;
					}

					else
						errorMsg(Expression::error);
				}
				else
				{
					backgroundColor(Color::YELLO);
					cout << "The Variable " << varName << " can not be found!\n";
					colorReset();
					continue;
				}
			}
			else
			{
				Expression exp(command);

				if (exp.isValidExpression)
				{
					BigNum Ans = exp.calculate();

					if (exp.isValidExpression)
						cout << Ans << endl;
					else
						errorMsg(Expression::error);
				}

				else
					errorMsg(Expression::error);
			}
		}
	}
}

string Calculator::Accuracy = "";
map<string, BigNum> Calculator::Variables = {};
errorType Expression::error = errorType::Null;