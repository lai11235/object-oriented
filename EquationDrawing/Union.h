#ifndef UNION_H
#define UNION_H

#include <iostream>
#include <string>
using namespace std;

typedef char******** no_type;
template<typename T1, typename T2, typename T3>
class Union {
protected:
	T1* type1 = 0;
	T2* type2 = 0;
	T3* type3 = 0;
	int nowType = 0;
public:
	Union() {
		nowType = 0;
	}
	Union(const Union& copy) {
		type1 = 0;
		type2 = 0;
		type3 = 0;
		nowType = 0;
		if (copy.type() == 1) {
			type1 = new T1;
			*type1 = copy.t1();
			nowType = 1;
		}
		else if (copy.type() == 2) {
			type2 = new T2;
			*type2 = copy.t2();
			nowType = 2;
		}
		else if (copy.type() == 3) {
			type3 = new T3;
			*type3 = copy.t3();
			nowType = 3;
		}
	}

	void clearAll(void) {
		if (type1) {
			delete type1;
			type1 = 0;
		}
		if (type2) {
			delete type2;
			type2 = 0;
		}
		if (type3) {
			delete type3;
			type3 = 0;
		}
		nowType = 0;
	}
	//~Union() {
	//	clearAll();
	//}

	int type(void) const {
		return nowType;
	}

	void setType1(void) {
		clearAll();
		type1 = new T1;
		nowType = 1;
	}
	void setType1(T1 _data) {
		setType1();
		*type1 = _data;
	}
	void setType2(void) {
		clearAll();
		type2 = new T2;
		nowType = 2;
	}
	void setType2(T2 _data) {
		setType2();
		*type2 = _data;
	}
	void setType3(void) {
		clearAll();
		type3 = new T3;
		nowType = 3;
	}
	void setType3(T3 _data) {
		setType3();
		*type3 = _data;
	}

	T1& t1(void) {
		if (nowType != 1) setType1();
		return *type1;
	}
	T1 t1(void) const {
		if (nowType != 1) cerr << "wrong type\n";
		return *type1;
	}
	T2& t2(void) {
		if (nowType != 2) setType2();
		return *type2;
	}
	T2 t2(void) const {
		if (nowType != 2) cerr << "wrong type\n";
		return *type2;
	}
	T3& t3(void) {
		if (nowType != 3) setType3();
		return *type3;
	}
	T3 t3(void) const {
		if (nowType != 3) cerr << "wrong type\n";
		return *type3;
	}

	friend istream& operator>> (istream& strm, Union& un) {
		if (un.nowType == 1) {
			strm >> *(un.type1);
		}
		else if (un.nowType == 2) {
			strm >> *(un.type2);
		}
		else if (un.nowType == 3) {
			strm >> *(un.type3);
		}
		return strm;
	}
	friend ostream& operator<< (ostream& strm, Union& un) {
		if (un.nowType == 1) {
			strm << *(un.type1);
		}
		else if (un.nowType == 2) {
			strm << *(un.type2);
		}
		else if (un.nowType == 3) {
			strm << *(un.type3);
		}
		else {
			strm << "None Type";
		}
		return strm;
	}
};

#endif

