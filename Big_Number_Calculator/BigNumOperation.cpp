#include "libraries.h"

int toSameType(BigNum& num1, BigNum& num2) {
	if (num1.isDouble || num2.isDouble) {
		if (!num1.isDouble) {
			BigDouble temp = num1;
			num1 = temp.toBigNum();
		}
		if (!num2.isDouble) {
			BigDouble temp = num2;
			num2 = temp.toBigNum();
		}
		return BigNum::DOUBLE_TYPE;
	}
	else {
		return BigNum::INT_TYPE;
	}
};

bool operator== (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return int1 == int2;
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return double1 == double2;
	}
};

bool operator>  (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return int1 > int2;
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return double1 > double2;
	}
};

bool operator>= (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return int1 >= int2;
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return double1 >= double2;
	}
};

bool operator<  (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return int1 < int2;
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return double1 < double2;
	}
};

bool operator<= (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return int1 <= int2;
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return double1 <= double2;
	}
};

BigNum operator+  (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return (int1 + int2).toBigNum();
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return (double1 + double2).toBigNum();
	}
};

void operator+= (BigNum num1, BigNum num2) {
	num1 = num1 + num2;
};

BigNum operator-  (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return (int1 - int2).toBigNum();
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return (double1 - double2).toBigNum();
	}
};

BigNum BigNum::operator-()
{
	isNegative = !isNegative;
	return *this;
}

BigNum BigNum::operator+()
{
	return *this;
}

void operator-= (BigNum num1, BigNum num2) {
	num1 = num1 - num2;
};

BigNum operator*  (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return (int1 * int2).toBigNum();
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return (double1 * double2).toBigNum();
	}
};

void operator*= (BigNum num1, BigNum num2) {
	num1 = num1 * num2;
};

BigNum operator/ (BigNum num1, BigNum num2) {
	int type = toSameType(num1, num2);
	if (type == BigNum::INT_TYPE) {
		BigInt int1 = num1;
		BigInt int2 = num2;
		return (int1 / int2).toBigNum();
	}
	else {
		BigDouble double1 = num1;
		BigDouble double2 = num2;
		return (double1 / double2).toBigNum();
	}
};

void operator/= (BigNum num1, BigNum num2) {
	num1 = num1 / num2;
};

BigNum operator%  (BigNum num1, BigNum num2) {
	BigInt int1 = num1;
	BigInt int2 = num2;
	return (int1 % int2).toBigNum();
};

void operator%= (BigNum num1, BigNum num2) {
	num1 = num1 % num2;
};

BigNum abs(BigNum num)
{
	return num.isNegative ? -num : num;
}