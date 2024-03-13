#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
#define useSelf auto& self = *this

template<typename T>
class MyVector : public vector<T> {
public:
	MyVector(int size = 0) : vector<T>(size) {

	}
	MyVector(int size, T initVal) : vector<T>(size, initVal) {

	}

	void reverse(void) {
		useSelf;
		for (int i = 0; i < self.size() / 2; i++) {
			T temp = self[i];
			self[i] = self[self.size() - 1 - i];
			self[self.size() - 1 - i] = temp;
		}
	}
	void sortThis(void) {
		useSelf;
		sort(self.begin(), self.end());
	}
	void rsortThis(void) {
		useSelf;
		sort(self.begin(), self.end(), greater<T>());
	}

	MyVector<T> getSubVec(int end) {
		useSelf;
		MyVector<T> subVec;
		for (int i = 0; i < end; i++) {
			subVec.push_back(self[i]);
		}
		return subVec;
	}
	MyVector<T> getSubVec(int from, int end) {
		useSelf;
		MyVector<T> subVec;
		for (int i = from; i < end; i++) {
			subVec.push_back(self[i]);
		}
		return subVec;
	}

	void operator+= (MyVector<T>& vec) {
		useSelf;
		for (auto& element : vec) {
			self.push_back(element);
		}
	}
	void operator+= (vector<T>& vec) {
		useSelf;
		for (auto& element : vec) {
			self.push_back(element);
		}
	}
	void operator+= (T element) {
		useSelf;
		self.push_back(element);
	}

	MyVector operator+ (MyVector<T>& vec) {
		useSelf;
		MyVector result = self;
		result += vec;
		return result;
	}
	MyVector operator+ (vector<T>& vec) {
		useSelf;
		MyVector result = self;
		result += vec;
		return result;
	}
	MyVector operator+ (T element) {
		useSelf;
		MyVector result = self;
		result += element;
		return result;
	}

	T& operator[] (int index) {
		useSelf;
		if (index < 0) {
			index += self.size();
		}
		if (index >= self.size()) {
			self.resize(index + 1);
		}
		return self.at(index);
	}

	friend ostream& operator<< (ostream& strm, MyVector vec) {
		strm << "{";
		for (int i = 0; i < vec.size() - 1; i++) {
			strm << vec[i] << ", ";
		}
		strm << vec.back() << "}";
		return strm;
	}
	//friend ostream& operator<< (ostream& strm, MyVector& vec) {
	//	strm << "{";
	//	for (int i = 0; i < vec.size() - 1; i++) {
	//		strm << vec[i] << ", ";
	//	}
	//	strm << vec.back() << "}";
	//	return strm;
	//}
};

template<typename T>
MyVector<T> operator+ (vector<T> vec1, vector<T> vec2) {
	MyVector<T> result;
	result += vec1;
	result += vec2;
	return result;
}

#endif
