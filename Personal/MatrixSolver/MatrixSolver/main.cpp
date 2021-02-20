//matrix solver project
//2 Feb 2021

#include "rational.h"
#include "tests.h"
#include "matrix.h"

int main() {
	testWrapper();

	Matrix A;
	fstream input("input.txt", std::ios::in);
	input >> A;
	
	A.rref();

	system("pause");
	return 0;
}