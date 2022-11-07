#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

int lengthOfLongestSubstring(char * s) {
	int lenLongestSubstring = 0;
	int headIndex = 0;

	//check for empty string case
	if (s[headIndex] == '\0') {
		return 0;
	}

	int tailIndex = 0;
	//set up character freq array and increment initial head value
	int arrCharFreq[256] = { 0 };
	arrCharFreq[s[headIndex]]++;

	do {
		tailIndex++;
		arrCharFreq[s[tailIndex]]++;

		//did the tail just bump into a repeat?
		if (arrCharFreq[s[tailIndex]] > 1) {

			//is this a new substring record?
			if (tailIndex - headIndex > lenLongestSubstring) {
				lenLongestSubstring = tailIndex - headIndex;
			}

			//advance head marker to just past 
			//previous iteration of match
			//undoing counts as the head travels forward
			while (s[headIndex] != s[tailIndex]) {
				arrCharFreq[s[headIndex]]--;
				headIndex++;
			}
			//this decreases the count of the repeated element
			//from 2 back to 1
			arrCharFreq[s[headIndex]]--;
			headIndex++;
		}

	} while (s[tailIndex] != '\0');

	//check one more time if this final config of head and tail
	//results in a new record
	if (tailIndex - headIndex > lenLongestSubstring) {
		lenLongestSubstring = tailIndex - headIndex;
	}
	return lenLongestSubstring;
}

int main() {
	char * myStr = "abcabcbb";
	int lenStr = 0;

	lenStr = lengthOfLongestSubstring(myStr);


	printf("Longest substring length is %d.\n\n", lenStr);

	system("pause");
	return 0;
}