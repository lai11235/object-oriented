#include "libraries.h"

BigInt BigInt::operator=(long long num) {
	isNegative = num < 0;
	isDouble = false;
	decimalSize = 0;

	num = std::abs(num);
	digits.clear();
	do {
		digits.push_back(num % 10);
		num /= 10;
	} while (num > 0);
	return *this;
};

BigInt BigInt::operator=(int num) {
	*this = long long(num);
	return *this;
}

BigInt BigInt::operator=(double num) {
	*this = long long(num);
	return *this;
};

BigInt BigInt::operator=(const BigNum& num) {
	this->isNegative = num.isNegative;
	this->isDouble = false;
	decimalSize = 0;
	
	this->digits.clear();
	auto copy = num.digits.begin() + num.decimalSize;
	for (; copy != num.digits.end(); copy++)
		this->digits.push_back(*copy);
	return *this;
};

BigInt BigInt::operator=(const string& expression) {
	return *this;
};

void BigInt::setStrNum(string strNum) {
	isNegative = false;
	isDouble = false;
	decimalSize = 0;

	auto start = strNum.rbegin();
	auto point = find(strNum.rbegin(), strNum.rend(), '.');
	if (point != strNum.rend()) {
		start = point + 1;
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
	for (auto digit = start; digit != end; digit++) {
		digits.push_back(*digit - '0');
	}
};

BigInt::BigInt() {
	*this = long long(0);
};

BigInt::BigInt(const long long& num) {
	*this = num;
};

BigInt::BigInt(const int& num) {
	*this = num;
}

BigInt::BigInt(const double& num) {
	*this = num;
};

BigInt::BigInt(const BigNum& copy) {
	*this = copy;
};
BigInt::BigInt(const string& expression) {

};