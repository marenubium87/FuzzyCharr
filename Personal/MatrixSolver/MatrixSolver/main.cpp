//matrix solver project
//2 Feb 2021

#include "rational.h"
#include "tests.h"
#include "matrix.h"

int main() {
	
	Rational r1(0, 1);
	//Matrix A(3, 4);
	Matrix B;
	//doThings(B);
	
	Matrix A;
	fstream input("input.txt", std::ios::in);
	input >> A;
	//cout << A;
	
	A.rref();
	
	//Rational r1;
	//cin >> r1;
	//cout << endl << r1;
	
	system("pause");
	return 0;
}