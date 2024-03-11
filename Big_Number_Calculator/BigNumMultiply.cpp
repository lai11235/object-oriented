#include "libraries.h"

BigInt BigInt::abs(void) {
	if (!isNegative) {
		return *this;
	}
	BigInt ans = *this;
	ans.isNegative = false;
	return ans;
}

BigInt BigInt::x10(int exponent) {
	BigInt zero;
	if (*this == zero) {
		return zero;
	}
	BigInt ans = *this;
	while (exponent > 0) {
		ans.digits.insert(ans.digits.begin(), 0);
		exponent--;
	}
	while (exponent < 0) {
		if (ans.digits.size() == 1) {
			ans.digits[0] = 0;
			break;
		}
		else {
			ans.digits.erase(ans.digits.begin());
		}
		exponent++;
	}
	return ans;
}

BigInt BigInt::xDigit(char& digit) {
	BigInt zero;
	if (*this == zero || digit > 9 || digit == 0) {
		return zero;
	}
	BigInt ans = *this;
	int carry = 0;
	for (int i = 0; i < ans.digits.size(); i++) {
		int sum = ans.digits[i] * digit + carry;
		ans.digits[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0) {
		ans.digits.push_back(carry);
	}
	return ans;
}

BigInt BigInt::operator*(BigInt& num) {
	BigInt sum;
	for (int i = 0; i < num.digits.size(); i++) {
		sum += this->xDigit(num.digits[i]).x10(i);
	}
	if (!this->isNegative && num.isNegative) {
		sum.isNegative = true;
	}
	else if (this->isNegative && !num.isNegative) {
		sum.isNegative = true;
	}
	else {
		sum.isNegative = false;
	}
	return sum;
}

void BigInt::operator*=(BigInt& num) {
	*this = *this * num;
}

BigInt BigInt::factorial() {
	BigInt zero, one = long long(1);
	if (*this <= zero) {
		return one;
	}
	BigInt remain = *this;
	BigInt ans = one;
	while (remain > zero) {
		ans *= remain;
		remain--;
	}
	return ans;
}

BigDouble BigDouble::abs(void) {
	if (!isNegative) {
		return *this;
	}
	BigDouble ans = *this;
	ans.isNegative = false;
	return ans;
}

BigDouble BigDouble::x10(int exponent) {
	BigDouble zero;
	if (*this == zero) {
		return zero;
	}
	BigDouble ans = *this;
	while (exponent > 0) {
		ans.digits.insert(ans.digits.begin(), 0);
		exponent--;
	}
	while (exponent < 0) {
		ans.digits.erase(ans.digits.begin());
		if (ans.digits.size() <= ans.decimalSize) {
			ans.digits.push_back(0);
		}
		exponent++;
	}
	return ans;
}

BigDouble BigDouble::xDigit(char& digit) {
	BigDouble zero;
	if (*this == zero || digit > 9 || digit == 0) {
		return zero;
	}
	BigDouble ans = *this;
	int carry = 0;
	for (int i = 0; i < ans.digits.size(); i++) {
		int sum = ans.digits[i] * (digit) + carry;
		carry = 0;
		ans.digits[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0) {
		ans.digits.push_back(carry);
	}
	return ans;
}

BigDouble BigDouble::operator*(BigDouble& num) {
	int maxSize = max(this->decimalSize, num.decimalSize);
	BigDouble sum(double(0), maxSize);
	int pow = -num.decimalSize;
	for (int i = 0; i < num.digits.size(); i++, pow++) {
		sum += this->xDigit(num.digits[i]).x10(pow);
	}

	if (!this->isNegative && num.isNegative) {
		sum.isNegative = true;
	}
	else if (this->isNegative && !num.isNegative) {
		sum.isNegative = true;
	}
	else {
		sum.isNegative = false;
	}
	return sum;
}

void BigDouble::operator*=(BigDouble& num) {
	*this = *this * num;
}

NewBigDouble operator*(NewBigDouble num1, NewBigDouble num2)
{
	NewBigDouble Ans;
	Ans.numerator =  num1.numerator * num2.numerator;
	Ans.denominator = num1.denominator * num2.denominator;

	return Ans;
}

NewBigDouble operator*(BigInt num1, NewBigDouble num2)
{
	NewBigDouble Ans;
	Ans.numerator =  (BigNum)num1 * num2.numerator;
	Ans.denominator = num2.denominator;
	return Ans;
}

NewBigDouble operator*(NewBigDouble num1, BigInt num2)
{
	NewBigDouble Ans;
	Ans.numerator = (BigNum)num2 * num1.numerator;
	Ans.denominator = num1.denominator;
	return Ans;
}

NewBigDouble NewBigDouble::operator*(BigDouble num)
{
	NewBigDouble Temp;
	int length = num.getRealDecimalSize();
	Temp.numerator = num.x10(length);
	Temp.denominator = BigDouble("1").x10(length);
	NewBigDouble Ans = *this * Temp;
	return Ans;
}