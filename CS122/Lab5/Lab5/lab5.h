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
	Complex();
	//constructor, args
	Complex(double realInput, double imagInput);

	//big three:
	//copy constructor
	Complex(Complex & newComplex);
	//destructor
	~Complex();
	//overloaded assignment operator
	Complex & operator=(Complex const & rhs);
	//accessors
	double getReal();
	double getImag();
	//mutators

private:
	double realPart;
	double imagPart;

};