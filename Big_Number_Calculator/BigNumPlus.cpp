#include "libraries.h"

void BigInt::operator+=(BigInt num) {
	/* A += B => A -= -B */
	if (!this->isNegative && num.isNegative) {
		num.isNegative = false;
		*this -= num;
		return;
	}
	/* A += B => -(-A -= B) */
	if (this->isNegative && !num.isNegative) {
		this->isNegative = false;
		*this -= num;
		*this = -long long(*this);
		return;
	}
	/* A += B => -(-A += -B) */
	if (this->isNegative && num.isNegative) {
		this->isNegative = false;
		num.isNegative = false;
		*this += num;
		*this = -long long(*this);
		return;
	}

	while (this->digits.size() < num.digits.size()) {
		this->digits.push_back(0);
	}
	int carry = 0;
	int i = 0;
	for (; i < num.digits.size(); i++) {
		int sum = this->digits[i] + num.digits[i] + carry;
		carry = 0;
		this->digits[i] = sum % 10;
		carry = sum / 10;
	}
	for (; i < this->digits.size(); i++) {
		int sum = this->digits[i] + carry;
		carry = 0;
		this->digits[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0) {
		this->digits.push_back(carry);
	}
};

BigInt BigInt::operator+(BigInt& num) {
	BigInt ans;
	ans = *this;
	ans += num;
	return ans;
};

BigInt BigInt::operator++(void) {
	BigInt ans = *this;
	*this += BigInt(long long(1));
	return ans;
};

BigInt BigInt::operator++(int) {
	*this += BigInt(long long(1));
	return *this;
};

void BigDouble::operator+=(BigDouble num) {
	/* A += B => A -= -B */
	if (!this->isNegative && num.isNegative) {
		num.isNegative = false;
		*this -= num;
		return;
	}
	/* A += B => -(-A -= B) */
	if (this->isNegative && !num.isNegative) {
		this->isNegative = false;
		*this -= num;
		*this = -double(*this);
		return;
	}
	/* A += B => -(-A += -B) */
	if (this->isNegative && num.isNegative) {
		this->isNegative = false;
		num.isNegative = false;
		*this += num;
		*this = -double(*this);
		return;
	}

	this->extentDeciSize(num.decimalSize);
	num.extentDeciSize(this->decimalSize);

	while (this->digits.size() < num.digits.size()) {
		this->digits.push_back(0);
	}
	int carry = 0;
	int i = 0;
	for (; i < num.digits.size(); i++) {
		int sum = this->digits[i] + num.digits[i] + carry;
		carry = 0;
		this->digits[i] = sum % 10;
		carry = sum / 10;
	}
	for (; i < this->digits.size(); i++) {
		int sum = this->digits[i] + carry;
		carry = 0;
		this->digits[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0) {
		this->digits.push_back(carry);
	}
};

BigDouble BigDouble::operator+(BigDouble& num) {
	BigDouble ans;
	ans = *this;
	ans += num;
	return ans;
};

BigDouble BigDouble::operator++(void) {
	BigDouble ans = *this;
	*this += BigDouble(long long(1));
	return ans;
};

BigDouble BigDouble::operator++(int) {
	*this += BigDouble(long long(1));
	return *this;
};

NewBigDouble operator+(NewBigDouble num1, NewBigDouble num2)
{
	NewBigDouble Ans;
	Ans.numerator = num2.denominator * num1.numerator + (num1.denominator * num2.numerator);
	Ans.denominator = num1.denominator * num2.denominator;

	return Ans;
}

NewBigDouble operator+(BigInt num1, NewBigDouble num2)
{
	NewBigDouble Ans;
	Ans.numerator = num2.denominator * num1 + num2.numerator;
	Ans.denominator = num1 * num2.denominator;
	return Ans;
}

NewBigDouble operator+(NewBigDouble num1, BigInt num2)
{
	NewBigDouble Ans;
	Ans = num2 + num1;
	return Ans;
}

NewBigDouble NewBigDouble::operator+(BigDouble num)
{
	NewBigDouble Temp;
	int length = num.getRealDecimalSize();
	Temp.numerator = num.x10(length);
	Temp.denominator = BigDouble("1").x10(length);
	NewBigDouble Ans = *this + Temp;
	return Ans;
}