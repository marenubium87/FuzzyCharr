//source for rational class

#include "rational.h"

//constructor
//precondition:  newDen cannot be zero
Rational::Rational(int const newNum, int const newDen) {
	sign = 1;

	if (newDen == 0) {
		cout << "Error creating rational; denominator cannot be zero" << endl;
		cout << "Setting rational to zero instead, and aborting." << endl;
		num = 0;
		den = 1;
		return;
	}
	else if (newDen < 0) {
		sign = -sign;
		den = -newDen;
	}
	else {
		den = newDen;
	}

	if (newNum < 0) {
		sign = -sign;
		num = -newNum;
	}
	else {
		num = newNum;
		//fixes an issue where "-0" could be a valid output
		if (num == 0) {
			sign = 1;
		}
	}
	//call reduce here
	this->reduce();
}

//copy constructor
Rational::Rational(Rational const & original) {
	*this = original;
}

//assignment
Rational & Rational::operator=(Rational const & rhs) {
	num = rhs.num;
	den = rhs.den;
	sign = rhs.sign;
	return *this;
}

//sets numerator, adjusts sign as necessary
//num attribute should always be positive
//also reduces fraction by result, can force not to reduce for speed
void Rational::setNum(int const newNum, int reduce) {
	if (newNum < 0) {
		sign = -1;
		num = -newNum;
	}
	//numerator is non-negative
	else {
		sign = 1;
		num = newNum;
	}
	if (reduce) {
		this->reduce();
	}
}

//sets denominator, adjusts sign as necessary
//den attribute should always be positive
//also reduces fraction by result, can force not to reduce for speed
void Rational::setDen(int const newDen, int reduce) {
	if (newDen == 0) {
		cout << "Error in fcn: setDen" << endl;
		cout << "Denominator cannot be zero" << endl;
		cout << "No changes made." << endl;
		return;
	}
	else if (newDen < 0) {
		sign = -1;
		den = -newDen;
	}
	//denom is positive
	else {
		sign = 1;
		den = newDen;
	}
	if (reduce) {
		this->reduce();
	}
}

//includes error message for invalid input
void Rational::setSign(int const newSign) {
	if (newSign != 1 && newSign != -1) {
		cout << "Error in fcn: setSign" << endl << "input is " << newSign
			<< ", +1 or -1 expected" << endl << "No changes made." << endl;
		return;
	}
	//avoids creating "-0" for outputs
	if (num == 0) {
		return;
	}
	sign = newSign;
}

//sets a new value for a rational
void Rational::setVal(int const newNum, int const newDen, int reduce) {
	
	if (newDen == 0) {
		cout << "Error in fcn: setVal" << endl;
		cout << "Denominator cannot be zero" << endl;
		cout << "No changes made." << endl;
		return;
	}

	//assume sign is +1 and adjust as necessary
	sign = 1;

	if (newNum < 0) {
		sign *= -1;
		num = -newNum;
	}
	else {
		num = newNum;
	}

	if (newDen < 0) {
		sign *= -1;
		den = -newDen;
		//prevents degenerate forms such as -0
		if (num == 0) {
			sign = 1;
		}
	}
	else {
		den = newDen;
	}

	if (reduce) {
		this->reduce();
	}
}

//reduces fraction to lowest terms, requires findGCD
void Rational::reduce() {
	//whole number, already reduced, do nothing
	if (den == 1) {
		return;
	}

	//if the numerator is zero, then lowest form is 0/1
	if (num == 0) {
		sign = 1;
		den = 1;
		return;
	}

	int GCD = findGCD(num, den);
	num /= GCD;
	den /= GCD;
}

//reads rational input from console
istream & operator>>(istream & lhs, Rational & rhs) {
	char tempCharr = '\0';
	int tempInt = 0;
	cin >> tempInt;
	if (tempInt < 0) {
		rhs.setSign(-1);
		rhs.setNum(-tempInt);
	}
	else
	{
		rhs.setSign(1);
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
			rhs.setSign(rhs.getSign() * -1);
			rhs.setDen(-tempInt);
		}
		else {
			rhs.setDen(tempInt);
		}
	}

	//reduces fraction
	if (rhs.getDen() > 1) {
		rhs.reduce();
	}

	return lhs;
}

//reads rational from file
fstream & operator>>(fstream & lhs, Rational & rhs) {
	char tempCharr = '\0';
	int tempInt = 0;
	lhs >> tempInt;
	if (tempInt < 0) {
		rhs.setSign(-1);
		rhs.setNum(-tempInt);
	}
	else
	{
		rhs.setSign(1);
		rhs.setNum(tempInt);
	}

	//did the user only enter a whole number?  no problem, let's check.
	if (lhs.peek() == ' ') {
		rhs.setDen(1);
	}
	else {
		lhs >> tempCharr;
		lhs >> tempInt;
		if (tempInt == 0) {
			cout << endl << "Error: denominator cannot be zero." << endl;
			cout << "Probable unreliable output beyond this point." << endl;
		}
		else if (tempInt < 0) {
			rhs.setSign(rhs.getSign() * -1);
			rhs.setDen(-tempInt);
		}
		else {
			rhs.setDen(tempInt);
		}
	}

	//reduces fraction
	if (rhs.getDen() > 1) {
		rhs.reduce();
	}

	return lhs;
}

//displays rational to console
ostream & operator<<(ostream & lhs, Rational & rhs) {
	if (rhs.getSign() == -1) {
		cout << "-";
	}
	else {
		cout << " ";
	}
	cout << setw(NUM_PADDING) << rhs.getNum();
	if (rhs.getDen() != 1 && rhs.getNum() != 0) {
		cout << "/" << setw(DEN_PADDING) << rhs.getDen();
	}
	else {
		for (int i = 0; i < DEN_PADDING + 1; i++) {
			cout << " ";
		}
	}
	return lhs;
}

//returns greatest common divisor of n1 and n2
//implements Stein's algorithm for computational speed
//precondition - n1 > 0, n2 > 0
int findGCD(int n1, int n2) {
	//checks precondition - if fails prints warning and returns 0
	//(which is never a valid GCD)
	if (n1 <= 0 || n2 <= 0) {
		cout << "Warning: invalid arguments (<= 0) in find GCD" << endl;
		cout << "Function did not execute; returning 0" << endl;
		return 0;
	}

	//if the two numbers are equal to each other then they
	//are by definition the GCD
	if (n1 == n2) {
		return n1;
	}

	int commonPowersOfTwo = 0;
	//if both numbers still even
	while (n1 % 2 == 0 && n2 % 2 == 0) {
		n1 = n1 >> 1;
		n2 = n2 >> 1;
		commonPowersOfTwo++;
	}

	//if one number still even
	while (n1 % 2 == 0) {
		n1 = n1 >> 1;
	}
	while (n2 % 2 == 0) {
		n2 = n2 >> 1;
	}

	//both numbers now odd
	//assign n1 to c so that if n1 = n2 already that will simply be the
	//non-powers of 2 component of the GCD
	int c = n1;
	while (n1 != n2) {
		//c is the (positive) difference between n1 and n2
		//premise of Stein's alg: GCD(smaller of n1 and n2, c) is the same
		//as GCD(n1, n2), so replace the larger of n1 and n2 by c
		
		c = n1 - n2;
		//c cannot be 0 here b/c that would imply n1 == n2 earlier
		if (c < 0) {
			c *= -1;
		}
		//c is guaranteed to be even right now, so bitshift c
		while (c % 2 == 0) {
			c = c >> 1;
		}
		//figure out which one to replace
		if (n1 > n2) {
			n1 = c;
		}
		else {
			n2 = c;
		}
	}
	//at this point n1 = n2 = c 
	//GCD is now c * 2 ^ (commonPowersOfTwo)
	int GCD = c << commonPowersOfTwo;
	return GCD;
}

//also reduces result
Rational operator+(Rational const & lhs, Rational const & rhs) {
	int tempInt = 0;
	Rational result;
	//assume sign is positive, fix later if necessary
	result.setSign(1);
	//for a/b + c/d, denom is simple b*d, will reduce later
	result.setDen(lhs.getDen() * rhs.getDen());
	//figure out numerator, including negative signs
	tempInt = lhs.getSign() * lhs.getNum() * rhs.getDen() +
		rhs.getSign() * rhs.getNum() * lhs.getDen();
	//is what will be the numerator negative?
	if (tempInt < 0) {
		result.setSign(-1);
		tempInt = -tempInt;
	}
	result.setNum(tempInt);
	result.reduce();
	return result;
}

//also reduces result
Rational operator-(Rational const & lhs, Rational const & rhs) {
	int tempInt = 0;
	Rational result;
	//assume sign is positive, fix later if necessary
	result.setSign(1);
	//for a/b + c/d, denom is simple b*d, will reduce later
	result.setDen(lhs.getDen() * rhs.getDen());
	//figure out numerator, including negative signs
	tempInt = lhs.getSign() * lhs.getNum() * rhs.getDen() -
		rhs.getSign() * rhs.getNum() * lhs.getDen();
	//is what will be the numerator negative?
	if (tempInt < 0) {
		result.setSign(-1);
		tempInt = -tempInt;
	}
	result.setNum(tempInt);
	result.reduce();
	return result;
}

//also reduces result
Rational operator*(Rational const & lhs, Rational const & rhs) {
	Rational result;
	result.setSign(lhs.getSign() * rhs.getSign());
	result.setNum(lhs.getNum() * rhs.getNum());
	result.setDen(lhs.getDen() * rhs.getDen());
	result.reduce();
	return result;
}

//also reduces result
Rational operator/(Rational const & lhs, Rational const & rhs) {
	Rational result;
	result.setSign(lhs.getSign() * rhs.getSign());
	result.setNum(lhs.getNum() * rhs.getDen());
	result.setDen(lhs.getDen() * rhs.getNum());
	result.reduce();
	return result;
}

//checks to see if two rational numbers are equivalent
bool operator==(Rational & lhs, Rational & rhs) {
	if (lhs.getSign() * lhs.getNum() * rhs.getDen() ==
		rhs.getSign() * rhs.getNum() * lhs.getDen()) {
		return true;
	}
	else {
		return false;
	}
}

//checks to see if two rational numbers are not equivalent
bool operator!=(Rational & lhs, Rational & rhs) {
	return !(lhs == rhs);
}

bool operator>=(Rational & lhs, Rational & rhs) {
	if (lhs.getSign() * lhs.getNum() * rhs.getDen() >=
		rhs.getSign() * rhs.getNum() * lhs.getDen()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<=(Rational & lhs, Rational & rhs) {
	if (lhs.getSign() * lhs.getNum() * rhs.getDen() <=
		rhs.getSign() * rhs.getNum() * lhs.getDen()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>(Rational & lhs, Rational & rhs) {
	return !(lhs <= rhs);
}

bool operator<(Rational & lhs, Rational & rhs) {
	return !(lhs >= rhs);
}