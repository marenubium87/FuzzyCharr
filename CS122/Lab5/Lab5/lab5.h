//header file for lab 5

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

//complex number class
class Complex {

public:
	//constructor, no args
	//Complex();
	//constructor, args
	Complex(double realInput = 0.0, double imagInput = 0.0);

	//big three:
	//copy constructor
	Complex(Complex & newComplex);
	//destructor
	~Complex();
	//overloaded assignment operator
	Complex & operator=(Complex const & rhs);
	//accessors
	double getReal() const;
	double getImag() const;
	//mutators
	void setReal(double const newReal);
	void setImag(double const newImag);

	//read from user input
	void read();

	//output to console
	void print() const;

	//adding, member fcn
	Complex & add(Complex const & rhs);

private:
	double realPart;
	double imagPart;
};

//non-member add fcn
Complex add(Complex const & c1, Complex const & c2);

//non-member overloaded + operator
Complex operator+(Complex const & lhs, Complex const & rhs);

//(non-member) overloaded - operator
Complex operator-(Complex const & lhs, Complex const & rhs);

//overloaded >> operator
istream & operator>>(istream & lhs, Complex & rhs);

//overloaded << operator
ostream & operator<<(ostream & lhs, Complex const & rhs);