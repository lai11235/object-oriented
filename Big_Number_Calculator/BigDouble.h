class BigDouble :public BigNum{
public:
	/***Assign***/
	BigDouble operator=(long long num);
	BigDouble operator=(int num);
	BigDouble operator=(double num);
	BigDouble operator=(const BigInt& num);
	BigDouble operator=(const BigNum& num);
	BigDouble operator=(const string& expression);

	/***Construct***/
	BigDouble(int _decimalSize = 100);
	BigDouble(const long long& num, int _decimalSize = 100);
	BigDouble(const int& num, int _decimalSize = 100);
	BigDouble(const double& num, int _decimalSize = 100);
	BigDouble(const BigInt& copy, int _decimalSize = 100);
	BigDouble(const BigNum& copy, int _decimalSize = 100);
	BigDouble(const BigDouble& copy, int _decimalSize = 100);
	BigDouble(const string& expression, int _decimalSize = 100);
	void setStrNum(string strNum); //temp

	/***Convert***/
	operator long long(void);
	operator double(void);
	operator BigInt(void);
	operator string(void);
	BigNum toBigNum(void);

	/***DecimalControl***/
	int getDecimalSize(void);
	int intPartSize(void);
	int decimalLen(void);
	void extentDeciSize(int toSize);
	void shortDeciSize(int toSize);
	void setDeciSize(int toSize);

	/***Compare***/
	int cmp(BigDouble& num);
	bool operator==(BigDouble& num);
	bool operator> (BigDouble& num);
	bool operator>=(BigDouble& num);
	bool operator< (BigDouble& num);
	bool operator<=(BigDouble& num);

	/***PlusAndMinus***/
	BigDouble operator++(void);
	BigDouble operator++(int);
	BigDouble operator+(BigDouble& num);
	void operator+=(BigDouble num);
	BigDouble operator--(void);
	BigDouble operator--(int);
	BigDouble operator-(BigDouble& num);
	void operator-=(BigDouble num);

	/***MultiplyAndDivide***/
	BigDouble abs(void);
	BigDouble x10(int exponent);
	BigDouble xDigit(char& exponent);
	BigDouble operator*(BigDouble& num);
	void operator*=(BigDouble& num);
	BigDouble operator/(BigDouble& num);
	void operator/=(BigDouble& num);
	//BigDouble pow(BigDouble exponent);

	/***IOstream***/
	friend ostream& operator<< (ostream& strm, BigDouble num);
	friend istream& operator>> (istream& strm, BigDouble& num);
};
