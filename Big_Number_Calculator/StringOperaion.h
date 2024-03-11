#pragma once
#include "libraries.h"

BigInt operator-(string int1, string int2)
{
	BigInt Int1(int1);
	BigInt Int2(int2);
	BigInt Ans = Int1 - Int2;
	cout << Ans;
	return Ans;
}
