//matrix solver project
//2 Feb 2021

#include "rational.h"
#include "tests.h"
#include "matrix.h"

int main() {
	//testWrapper();
	//Matrix A(5, 4);
	Rational r1(-6, 15), r2(-4, 5);
	cout << "r1 is " << r1 << " and r2 is " << r2 << endl << endl;
	cout << "==" << (r1 == r2) << endl;
	cout << "!=" << (r1 != r2) << endl;
	cout << ">=" << (r1 >= r2) << endl;
	cout << ">" << (r1 > r2) << endl;
	cout << "<=" << (r1 <= r2) << endl;
	cout << "<" << (r1 < r2) << endl;



	system("pause");
	return 0;
}