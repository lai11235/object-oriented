#include "libraries.h"

BigInt::operator long long(void) {
	stringstream ss;
	long long output;
	ss << *this;
	ss >> output;
	return output;
};

BigInt::operator double(void) {
	stringstream ss;
	double output;
	ss << *this;
	ss >> output;
	return output;
};

BigDouble::operator string(void) {
	stringstream ss;
	string output;
	ss << *this;
	ss >> output;
	return output;
}; 

BigNum BigInt::toBigNum(void) {
	BigNum output;
	output.digits = this->digits;
	output.isNegative = this->isNegative;
	output.isDouble = false;
	output.decimalSize = 0;
	return output;
}

BigDouble::operator long long(void) {
	stringstream ss;
	long long output;
	ss << *this;
	ss >> output;
	return output;
};

BigDouble::operator double(void) {
	stringstream ss;
	double output;
	ss << *this;
	ss >> output;
	return output;
};

BigDouble::operator BigInt(void) {
	stringstream ss;
	BigInt output;
	ss << *this;
	ss >> output;
	return output;
};

BigInt::operator string(void) {
	stringstream ss;
	string output;
	ss << *this;
	ss >> output;
	return output;
};

BigNum BigDouble::toBigNum(void) {
	BigNum output;
	output.digits = this->digits;
	output.isNegative = this->isNegative;
	output.isDouble = true;
	output.decimalSize = this->decimalSize;
	return output;
}

NewBigDouble::operator BigDouble(void)
{
	BigDouble output;

	output = this->numerator / this->denominator;

	return output;
}