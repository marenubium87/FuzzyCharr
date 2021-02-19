//header for rational class
#pragma once

//number of spaces to pad numerator and denominator
//should be at least the number of digits of the largest numerator/denominator
#define NUM_PADDING 4
#define DEN_PADDING 4

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
	//if single argument is input, will assume whole number
	Rational(int const newNum, int const newDen = 1);
	Rational(Rational const & original);
	~Rational() {}

	//assignment
	Rational & operator=(Rational const & rhs);

	//accessors, mutators
	int getNum() const { return num; }
	int getDen() const { return den; }
	int getSign() const { return sign; }

	//sets attribute but also adjusts sign as necessary so that
	//num and den are always positive
	//also reduces fraction by result, can force not to reduce for speed
	void setNum(int const newNum, int reduce = 1);
	//also includes error checking when newDen = 0
	void setDen(int const newDen, int reduce = 1);
	
	//includes error message for invalid input
	void setSign(int const newSign);
	//assigns a rational to a new value
	//also includes error checking when newDen = 0
	//also reduces fraction by result, can force not to reduce for speed
	//will set to whole number if single argument is input
	void setVal(int const newNum, int const newDen = 1, int reduce = 1);

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
//throws error and aborts operation if rhs = 0
Rational operator/(Rational const & lhs, Rational const & rhs);

//checks to see if two rational numbers are equivalent
bool operator==(Rational & lhs, Rational & rhs);

//checks to see if two rational numbers are not equivalent
bool operator!=(Rational & lhs, Rational & rhs);

bool operator>=(Rational & lhs, Rational & rhs);

bool operator<=(Rational & lhs, Rational & rhs);

bool operator>(Rational & lhs, Rational & rhs);

bool operator<(Rational & lhs, Rational & rhs);