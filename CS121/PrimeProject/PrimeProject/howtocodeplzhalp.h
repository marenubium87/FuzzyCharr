//header file for prime project

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//for a three line triplet in input.txt...
//ignores line 1 (i.e. ignores the array ID)
//uses line 2 to determine number of elements
//uses line 3 to populate target array
//also returns the target size
int populate_array(int target[]);

//determines if target number is prime or not
//returns 1 if prime, 0 if not
int determine_prime(int target);

//goes through source, and for any primes writes them to 
//successive elements of dest; returns destination array size
int write_primes(int source[], int dest[], int source_size);

//prints the first target_size elements of array target
void print_array(int target[], int target_size);