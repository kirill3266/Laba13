#ifndef Laba13
#define Laba13

class Polynom
{
	int* coef;
	int deg;
public:
	Polynom();
	Polynom(const int right[],const int size);
	Polynom(const Polynom& right);
	Polynom(int deg);
	Polynom operator+(const Polynom& right) const;
	Polynom operator-(const Polynom& right) const;
	Polynom operator*(const Polynom& right) const;
	Polynom& operator+=(const Polynom& right);
	Polynom& operator-=(const Polynom& right);
	Polynom& operator*=(const Polynom right);
	Polynom& operator=(const Polynom& right);
	bool operator==(const Polynom& right) const;
	bool operator!=(const Polynom& right) const;
	bool operator>(const Polynom& right) const;
	bool operator<(const Polynom& right) const;
	bool operator>=(const Polynom& right) const;
	bool operator<=(const Polynom& right) const;
	void input();
	void output();
	~Polynom();
};
#endif