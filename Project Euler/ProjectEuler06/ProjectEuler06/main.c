//project Euler 06

#include "pe06.h"

int main() {
	int sumSquares = 0;
	int sumNonSquares = 0;

	for (int i = 1; i <= 100; i++) {
		sumSquares += pow(i, 2);
		sumNonSquares += i;
	}
	int squareSum = pow(sumNonSquares, 2);
	int result = sumSquares - squareSum;
	printf("Result is %d\n", result);

	system("pause");
	return 0;
}