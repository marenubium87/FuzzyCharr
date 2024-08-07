//source file for lab 5

#include "lab5.h"

//constructor, no args
//Complex::Complex() {
//	realPart = 0.0;
//	imagPart = 0.0;
//}

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
double Complex::getReal() const {
	return realPart;
}

double Complex::getImag() const {
	return imagPart;
}

//mutators
void Complex::setReal(double const newReal) {
	realPart = newReal;
}

void Complex::setImag(double const newImag) {
	imagPart = newImag;
}

//read from user input
void Complex::read() {
	char tempCharr = '\0';
	cin >> realPart >> tempCharr >> imagPart;
	if (tempCharr == '-') {
		imagPart = -imagPart;
	}
	cin >> tempCharr;
}

//output to console
void Complex::print() const {
	cout << realPart;
	if (imagPart >= 0) {
		cout << " + ";
	}
	else {
		cout << " - ";
	}
	cout << abs(imagPart) << 'i';
}

//member add fcn
Complex & Complex::add(Complex const & rhs) {
	realPart += rhs.realPart;
	imagPart += rhs.imagPart;
	return *this;
}

//non-member add fcn
Complex add(Complex const & c1, Complex const & c2) {
	Complex sum;
	sum.setReal(c1.getReal() + c2.getReal());
	sum.setImag(c1.getImag() + c2.getImag());
	return sum;
}

//overloaded + operator
Complex operator+(Complex const & lhs, Complex const & rhs) {
	Complex sum;
	sum.setReal(lhs.getReal() + rhs.getReal());
	sum.setImag(lhs.getImag() + rhs.getImag());
	return sum;
}

//overloaded - operator
Complex operator-(Complex const & lhs, Complex const & rhs) {
	Complex difference;
	difference.setReal(lhs.getReal() - rhs.getReal());
	difference.setImag(lhs.getImag() - rhs.getImag());
	return difference;
}

//overloaded >> operator
istream & operator>>(istream & lhs, Complex & rhs) {
	
	char tempCharr = '\0';
	double tempNum = 0.0;

	//extract real part
	cin >> tempNum;
	rhs.setReal(tempNum);

	//extract imag part
	cin >> tempCharr;
	cin >> tempNum;
	if (tempCharr == '-') {
		tempNum = -tempNum;
	}
	rhs.setImag(tempNum);

	//clear 'i' symbol
	cin >> tempCharr;
	return lhs;
}

//overloaded << operator
ostream & operator<<(ostream & lhs, Complex const & rhs) {
	cout << rhs.getReal();
	if (rhs.getImag() >= 0) {
		cout << " + ";
	}
	else {
		cout << " - ";
	}
	cout << abs(rhs.getImag()) << 'i';
	return lhs;
}