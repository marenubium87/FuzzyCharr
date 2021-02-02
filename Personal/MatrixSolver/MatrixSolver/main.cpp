//matrix solver project
//2 Feb 2021

#include "rational.h"

int main() {
	Rational r1, r2(-3, 5), r3(-7), r4(23, 17);
	cout << r1 << "  " << r2 << "  " << r3 << "  " << r4 << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Enter a rational:  ";
		cin >> r1;
		cout << "You entered:  " << r1 << endl << endl;
	}
	

	system("pause");
	return 0;
}