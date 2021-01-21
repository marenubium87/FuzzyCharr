//Project Euler 05

#include "pe05.h"

int main() {
	//declare prime array
	int const listOfPrimes[NUM_PRIMES] = { 2, 3, 5, 7, 11, 13, 17, 19 };
	int primeCountsArray[NUM_PRIMES] = { 0 };
	int masterPrimeCounts[NUM_PRIMES] = { 0 };


	for (int j = 2; j <= 20; j++) {
		findPrimeFactorization(j, primeCountsArray, listOfPrimes);
		appendPrimeMasterCounts(primeCountsArray, masterPrimeCounts);
		clearPrimeCountsArray(primeCountsArray);
	}

	int total = 1;
	for (int i = 0; i < NUM_PRIMES; i++) {
		total *= pow(listOfPrimes[i], masterPrimeCounts[i]);
	}

	printf("Total is %d\n", total);

	system("pause");
	return 0;
}