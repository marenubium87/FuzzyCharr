//Project Euler 2

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

int main() {
	int fibMinus1 = 2;
	int fibMinus2 = 1;
	int fibCurrent = 0;
	int sum = 0;
	while (fibCurrent < 4000000) {
		//come up with the next fib number
		fibCurrent = fibMinus1 + fibMinus2;
		//is it even?
		if (fibCurrent % 2 == 0) {
			sum += fibCurrent;
		}
		//push down the current fib number to the previous
		//to get ready for the next iteration
		fibMinus2 = fibMinus1;
		fibMinus1 = fibCurrent;
	}

	//add 2 because we never added the first 2 which is an even fib number
	sum += 2;
	printf("Sum is %d\n\n", sum);

	system("pause");
	return 0;
}