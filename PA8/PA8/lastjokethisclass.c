//source for PA8
//122 here we come!

#include "lastjokethisclass.h"

//function for task 1
//accepts a pointer to a destination string, a source string and an int n
//returns pointer to destination string
//copies at most n characters from source to the end of dest
//but STOPS before n if a null character is encountered
//i beseech the sorcerer lynx to allow me to use sorc for source, kthx
//note, rewrite this to use fgets
//use strlen
char * my_str_n_cat(char sorc[], char dest[], int n) {
	int i = 0;
	int j = 0;
	//figures out where the end of dest is
	while (dest[j] != '\0') {
		j++;
	}
	printf("\n");
	printf("Reading \"%s\" for sorc\n", sorc);
	printf("Reading \"%s\" for dest\n\n", dest);

	//appending sorc to dest given restrictions
	printf("Copying first %d characters from sorc to dest...\n", n);
	do {
		dest[j] = sorc[i];
		if (sorc[i] != '\0') {
			i++;
			j++;
		}
		else {
			printf("Reached end of source string, stopping.\n\n");
		}

		if (i == n) {
			printf("Copied %d characters, stopping.\n\n", n);
		}

	} while (sorc[i] != '\0' && i < n);
	printf("dest now reads \"%s\".\n\n", dest);
	return dest;
}

//aux function for task two, for debugging and ease of presentation purposes
void printStringArray(char * target[], int targetSize) {
	printf("String array composition:\n\n");
	for (int i = 0; i < targetSize; i++) {
		printf("%s\n", target[i]);
	}
	printf("\nEnd of output.\n\n");
}

//sorts the first n entries of target pointers to strings array
//using the bubble sort algorithm, with "less than" determined by
//the strcmp function
void bubble_sort(char * target[], int n) {
	//sets unsorted section marker at the end of the list
	
	int u = n - 1;
	while (u >= 1) {
		//sets current element marker at its beginning position
		int c = 1;
		char * temp = NULL;
		while (c <= u) {
			if (strcmp(target[c], target[c - 1]) == -1) {
				temp = target[c - 1];
				target[c - 1] = target[c];
				target[c] = temp;
			}
			c++;
		}
		u--;
	}
}

//recursively sums all primes from 2 to n
int sum_primes(unsigned int n) {
	if (n == 2) {
		return 2;
	}
	else if (n == 0 || n == 1) {
		return 0;
	}
	else {
		//is the current number prime?
		//determine divisibility up to the square root of n
		int checkMax = (int)sqrt(n);
		for (int i = 2; i <= checkMax; i++) {
			//if at any point divides evenly, n is not prime
			//so move on to next number
			if (n % i == 0) {
				return sum_primes(n - 1);
			}
		}
		//if we make it through the for loop
		//n is prime, so add it to the rest of the recursion
		return n + sum_primes(n - 1);
	}
}

//aux function, prints target int array to the console
void printArray(int target[], int targetSize) {
	printf("Target Array Composition:\n{ ");
	for (int i = 0; i < targetSize; i++) {
		printf("%d ", target[i]);
	}
	printf("}\n");
}

//returns sum of the (sub)sequence in target signed int array 
//of size targetSize that contains the smallest (most negative) sum
//also prints start and end indices and minimum sum of min subarray
//to the console.
int smallest_sum_sequence(int target[], int targetSize) {
	//first determine the minimum value in the array
	printArray(target, targetSize);
	printf("Searching for minimum subsequence in target array...\n\n");
	int minVal = target[0];
	int minIndex = 0;
	for (int i = 1; i < targetSize; i++) {
		if (target[i] < minVal) {
			minVal = target[i];
			minIndex = i;
		}
	}
	//this implies all the entries in target are >= 0
	//therefore the smallest subsequence is simply of size 1
	//and is whatever the smallest entry is
	if (minVal >= 0) {
		printf("Minimum sum subarray start index:  %4d\n", minIndex);
		printf("Minimum sum subarray end   index:  %4d\n", minIndex);
		printf("Minimum sum subarray sum:          %4d\n", minVal);
		printf("\n**\n\n");
		return minVal;
	}
	//this is the more general case with at least one negative entry
	//in the array
	else {
		//variables needed to determine current minimum subarray
		int curLB = 0;
		int curRB = 0;
		int curSum = 0;
		int curMin = 0;
		//variables dealing with the absolute minimum subarray
		int absMin = 0;
		int absMinLeft = 0;
		int absMinRight = 0;

		for (int i = 0; i < targetSize; i++) {
			//find the next negative entry in the array and set the
			//current left bound (curLB) there, and start the sum
			if (target[i] < 0) {
				curLB = i;
				curRB = i;
				curSum = target[i];
				curMin = target[i];
				//advance the right marker starting with the element
				//one to the right of i, if it exists
				for (int j = i + 1; j < targetSize; j++) {
					//only add it if it does not
					//make the current sum go above zero
					if (curSum + target[j] < 0) {
						curSum += target[j];
						//does it create a new min?  if so, update the 
						//right bound and the new minimum sum.
						if (curSum < curMin) {
							curRB = j;
							curMin = curSum;
						}
					}
					//if adding the next entry does make the
					//sum 0 or greater, we break the loop 
					//as there is no reason to keep searching
					//for this particular left bound.
					else {
						break;
					}
				}

				//did we achieve a new absolute min?  update if so.
				if (curMin < absMin) {
					absMin = curMin;
					absMinLeft = curLB;
					absMinRight = curRB;
				}
			}
		}

		printf("Minimum sum subarray start index:  %4d\n", absMinLeft);
		printf("Minimum sum subarray end   index:  %4d\n", absMinRight);
		printf("Minimum sum subarray sum:          %4d\n", absMin);
		printf("\n**\n\n");
		return absMin;
	}
}

//prints out target 2D array with number of rows
//and number of cols to the console
void print2DArray(int target[][COLS], int rows, int cols) {
	printf("Target array composition:\n\n");
	for (int i = 0; i < rows; i++) {
		printf("{");
		for (int j = 0; j < cols; j++) {
			printf("%4d", target[i][j]);
		}
		printf("   }\n");
	}
	printf("\n\n");
}

//takes a 2d array of signed integers with number of rows and cols
//output parameter pAddr for the address of the start of the max
//consecutive sequence of the same integer
//output parameter pVal to store the number of values in the sequence
void max_consecutive_integers(int target[][COLS], int rows, int cols,
	int ** pAddr, int * pVal) {

	int curSeq = 0;
	int curSeqVal = 0;
	int * pCurSeqLoc = NULL;
	//forces the maxSeq and maxSeqVal to be the first entry
	//to avoid weird edge cases
	int maxSeq = 1;
	int maxSeqVal = target[0][0];
	int * pMaxSeqLoc = &target[0][0];

	//proc:  add one to the count if the next number in the array 
	//is the same as the current sequence value
	//reset the count and every time the value changes, as well as make
	//a note of the location that starts at

	//and append to maxSeq and maxSeqVal any time the current sequence
	//multiplicity exceeds the current max

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (target[i][j] == curSeqVal) {
				curSeq++;
			}
			else {
				//was the sequence that just ended longer than the current max?
				if (curSeq > maxSeq) {
					maxSeq = curSeq;
					pMaxSeqLoc = pCurSeqLoc;
				}

				//either way, reset the count and mark the new location
				pCurSeqLoc = &target[i][j];
				curSeq = 1;
				curSeqVal = target[i][j];
			}
		}
	}

	//saves max sequence amount (not the value of the int that has
	//the max sequence!)
	*pVal = maxSeq;
	*pAddr = pMaxSeqLoc;
}