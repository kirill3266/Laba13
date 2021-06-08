#include "Laba13.h"
#include <iostream>

int main() {
	int masA[] = { 1,2,3,4 };
	Polynom a(masA,4);
	int masB[] = { 4,3,2,1 };
	Polynom b(masB,4);
	if (b == a) std::cout << "B Equal A!\n";
	else std::cout << "B Not Equal A!\n";
	Polynom c = b;
	if (c != a) std::cout << "C Not equal A!\n";
	if (a > b) std::cout << "A > B\n";
	if (b >= c) std::cout << "B >= C\n";
	if (b < a) std::cout << "B < A\n";
	c -= a;
	c.output();
	c += a;
	c.output();
	c *= a;
	c.output();
	c = b * a;
	c.output();
	b = c - a;
	b.output();
	b = c + a;
	b.output();
	return 0;
}