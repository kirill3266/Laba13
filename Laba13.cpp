#include "Laba13.h"
#include <iostream>


Polynom::Polynom() {//+
	coef = nullptr;
	deg = 0;
}

Polynom::Polynom(const int right[], const int size) {
	deg = size;
	coef = new int[deg];
	for (int i = 0; i < deg; i++)
		coef[i] = right[i];
}

Polynom::Polynom(int size) {//+
	if (size > 0) {
		deg = size;
		coef = new int[deg];
		for (int i = 0; i < deg; i++) {
			coef[i] = 0;
		}
	}
	else if (size == 0) {
		deg = 0;
		coef = nullptr;
	}
}

Polynom::Polynom(const Polynom& right) {
	deg = right.deg;
	coef = new int[deg];
	for (int i = 0; i < deg; i++) coef[i] = right.coef[i];
}


Polynom Polynom::operator+(const Polynom& right) const {
	if (deg == 0) return Polynom();
	else if (right.deg == 0) return *this;
	int polynom_res_size = deg > right.deg ? deg : right.deg;
	Polynom polynom_res(polynom_res_size);
	if (deg == right.deg)
		for (int i = 0; i < deg; ++i)
			polynom_res.coef[i] = coef[i] + right.coef[i];
	else if (deg > right.deg) {
		int j = 0;
		for (int i = 0; i < deg; ++i)
			if (j < right.deg && i >= deg - right.deg)polynom_res.coef[i] = coef[i] + right.coef[j++];
			else polynom_res.coef[i] = coef[i];
	}
	else {
		int j = 0;
		for (int i = 0; i < right.deg; ++i)
			if (j < deg && i >= right.deg - deg)polynom_res.coef[i] = coef[j++] + right.coef[i];
			else polynom_res.coef[i] = right.coef[i];
	}
	int counter = 0;//счётчик нулей
	for (int i = 0; i < deg; i++)
		if (coef[i] == 0) {
			counter++;
		}
	if (counter == polynom_res.deg) {
		polynom_res.deg = 0;
		delete[]polynom_res.coef;
		polynom_res.coef = nullptr;
	}
	return  polynom_res;
}

Polynom Polynom::operator-(const Polynom& right) const {//+
	int mas[] = { -1 };
	return *this+right*Polynom(mas,1);
}

Polynom Polynom::operator*(const Polynom& right) const {//+
	if (deg == 0 || right.deg == 0) return Polynom();
	int polynom_res_size = deg + right.deg - 1;
	Polynom polynom_res(polynom_res_size);
	for (int i = 0; i < deg; ++i) {
		for (int j = 0; j < right.deg; ++j) {
			polynom_res.coef[i + j] += coef[i] * right.coef[j];
		}
	}
	return  polynom_res;
}

Polynom& Polynom::operator+=(const Polynom& right) {
	return *this = *this + right;
	
}

Polynom& Polynom::operator-=(const Polynom& right) {//+
	return *this = *this - right;
	
}

Polynom& Polynom::operator*=(const Polynom right) {
	return *this = *this * right;//++
}

Polynom& Polynom::operator=(const Polynom& right) {//+
	if (this == &right) {
		return *this;
	}
	if (right.deg > 0) {
		deg = right.deg;
		delete coef;
		coef = new int[deg];
		for (int i = 0; i < deg; i++)
			coef[i] = right.coef[i];
	}
	else {
		deg = 0;
		coef = nullptr;
	}
	return *this;
}

bool Polynom::operator==(const Polynom& right) const {//+
	return !(*this < right) && !(right < *this);
}

bool Polynom::operator!=(const Polynom& right) const {
	return !(*this == right);//+
}

bool Polynom::operator>(const Polynom& right) const {//+
	return !(*this < right) && (*this != right);
}

bool Polynom::operator<(const Polynom& right) const {//+
	if (deg > right.deg) return false;
	else for (int i = 0; i < deg; i++) {
		if (coef[i] == right.coef[i]) continue;
		if (coef[i] < right.coef[i]) return true;
	}
	return false;
}

bool Polynom::operator>=(const Polynom& right) const {//+
	return (*this == right) || (*this > right);
}

bool Polynom::operator<=(const Polynom& right) const {//+
	return (*this == right) || (*this < right);
}

void Polynom::input() {//+
	std::cout << "Vvodite coefficienti: To stop press 0\n";
	int ratio = 1;
	int N = 10;
	int v = 0;
	int* mas = new int[N];
	int* copy = nullptr;
	while (ratio != 0) {
		std::cin >> ratio;
		mas[v] = ratio;
		v++;
		if (v == N - 1) {
			N *= 10;
			copy = new int[N];
			for (int i = 0; i < v; i++)
				copy[i] = mas[i];
			delete mas;
			mas = new int[N];
			for (int i = 0; i < v; i++)
				mas[i] = copy[i];
			delete copy;
		}
	}
	std::cin.ignore(10000, '\n');
	int i;
	for (i = 0; mas[i] != 0; i++);
	deg = i;
	std::cout << "Deg is: " << deg << "\n";
	coef = new int[deg];
	for (int i = 0; i < deg; i++)
		coef[i] = mas[i];
	delete mas;
	std::cout << "Vvedenniy polinom is: ";
	output();
	std::cout << "\n";
}

void Polynom::output() {//+
	int j = 0;
	bool zero = true;
	for (int i = 0; i < deg; i++) {
		j = deg - i - 1;
		if (coef[i] != 0) {
			if (i != 0 && coef[i] >= 0 && zero == true) std::cout << "+";
			if (coef[i] != 1 && coef[i] != -1) {
				if (j > 1) std::cout << coef[i] << "X^" << j;
				else if (j == 1) std::cout << coef[i] << "X";
			}
			if (coef[i] == -1) {
				if (j > 1) std::cout << "-X^" << j;
				else if (j == 1) std::cout << "-X";
			}
			if (coef[i] == 1) {
				if (j > 1) std::cout << "X^" << j;
				else if (j == 1) std::cout << "X";
			}
			if (j == 0) std::cout << coef[i];
			zero = true;
		}
		else zero = false;
	}
	std::cout << "\n";
}

Polynom::~Polynom() {
	deg = 0;
	delete coef;
}
