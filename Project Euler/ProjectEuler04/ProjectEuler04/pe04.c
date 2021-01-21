//source for project euler 04

#include "pe04.h";

//checks if target string is palindrome, returns 1 if yes, 0 if no
//for initial call, passin 0 for left and strlen - 1 for right
int isPalindrome(char * target, int left, int right) {
	if (left >= right) {
		return 1;
	}
	else if (target[left] != target[right]) {
		return 0;
	}
	else {
		return isPalindrome(target, left + 1, right - 1);
	}
}