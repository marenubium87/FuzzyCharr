//header file for Project Euler 05

#define _CRT_SECURE_NO_WARNINGS
#define NUM_PRIMES 8


#include <stdio.h>
#include <Windows.h>
#include <math.h>

//finds the prime factorization of target using primes defined
//in primeRefArray, and creates counts in primeCountsArray
//e.g. if target = 18 = 2 * 3 * 3, 
//returns primeCountsArray composition {1, 2, 0, 0, 0, 0, 0, 0}
void findPrimeFactorization(int target, int primeCountsArray[],
	int const primeRefArray[]);

//resets prime counts array to all zeroes
void clearPrimeCountsArray(int primeCountsArray[]);

//increases primeMaster[i] to value of primeCountsArray[i]
//IF primeCountsArray[i] > primeMaster[i]
//idea is to have minimum prime factorization list in primeMaster
void appendPrimeMasterCounts(int primeCountsArray[], int primeMaster[]);
