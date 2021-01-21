//project euler problem 4

#include "pe04.h"

int main() {
	int result = 0;
	char strResult[7] = "";

	for (int i = MAX_NUM; i > 900; i--) {
		//first diagonal pass
		//compute difference btwn i and MAX_NUM
		//increment j between 0 and that and compute i^2 - j^2
		int i_diff = MAX_NUM - i;
		for (int j = 0; j <= i_diff; j++) {
			result = pow(i, 2) - pow(j, 2);
			//convert to string
			sprintf(strResult, "%d", result);
			//if palindrome, print out to console
			if (isPalindrome(strResult, 0, strlen(strResult) - 1)) {
				printf("%s\n", strResult);
			}
		}
		//second diagonal pass
		//for p = i and q = i - 1, take products of pq
		//increment p, decrement q, until p hits MAX_NUM

		for (int p = i, q = i - 1; p <= MAX_NUM; p++, q--) {
			result = p * q;
			sprintf(strResult, "%d", result);
			//if palindrome, print out to console
			if (isPalindrome(strResult, 0, strlen(strResult) - 1)) {
				printf("%s\n", strResult);
			}
		}
	}
	system("pause");
	return 0;
}