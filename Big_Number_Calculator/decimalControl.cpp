#include "libraries.h"

int BigDouble::getDecimalSize(void) {
	return decimalSize;
};

int BigDouble::intPartSize(void) {
	return digits.size() - decimalSize;
};

int BigDouble::decimalLen(void) {
	int zeroCnt = 0;
	while (digits[zeroCnt] == 0 && zeroCnt < decimalSize) {
		zeroCnt++;
	}
	return decimalSize - zeroCnt;
}

void BigDouble::extentDeciSize(int toSize) {
	while (decimalSize < toSize) {
		digits.insert(digits.begin(), 0);
		decimalSize++;
	}
}

void BigDouble::shortDeciSize(int toSize) {
	while (decimalSize > toSize) {
		digits.erase(digits.begin());
		decimalSize--;
	}
}

void BigDouble::setDeciSize(int toSize) {
	while (decimalSize < toSize) {
		digits.insert(digits.begin(), 0);
		decimalSize++;
	}
	while (decimalSize > toSize) {
		digits.erase(digits.begin());
		decimalSize--;
	}
}