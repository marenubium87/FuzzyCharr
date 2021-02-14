//header for rational class
#pragma once

//number of spaces to pad numerator and denominator
//should be at least the number of digits of the largest numerator/denominator
#define NUM_PADDING 2
#define DEN_PADDING 2

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;
using std::fstream;

class Rational {
public:
	//constructors, destructors
	Rational() { num = 0; den = 1; sign = 1; }
	//newDen cannot equal 0
	Rational(int const newNum, int const newDen = 1);
	Rational(Rational const & original);
	~Rational() {}

	//assignment
	Rational & operator=(Rational const & rhs);

	//accessors, mutators
	int getNum() const { return num; }
	int getDen() const { return den; }
	int getSign() const { return sign; }

	void setNum(int const newNum);
	void setDen(int const newDen);
	//includes error message for invalid input
	void setSign(int const newSign);
	//assigns a rational to a new value
	void setVal(int const newSign, int const newNum, int const newDen);

	//methods
	//reduces fraction to lowest terms, requires findGCD
	void reduce();

private:
	int num;
	int den;
	// = +1 or -1 only
	int sign;
};

//reads rational from console
istream & operator>>(istream & lhs, Rational & rhs);

//reads rational from file
fstream & operator>>(fstream & lhs, Rational & rhs);

//displays rational to console
ostream & operator<<(ostream & lhs, Rational & rhs);

//returns greatest common divisor of n1 and n2
//implements Stein's algorithm for computational speed
int findGCD(int n1, int n2);

//also reduces result
Rational operator+(Rational const & lhs, Rational const & rhs);

//also reduces result
Rational operator-(Rational const & lhs, Rational const & rhs);

//also reduces result
Rational operator*(Rational const & lhs, Rational const & rhs);

//also reduces result
Rational operator/(Rational const & lhs, Rational const & rhs);

//checks to see if two rational numbers are equivalent
bool operator==(Rational & lhs, Rational & rhs);

//checks to see if two rational numbers are not equivalent
bool operator!=(Rational & lhs, Rational & rhs);

bool operator>=(Rational & lhs, Rational & rhs);

bool operator<=(Rational & lhs, Rational & rhs);

bool operator>(Rational & lhs, Rational & rhs);

bool operator<(Rational & lhs, Rational & rhs);