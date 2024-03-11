#include "libraries.h"

int BigInt::cmp(BigInt& num) {
	const int larger = 1;
	const int equal = 0;
	const int smaller = -1;
	
	while (this->digits.back() == 0 && this->digits.size() > 1) {
		this->digits.pop_back();
	}
	while (num.digits.back() == 0 && num.digits.size() > 1) {
		num.digits.pop_back();
	}

	if (!this->isNegative && num.isNegative) {
		return larger;
	}
	if (this->isNegative && !num.isNegative) {
		return smaller;
	}
	if (this->digits.size() > num.digits.size()) {
		return this->isNegative ? smaller : larger;
	}
	if (this->digits.size() < num.digits.size()) {
		return this->isNegative ? larger : smaller;
	}

	for (int i = digits.size() - 1; i >= 0; i--) {
		if (this->digits[i] > num.digits[i]) {
			return this->isNegative ? smaller : larger;
		}
		if (this->digits[i] < num.digits[i]) {
			return this->isNegative ? larger : smaller;
		}
	}

	return equal;
}

bool BigInt::operator==(BigInt& num) {
	return cmp(num) == 0;
};

bool BigInt::operator> (BigInt& num) {
	return cmp(num) == 1;
};

bool BigInt::operator>=(BigInt& num) {
	int cmpResult = cmp(num);
	return cmpResult == 1 || cmpResult == 0;
};

bool BigInt::operator< (BigInt& num) {
	return cmp(num) == -1;
};

bool BigInt::operator<=(BigInt& num) {
	int cmpResult = cmp(num);
	return cmpResult == -1 || cmpResult == 0;
};

int BigDouble::cmp(BigDouble& num) {
	const int larger = 1;
	const int equal = 0;
	const int smaller = -1;

	while (this->digits.back() == 0 && this->intPartSize() > 1) {
		this->digits.pop_back();
	}
	while (num.digits.back() == 0 && num.intPartSize() > 1) {
		num.digits.pop_back();
	}

	if (!this->isNegative && num.isNegative) {
		return larger;
	}
	if (this->isNegative && !num.isNegative) {
		return smaller;
	}
	if (this->intPartSize() > num.intPartSize()) {
		return this->isNegative ? smaller : larger;
	}
	if (this->intPartSize() < num.intPartSize()) {
		return this->isNegative ? larger : smaller;
	}

	int iThis = this->digits.size() - 1;
	int iNum = num.digits.size() - 1;
	for (; iThis >= this->decimalSize && iNum >= num.decimalSize; iThis--, iNum--) {
		if (this->digits[iThis] > num.digits[iNum]) {
			return this->isNegative ? smaller : larger;
		}
		if (this->digits[iThis] < num.digits[iNum]) {
			return this->isNegative ? larger : smaller;
		}
	}

	int thisLen = this->decimalLen();
	int numLen = num.decimalLen();
	for (; iThis > 0 && iNum > 0; iThis--, iNum--) {
		if (this->digits[iThis] > num.digits[iNum]) {
			return this->isNegative ? smaller : larger;
		}
		if (this->digits[iThis] < num.digits[iNum]) {
			return this->isNegative ? larger : smaller;
		}
	}
	if (iThis > 0) {
		return this->isNegative ? smaller : larger;
	}
	if (iNum > 0) {
		return this->isNegative ? larger : smaller;
	}
	return equal;
}

bool BigDouble::operator==(BigDouble& num) {
	return cmp(num) == 0;
};

bool BigDouble::operator> (BigDouble& num) {
	return cmp(num) == 1;
};

bool BigDouble::operator>=(BigDouble& num) {
	int cmpResult = cmp(num);
	return cmpResult == 1 || cmpResult == 0;
};

bool BigDouble::operator< (BigDouble& num) {
	return cmp(num) == -1;
};

bool BigDouble::operator<=(BigDouble& num) {
	int cmpResult = cmp(num);
	return cmpResult == -1 || cmpResult == 0;
};