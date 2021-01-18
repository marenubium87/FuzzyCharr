//source file for lab 5

#include "lab5.h"

//constructor, no args
Complex::Complex() {
	realPart = 0.0;
	imagPart = 0.0;
}

//constructor, args
Complex::Complex(double realInput, double imagInput) {
	realPart = realInput;
	imagPart = imagInput;
}

//copy constructor
Complex::Complex(Complex & newComplex) {
	realPart = newComplex.realPart;
	imagPart = newComplex.imagPart;
}

//destructor
Complex::~Complex() {

}

//overloaded assignment operator
Complex & Complex::operator=(Complex const & rhs) {
	realPart = rhs.realPart;
	imagPart = rhs.imagPart;
	return *this;
}

//accessors
double Complex::getReal() {
	return realPart;
}

double Complex::getImag() {
	return imagPart;
}

//mutators
