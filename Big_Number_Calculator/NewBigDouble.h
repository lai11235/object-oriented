#pragma once
class NewBigDouble : public BigNum
{
	private:
	BigDouble numerator;
	BigDouble denominator;
	public:
	NewBigDouble()
	{
		isDouble = true;
		isNewDouble = true;
	}

	NewBigDouble operator-()
	{
		numerator.isNegative = !numerator.isNegative;
		return *this;
	}
	
	void setNumerator(string numera)
	{
		numerator.setStrNum(numera);
		//cout << numerator;
	}

	void setDenominator(string denomin)
	{
		denominator.setStrNum(denomin);
	}

	void show()
	{
		cout << numerator << " / " << denominator << "\n";
	}
	
	bool operator==(NewBigDouble &num)
	{
		BigDouble Temp1 = numerator / denominator;
		BigDouble Temp2 = num.numerator / num.denominator;
		return Temp1 == Temp2;
	}

	operator BigDouble(void);

	NewBigDouble operator=(BigNum &num);

	friend NewBigDouble operator+(NewBigDouble num1, NewBigDouble num2);
	friend NewBigDouble operator+(BigInt num1, NewBigDouble num2);
	friend NewBigDouble operator+(NewBigDouble num2, BigInt num1);
	NewBigDouble operator+(BigDouble num);
	friend NewBigDouble operator-(NewBigDouble num1, NewBigDouble num2);
	friend NewBigDouble operator-(BigInt num1, NewBigDouble num2);
	friend NewBigDouble operator-(NewBigDouble num2, BigInt num1);
	NewBigDouble operator-(BigDouble num);
	friend NewBigDouble operator*(NewBigDouble num1, NewBigDouble num2);
	friend NewBigDouble operator*(BigInt num1, NewBigDouble num2);
	friend NewBigDouble operator*(NewBigDouble num2, BigInt num1);
	NewBigDouble operator*(BigDouble num);
	friend NewBigDouble operator/(NewBigDouble num1, NewBigDouble num2);
	friend NewBigDouble operator/(BigInt num1, NewBigDouble num2);
	friend NewBigDouble operator/(NewBigDouble num2, BigInt num1);
	NewBigDouble operator/(BigDouble num);
	friend class Expression;

	friend ostream& operator<<(ostream& strm, NewBigDouble num);
};
