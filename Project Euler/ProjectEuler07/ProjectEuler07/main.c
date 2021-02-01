//Project Euler 07
//26 Jan 2021

#include <stdio.h>
#include <Windows.h>
#include <math.h>

//only put in target >= 4
int isPrime(int target) {
	for (int i = 2; i <= floor(sqrt(target)); i++) {
		if (target % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {

	printf("Prime #\tPrime Value\n\n");
	printf("1\t\t2\n");
	printf("2\t\t3\n");

	int primeCount = 2;
	int i = 5;
	while (primeCount < 10002) {
		if (isPrime(i)) {
			primeCount++;
			printf("%d\t\t%d\n", primeCount, i);
			
		}
		i++;
	}


	system("pause");
	return 0;
}