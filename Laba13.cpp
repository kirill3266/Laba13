#include "Laba13.h"
#include <iostream>
#include <cmath>
Polynom::Polynom() {//+
	coef = nullptr;
	deg = 0;
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
	if (deg == 0) return Polynom();
	else if (right.deg == 0) return *this;
	int polynom_res_size = deg > right.deg ? deg : right.deg;
	Polynom polynom_res(polynom_res_size);
	if (deg == right.deg)
		for (int i = 0; i < deg; ++i)
			polynom_res.coef[i] = coef[i] - right.coef[i];
	else if (deg > right.deg) {
		int j = 0;
		for (int i = 0; i < deg; ++i)
			if (j < right.deg && i >= deg - right.deg)polynom_res.coef[i] = coef[i] - right.coef[j++];
			else polynom_res.coef[i] = coef[i];
	}
	else {
		int j = 0;
		for (int i = 0; i < right.deg; ++i)
			if (j < deg&&i>=right.deg-deg)polynom_res.coef[i] = coef[j++] - right.coef[i];
			else polynom_res.coef[i] = -right.coef[i];
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
	if (right.deg > 0 && deg == right.deg)//для одинаковых степеней
		for (int i = 0; i < right.deg; i++)
			coef[i] += right.coef[i];
	else if (right.deg > 0 && deg > 0 && deg != right.deg) {//для разных степеней
		if (deg < right.deg) {//увеличение *this для вывода результата
			int* buff = new int[deg];
			int buff_size = deg;
			for (int i = 0; i < deg; i++)
				buff[i] = coef[i];
			delete[] coef;
			coef = new int[right.deg];
			int j = buff_size - 1;
			for (int i = right.deg - 1; i > -1; i--) {
				if (i >= j && j >= 0) coef[i] = buff[j--];
				else coef[i] = 0;
			}
			delete[] buff;

			for (int i = 0; i < right.deg; i++)//непосредственно сложение??
				coef[i] += right.coef[i];
			deg = right.deg;
		}
		else {
			int j = 0;
			for (int i = deg - right.deg; i < deg; i++)
				if (j < right.deg) coef[i] += right.coef[j++];
		}
	}
	else if (right.deg == 0 || deg == 0)//не выполняет никаких операций, если один из компонентов не определён
		return *this;

	//определение  нулевых значений
	int counter = 0;//счётчик нулей
	for (int i = 0; i < deg; i++)
		if (coef[i] == 0) {
			counter++;
		}
	if (counter == deg) {
		deg = 0;
		delete[]coef;
		coef = nullptr;
	}
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& right) {//+
	if (right.deg > 0 && deg == right.deg)//для одинаковых степеней
		for (int i = 0; i < right.deg; i++)
			coef[i] -= right.coef[i];
	else if (right.deg > 0 && deg > 0 && deg != right.deg) {//для разных степеней
		if (deg < right.deg) {//увеличение *this для вывода результата
			int* buff = new int[deg];
			int buff_size = deg;
			for (int i = 0; i < deg; i++)
				buff[i] = coef[i];
			delete[] coef;
			coef = new int[right.deg];
			int j = buff_size - 1;
			for (int i = right.deg - 1; i > -1; i--) {
				if (i >= j && j >= 0) coef[i] = buff[j--];
				else coef[i] = 0;
			}
			delete[] buff;
			for (int i = right.deg - deg - 1; i < right.deg; i++)//непосредственно вычитание
				coef[i] -= right.coef[i];
			deg = right.deg;
		}
		else {
			int j = 0;
			for (int i = deg - right.deg; i < deg; i++)
				if (j < right.deg) coef[i] -= right.coef[j++];
		}
	}
	else if (right.deg == 0 || deg == 0)//не выполняет никаких операций, если один из компонентов не определён
		return *this;

	//определение  нулевых значений
	int counter = 0;//счётчик нулей
	for (int i = 0; i < deg; i++)
		if (coef[i] == 0) {
			counter++;
		}
	//if (counter > 0 && counter != deg) {
	//	int* buff = new int[deg - counter];
	//	int k = 0;
	//	for (int i = 0; i < deg; i++) //копирование без нулей
	//		if (coef[i] != 0) {
	//			buff[k] = coef[i];
	//			k++;
	//		}
	//	delete[] coef;
	//	deg -= counter;
	//	coef = new int[deg];
	//	for (int i = 0; i < deg; i++)
	//		coef[i] = buff[i];
	//	delete[] buff;
	//}
	if (counter == deg) {
		deg = 0;
		delete[]coef;
		coef = nullptr;
	}
	return *this;
}

Polynom& Polynom::operator*=(const Polynom right) {//++
	if (deg == 0 || right.deg == 0) return *this;
	int buff_size = deg + right.deg - 1;
	int* buff = new int[buff_size];
	for (int i = 0; i < buff_size; i++) buff[i] = 0;
	for (int i = 0; i < deg; ++i) {
		for (int j = 0; j < right.deg; ++j) {
			buff[i + j] += coef[i] * right.coef[j];
		}
	}
	delete[] coef;
	deg = buff_size;
	coef = new int[deg];
	for (int i = 0; i < deg; i++)
		coef[i] = buff[i];
	delete[] buff;
	return  *this;
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
	if (deg != right.deg) return false;
	else for (int i = 0; i < deg; i++)
		if (coef[i] != right.coef[i]) return false;
	return true;
}

bool Polynom::operator!=(const Polynom& right) const {//+
	int i;
	if (deg != right.deg) return true;
	else for (i = 0; i < deg && coef[i] == right.coef[i]; i++);
	return coef[i] - right.coef[i] == 0 ? false : true;
}
bool Polynom::operator>(const Polynom& right) const {//+
	if (deg < right.deg) return false;
	else for (int i = 0; i < deg; i++) {
		if (coef[i] == right.coef[i]) continue;
		if (coef[i] > right.coef[i]) return true;
	}
	return false;
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
	int i;
	if (deg < right.deg) return false;
	else for (i = 0; i < deg && coef[i] == right.coef[i]; i++);
	return coef[i] - right.coef[i] >= 0 ? true : false;
}

bool Polynom::operator<=(const Polynom& right) const {//+
	int i;
	if (deg > right.deg) return false;
	else for (i = 0; i < deg && coef[i] == right.coef[i]; i++);
	return coef[i] - right.coef[i] > 0 ? false : true;
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
		//std::cout << "Mas[" << v << "] is: " << mas[v] << "\n";
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
