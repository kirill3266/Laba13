#include "Laba13.h"
#include <iostream>


int main() {
	Polynom a;
	a.input();
	Polynom b = a;
	b.output();
	if (b == a) std::cout << "Equal!\n";
	Polynom c = a * b;
	c.output();
	b.input();
	if (b < a) std::cout << "Smaller!\n";
	b += c;
	b.output();
	return 0;
}