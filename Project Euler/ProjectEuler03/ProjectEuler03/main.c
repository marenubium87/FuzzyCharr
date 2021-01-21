//Project Euler 3

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <Windows.h>


int main() {
	long long int myNum = 600851475143;
	int listOfDivisors[30] = { 0 };
	//index for divisors array
	int j = 0;
	int divisorFoundFlag;
	do {
		divisorFoundFlag = 0;
		int sqrtOfMyNum = floor(sqrt(myNum));
		for (int i = 2; i <= sqrtOfMyNum; i++) {
			if (myNum % i == 0) {
				//if i is a divisor, write it to array index j
				listOfDivisors[j] = i;
				j++;
				myNum /= i;
				divisorFoundFlag = 1;
				break;
			}
		}
	} while (divisorFoundFlag);
	//so at this point, myNum is the last prime factor, as it itself is prime
	//and all other factors below it have been divided away.
	listOfDivisors[j] = myNum;

	for (int i = 0; i < 30; i++) {
		printf("%d ", listOfDivisors[i]);
	}

	system("pause");
	return 0;
}