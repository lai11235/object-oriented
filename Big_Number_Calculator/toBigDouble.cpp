#include "libraries.h"

BigDouble BigDouble::operator=(long long num) {
	isNegative = num < 0;
	isDouble = true;

	num = std::abs(num);
	digits.clear();
	digits.resize(decimalSize);
	do {
		digits.push_back(num % 10);
		num /= 10;
	} while (num > 0);
	return *this;
};

BigDouble BigDouble::operator=(int num) {
	*this = long long(num);
	return *this;
}

BigDouble BigDouble::operator=(double num) {
	setStrNum(to_string(num));
	/*
	isNegative = num < 0;
	isDouble = true;

	num = std::abs(num);
	digits.clear();
	digits.resize(decimalSize);
	long long intPart = num;
	double decimalPart = num - intPart;
	do {
		digits.push_back(intPart % 10);
		intPart /= 10;
	} while (intPart > 0);

	int decimalIndex = decimalSize - 1;
	while (decimalPart > 0 && decimalIndex >= 0) {
		decimalPart *= 10;
		char intDigit = decimalPart;
		decimalPart -= intDigit;
		digits[decimalIndex--] = intDigit;
	}
	*/
	return *this;
};

BigDouble BigDouble::operator=(const BigInt& num) {
	this->isNegative = num.isNegative;
	this->isDouble = true;

	this->digits.clear();
	this->digits.resize(decimalSize);
	for (auto copy = num.digits.begin(); copy != num.digits.end(); copy++) {
		this->digits.push_back(*copy);
	}
	return *this;
};

BigDouble BigDouble::operator=(const BigNum& num) {
	if (num.isDouble) {
		this->digits = num.digits;
		this->decimalSize = num.decimalSize;
		this->isNegative = num.isNegative;
		this->isDouble = true;
	}
	else {
		*this = BigInt(num);
	}
	return *this;
}

BigDouble BigDouble::operator=(const string& expression) {
	return *this;
};

void BigDouble::setStrNum(string strNum) {
	isNegative = false;
	isDouble = true;
	auto start = strNum.rbegin();
	auto intStart = find(strNum.rbegin(), strNum.rend(), '.');
	
	bool haveDecimal = false;
	if (intStart == strNum.rend()) {
		intStart = strNum.rbegin();
	}
	else {
		haveDecimal = true;
		intStart++;
	}

	auto end = strNum.rend();
	if (strNum[0] == '+') {
		end--;
	}
	if (strNum[0] == '-') {
		isNegative = true;
		end--;
	}

	digits.clear();
	digits.resize(decimalSize);
	if (haveDecimal) {
		int decimalIndex = decimalSize - 1;
		for (auto decimal = intStart - 2;decimalIndex >= 0; decimal--) {
			digits[decimalIndex--] = *decimal - '0';
			if (decimal == strNum.rbegin()) {
				break;
			}
		}
	}
	
	for (auto integer = intStart; integer != end; integer++) {
		digits.push_back(*integer - '0');
	}
};

BigDouble::BigDouble(int _decimalSize) {
	decimalSize = _decimalSize;
	*this = double(0);
};

BigDouble::BigDouble(const long long& num, int _decimalSize) {
	decimalSize = _decimalSize;
	*this = num;
};

BigDouble::BigDouble(const int& num, int _decimalSize) {
	decimalSize = _decimalSize;
	*this = num;
}

BigDouble::BigDouble(const double& num, int _decimalSize) {
	decimalSize = _decimalSize;
	*this = num;
};

BigDouble::BigDouble(const BigInt& copy, int _decimalSize) {
	decimalSize = _decimalSize;
	*this = copy;
};

BigDouble::BigDouble(const BigNum& copy, int _decimalSize) {
	decimalSize = _decimalSize;
	*this = copy;
}

BigDouble::BigDouble(const BigDouble& copy, int _decimalSize) {
	*this = copy;
	//this->setDecimalSize(_decimalSize);
};

BigDouble::BigDouble(const string& expression, int _decimalSize) {
	decimalSize = _decimalSize;
};

NewBigDouble NewBigDouble::operator=(BigNum& num)
{
	if (num.isNewDouble)
	{
		
	}
}