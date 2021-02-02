//source for rational class

#include "rational.h"

//constructor
//precondition:  newDen cannot be zero
Rational::Rational(int const newNum, int const newDen) {
	sgn = 1;

	if (newDen == 0) {
		cout << "Error creating rational; denominator cannot be zero" << endl;
	}
	else if (newDen < 0) {
		sgn = -sgn;
		den = -newDen;
	}
	else {
		den = newDen;
	}

	if (newNum < 0) {
		sgn = -sgn;
		num = -newNum;
	}
	else {
		num = newNum;
	}
}

//copy constructor
Rational::Rational(Rational const & original) {
	*this = original;
}

//assignment
Rational & Rational::operator=(Rational const & rhs) {
	num = rhs.num;
	den = rhs.den;
	sgn = rhs.sgn;
	return *this;
}

//includes error message for invalid input
void Rational::setSgn(int const newSgn) {
	if (newSgn != 1 && newSgn != -1) {
		cout << "Error in fcn: setSgn" << endl << "intput is " << newSgn
			<< ", +1 or -1 expected" << endl;
		return;
	}
	sgn = newSgn;
}

//reads rational input from console
istream & operator>>(istream & lhs, Rational & rhs) {
	char tempCharr = '\0';
	int tempInt = 0;
	cin >> tempInt;
	if (tempInt < 0) {
		rhs.setSgn(-1);
		rhs.setNum(-tempInt);
	}
	else
	{
		rhs.setSgn(1);
		rhs.setNum(tempInt);
	}

	//did the user only enter a whole number?  no problem, let's check.
	if (cin.peek() == '\n') {
		rhs.setDen(1);
	}
	else {
		cin >> tempCharr;
		cin >> tempInt;
		if (tempInt == 0) {
			cout << endl << "Error: denominator cannot be zero." << endl;
			cout << "Probable unreliable output beyond this point." << endl;
		}
		else if (tempInt < 0) {
			rhs.setSgn(rhs.getSgn() * -1);
			rhs.setDen(-tempInt);
		}
		else {
			rhs.setDen(tempInt);
		}
	}

	return lhs;
}

//displays rational to console
ostream & operator<<(ostream & lhs, Rational const & rhs) {
	if (rhs.getSgn() == -1) {
		cout << "-";
	}
	cout << rhs.getNum();
	if (rhs.getDen() != 1) {
		cout << "/" << rhs.getDen();
	}
	return lhs;
}