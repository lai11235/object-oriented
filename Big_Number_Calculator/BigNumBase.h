#pragma once
class BigNum {
	friend class BigInt;
	friend class BigDouble;
	friend class NewBigDouble;

protected:
	vector<char> digits = { 0 };
	vector<char> numerator = { 0 };
	vector<char> denominator = { 0 };

	bool isNegative = false;
	bool isDouble = false;
	bool isNewDouble = false;
	int decimalSize = 0;
	int stringDecimalSize = 0;
public:
	static string getNumStr(istream& strm = cin) {
		while (strm.peek() == ' ' || strm.peek() == '\n') {
			char temp = strm.get();
		}

		string numStr;
		if (strm.peek() == '+') {
			char temp = strm.get();
		}
		if (strm.peek() == '-') {
			numStr.push_back(strm.get());
		}

		bool havePoint = false;
		int numCnt = 0;
		while ((strm.peek() >= '0' && strm.peek() <= '9') || strm.peek() == '.') {

			if (strm.peek() == '.') {
				if (havePoint) {
					break;
				}
				if (numCnt == 0) {
					numStr.push_back('0');
				}
				numStr.push_back(strm.get());
				havePoint = true;
			}

			else {
				numStr.push_back(strm.get());
				numCnt++;
			}
		}

		if (numStr.back() == '.') {
			numStr.pop_back();
		}

		return numCnt == 0 ? "0" : numStr;
	}
	string getNumberString()
	{
		string num = "";

		bool flag = false;
		if (!isDouble)
			flag = true;
		for (int i = 0; i < digits.size(); i++)
		{
			if ((!flag && digits[i]))
			{
				flag = true;
				i--;
			}

			else if(flag)
				num += digits[i];
		}
		
		int size = num.size();

		for (int i = 0; i < size / 2; i++)
		{
			swap(num[i], num[size - i - 1]);
		}

		return num;
	}
	int getRealDecimalSize()
	{
		if (isDouble)
		{
			int dSize = 100;

			for (int i = 0; i < digits.size(); i++)
			{
				if (digits[i] != 0  || !dSize)
					break;
				dSize--;
			}

			return dSize;
		}

		else
			return 0;
	}
	void clearBackZero(void) {
		while (digits.back() == 0 && (digits.size() - decimalSize) > 1) {
			digits.pop_back();
		}
	}
	bool isInteger(void){
		return !isDouble;
	}
	bool isPositive(void) {
		return !isNegative;
	}
	void toOppositeSign()
	{
		isNegative = !isNegative;
	}
	char digitValue(int index)
	{
		return digits[index];
	}
	int digitSize()
	{
		return digits.size();
	}
	const static int INT_TYPE = 0;
	const static int DOUBLE_TYPE = 1;
	friend int toSameType(BigNum& num1, BigNum& num2);

	friend bool operator== (BigNum num1, BigNum num2);
	friend bool operator>  (BigNum num1, BigNum num2);
	friend bool operator>= (BigNum num1, BigNum num2);
	friend bool operator<  (BigNum num1, BigNum num2);
	friend bool operator<= (BigNum num1, BigNum num2);

	friend BigNum operator+  (BigNum num1, BigNum num2);
	friend void operator+= (BigNum num1, BigNum num2);
	friend BigNum operator-  (BigNum num1, BigNum num2);
	friend void operator-= (BigNum num1, BigNum num2);
	friend BigNum operator*  (BigNum num1, BigNum num2);
	friend void operator*= (BigNum num1, BigNum num2);
	friend BigNum operator/  (BigNum num1, BigNum num2);
	friend void operator/= (BigNum num1, BigNum num2);
	friend BigNum operator%  (BigNum num1, BigNum num2);
	friend void operator%= (BigNum num1, BigNum num2);
	friend BigNum abs(BigNum num1);
	friend BigNum Sqrt(BigNum num1);

	BigNum operator-();
	BigNum operator+();

	friend ostream& operator<< (ostream& strm, BigNum num);
	friend istream& operator>> (istream& strm, BigNum& num);
};
