//header for rational class
#pragma once

#include <iostream>
#include <cmath>
#include <string>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;

class Rational {
public:
	//constructors, destructors
	Rational() { num = 0; den = 1; sgn = 1; }
	//newDen cannot equal 0
	Rational(int const newNum, int const newDen = 1);
	Rational(Rational const & original);
	~Rational() {}

	//assignment
	Rational & operator=(Rational const & rhs);

	//accessors, mutators
	unsigned int getNum() const { return num; }
	unsigned int getDen() const { return den; }
	int getSgn() const { return sgn; }

	void setNum(unsigned int const newNum) { num = newNum; }
	void setDen(unsigned int const newDen) { den = newDen; }
	//includes error message for invalid input
	void setSgn(int const newSgn);

	//methods
	//reduces fraction to lowest terms, requires findGCD
	void reduce();

private:
	unsigned int num;
	unsigned int den;
	// = +1 or -1 only
	int sgn;
};

istream & operator>>(istream & lhs, Rational & rhs);

ostream & operator<<(ostream & lhs, Rational const & rhs);

//returns greatest common divisor of n1 and n2
//implements Stein's algorithm for computational speed
unsigned int findGCD(int n1, int n2);

//also reduces result
Rational operator+(Rational const & lhs, Rational const & rhs);

//also reduces result
Rational operator-(Rational const & lhs, Rational const & rhs);

//also reduces result
Rational operator*(Rational const & lhs, Rational const & rhs);

//also reduces result
Rational operator/(Rational const & lhs, Rational const & rhs);

//checks to see if two rational numbers are equivalent
bool operator==(Rational const & lhs, Rational const & rhs);

