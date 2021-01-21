//Project Euler 1

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

int main() {
	//add up all multiples of 3
	int sum = 0;
	int i = 3;
	while (i < 1000) {
		sum += i;
		i += 3;
	}
	//add up all multiples of 5 ONLY IF they aren't also a multiple of 3
	int j = 5;
	while (j < 1000) {
		if (j % 3 != 0) {
			sum += j;
		}
		j += 5;
	}
	printf("Sum is %d\n", sum);

	system("pause");
	return 0;
}