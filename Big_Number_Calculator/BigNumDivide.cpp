#include "libraries.h"

pair<BigInt, BigInt> BigInt::divideResult(BigInt& num) {
	BigInt quotient;
	BigInt remain;
	for (int i = this->digits.size() - 1; i >= 0; i--) {
		BigInt nowDigit = this->digits[i];
		remain = remain.x10(1) + nowDigit;
		int cnt = 0;
		while (remain >= num) {
			remain -= num;
			cnt++;
		}
		BigInt resultDigit = cnt;
		quotient += resultDigit.x10(i);
	}
	
	if (!this->isNegative && num.isNegative) {
		quotient.isNegative = true;
	}
	else if (this->isNegative && !num.isNegative) {
		quotient.isNegative = true;
	}
	else {
		quotient.isNegative = false;
	}
	remain.isNegative = this->isNegative;

	return { quotient, remain };
}

BigInt BigInt::operator/(BigInt& num) {
	auto devideAns = this->divideResult(num);
	return devideAns.first;
}

void BigInt::operator/=(BigInt& num) {
	*this = *this / num;
}

BigInt BigInt::operator%(BigInt& num) {
	auto devideAns = this->divideResult(num);
	return devideAns.second;
}

void BigInt::operator%=(BigInt& num) {
	*this = *this % num;
}

BigDouble BigDouble::operator/(BigDouble& num) {
	BigDouble num1 = *this;
	BigDouble num2 = num;

	int maxDeciSize = max(num1.decimalSize, num2.decimalSize);
	int maxDeciLen = max(num1.decimalLen(), num2.decimalLen());
	num1.setDeciSize(maxDeciLen);
	num2.setDeciSize(maxDeciLen);
	num1.decimalSize = 0;
	num2.decimalSize = 0;

	BigInt int1 = BigInt(num1);
	BigInt int2 = BigInt(num2);

	auto iter1 = int1.digits.begin();
	auto iter2 = int2.digits.begin();
	for (; iter1 != int1.digits.end() && iter2 != int2.digits.end();) {
		if (*iter1 == 0 && *iter2 == 0 && int1.digits.size() > 1 && int2.digits.size() > 1) {
			iter1 = int1.digits.erase(iter1);
			iter2 = int2.digits.erase(iter2);
		}
		else {
			break;
		}
	}

	auto result = int1.divideResult(int2);
	
	stringstream ss;
	BigDouble quotient(0, maxDeciSize);
	ss << result.first;
	ss >> quotient;
	BigInt remain = result.second;

	BigInt zero;
	for (int pow = -1; pow >= -maxDeciSize; pow--) {
		if (remain == zero) {
			break;
		}
		auto tempResult = remain.x10(1).divideResult(int2);
		BigDouble tempQuotient = tempResult.first;
		quotient.digits[decimalSize + pow] = long long(tempQuotient);
		//quotient += tempQuotient.x10(pow);
		//cout << quotient;
		remain = tempResult.second;
	}

	if (!this->isNegative && num.isNegative) {
		quotient.isNegative = true;
	}
	else if (this->isNegative && !num.isNegative) {
		quotient.isNegative = true;
	}
	else {
		quotient.isNegative = false;
	}
	return quotient;
}

void BigDouble::operator/=(BigDouble& num) {
	*this = *this / num;
}

NewBigDouble operator/(NewBigDouble num1, NewBigDouble num2)
{
	NewBigDouble Ans;
	Ans.numerator = num1.numerator * num2.denominator;
	Ans.denominator = num1.denominator * num2.numerator;

	return Ans;
}

NewBigDouble operator/(BigInt num1, NewBigDouble num2)
{
	NewBigDouble Ans;
	Ans.numerator = num2.denominator * num1;
	Ans.denominator = num2.numerator;
	return Ans;
}

NewBigDouble operator/(NewBigDouble num1, BigInt num2)
{
	NewBigDouble Ans;
	Ans.numerator = num1.numerator;
	Ans.denominator = num1.denominator * num2;
	return Ans;
}

NewBigDouble NewBigDouble::operator/(BigDouble num)
{
	NewBigDouble Temp;
	int length = num.getRealDecimalSize();
	Temp.numerator = num.x10(length);
	Temp.denominator = BigDouble("1").x10(length);
	NewBigDouble Ans = *this / Temp;
	return Ans;
}