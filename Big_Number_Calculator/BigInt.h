class BigInt :public BigNum {
	friend class BigDouble;
public:
	/***Assign***/
	BigInt operator=(long long num);
	BigInt operator=(int num);
	BigInt operator=(double num);
	BigInt operator=(const BigNum& num);
	BigInt operator=(const string& expression);

	/***Construct***/
	BigInt();
	BigInt(const long long& num);
	BigInt(const int& num);
	BigInt(const double& num);
	BigInt(const BigNum& copy);
	BigInt(const string& expression);
	void setStrNum(string strNum); //temp

	/***Convert***/
	operator long long(void);
	operator double(void);
	operator string(void);
	BigNum toBigNum(void);

	/***Compare***/
	int cmp(BigInt& num);
	bool operator==(BigInt& num);
	bool operator> (BigInt& num);
	bool operator>=(BigInt& num);
	bool operator< (BigInt& num);
	bool operator<=(BigInt& num);

	/***PlusAndMinus***/
	BigInt operator++(void);
	BigInt operator++(int);
	BigInt operator+(BigInt& num);
	void operator+=(BigInt num);
	BigInt operator--(void);
	BigInt operator--(int);
	BigInt operator-(BigInt& num);
	void operator-=(BigInt num);

	/***Multiply***/
	BigInt abs(void);
	BigInt x10(int exponent);
	BigInt xDigit(char& digit);
	BigInt operator*(BigInt& num);
	void operator*=(BigInt& num);
	BigInt factorial();

	/***Divide***/
	pair<BigInt, BigInt> divideResult(BigInt& num);
	BigInt operator/(BigInt& num);
	void operator/=(BigInt& num);
	BigInt operator%(BigInt& num);
	void operator%=(BigInt& num);
	//BigNum pow(BigNum exponent);
	

	/***IOstream***/
	friend ostream& operator<< (ostream& strm, BigInt num);
	friend istream& operator>> (istream& strm, BigInt& num);
};

//BigInt operator-(BigInt& num);


