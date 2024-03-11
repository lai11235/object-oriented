#include "libraries.h"

ostream& operator<< (ostream& strm, BigInt num) {
	string output;
	if (num.isNegative) {
		output.push_back('-');
	}
	for (auto digit = num.digits.rbegin(); digit != num.digits.rend(); digit++) {
		output.push_back('0' + *digit);
	}
	strm << output;
	return strm;
};

istream& operator>> (istream& strm, BigInt& num) {
	num.setStrNum(BigNum::getNumStr(strm));
	return strm;
};

ostream& operator<< (ostream& strm, BigDouble num) {
	int zeroNum = 0;
	int i = 0;
	while (num.digits[i] == 0 && i < num.decimalSize) {
		zeroNum++;
		i++;
	}

	int decimalLen = num.decimalSize - zeroNum;
	auto end = num.digits.rend() - zeroNum;
	auto decimalStart = end - decimalLen;
	string output;
	if (num.isNegative) {
		output.push_back('-');
	}
	for (auto digit = num.digits.rbegin(); digit != end; digit++) {
		if (digit == decimalStart) {
			output.push_back('.');
		}
		output.push_back('0' + *digit);
	}
	strm << output;
	return strm;
};

istream& operator>> (istream& strm, BigDouble& num) {
	num.setStrNum(BigNum::getNumStr(strm));
	return strm;
};

ostream& operator<<(ostream& strm, NewBigDouble _num)
{
	BigDouble num;
	num = _num.numerator / _num.denominator;

	int zeroNum = 0;
	int i = 0;
	while (num.digitValue(i) == 0 && i < num.getDecimalSize()) {
		zeroNum++;
		i++;
	}

	int decimalLen = num.getDecimalSize() - zeroNum;
	int end = zeroNum - 1;
	int decimalStart = end + decimalLen;
	string output;
	if (!num.isPositive()) {
		output.push_back('-');
	}
	for (int digit = num.digitSize() - 1; digit != end; digit--) {
		if (digit == decimalStart) {
			output.push_back('.');
		}
		output.push_back('0' + num.digitValue(digit));
	}
	strm << output;
	return strm;

}

ostream& operator<< (ostream& strm, BigNum num) {
	if (num.isNewDouble){
		NewBigDouble output = num;

	}
	else if (num.isDouble) {
		BigDouble output = num;
		strm << output;
	}
	else {
		BigInt output = num;
		strm << output;
	}
	return strm;
}

istream& operator>> (istream& strm, BigNum& num) {
	BigDouble input;
	strm >> input;
	num = input.toBigNum();
	return strm;
}

