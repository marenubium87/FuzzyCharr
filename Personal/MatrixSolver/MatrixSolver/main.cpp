//matrix solver project
//2 Feb 2021

#include "rational.h"
#include "tests.h"
#include "matrix.h"

int main() {
	testWrapper();
	Rational r1(0, 1);
	Matrix A(3, 4);
	Matrix B;
	//doThings(B);
	for (int i = 0; i < A.getRows(); i++) {
		for (int j = 0; j < A.getCols(); j++) {
			r1.setVal(i-j, i+j+1);
			A[i][j] = r1;
		}
	}
	A[2][1].setSign(-3);
	cout << A;
	doThings(A);

	A[2][1] = r1;
	cout << A;


	system("pause");
	return 0;
}