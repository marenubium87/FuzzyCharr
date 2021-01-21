//source file for project Euler 05

#include "pe05.h"

//finds the prime factorization of target using primes defined
//in primeRefArray, and creates counts in primeCountsArray
//e.g. if target = 18 = 2 * 3 * 3, 
//returns primeCountsArray composition {1, 2, 0, 0, 0, 0, 0, 0}
void findPrimeFactorization(int target, int primeCountsArray[],
		int const primeRefArray[]) {

	int i = 0;
	while (target > 1) {
		if (target % primeRefArray[i] == 0) {
			target /= primeRefArray[i];
			primeCountsArray[i]++;
		}
		else {
			i++;
		}
	}
}

//resets prime counts array to all zeroes
void clearPrimeCountsArray(int primeCountsArray[]) {
	for (int i = 0; i < NUM_PRIMES; i++) {
		primeCountsArray[i] = 0;
	}
}

//increases primeMaster[i] to value of primeCountsArray[i]
//IF primeCountsArray[i] > primeMaster[i]
//idea is to have minimum prime factorization list in primeMaster
void appendPrimeMasterCounts(int primeCountsArray[], int primeMaster[]) {
	for (int i = 0; i < NUM_PRIMES; i++) {
		if (primeCountsArray[i] > primeMaster[i]) {
			primeMaster[i] = primeCountsArray[i];
		}
	}
}