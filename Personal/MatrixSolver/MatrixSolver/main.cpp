//matrix solver project
//2 Feb 2021

#include "rational.h"
#include "tests.h"

int main() {
	//testWrapper();
	Rational r1(1, 2), r2(-3, 10), r3;
	r3 = r1 + r2;
	cout << r1 << " + " << r2 << " = " << r3 << endl;
	r3 = r1 - r2;
	cout << r1 << " - " << r2 << " = " << r3 << endl;
	r3 = r1 * r2;
	cout << r1 << " * " << r2 << " = " << r3 << endl;
	r3 = r1 / r2;
	cout << r1 << " / " << r2 << " = " << r3 << endl;

	Rational r4(9, 12), r5(5, 10);
	cout << r4 << " is ";
	if (!(r4 == r5)) {
		cout << "not ";
	}
	cout << "equivalent to " << r5 << endl;

	system("pause");
	return 0;
}