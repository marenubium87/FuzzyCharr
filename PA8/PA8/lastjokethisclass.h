//Header file for PA8
//wow, guess this is really it, huh.  alas.

#define _CRT_SECURE_NO_WARNINGS
#define ROWS 5
#define COLS 5

#include <stdio.h>
#include <math.h>
#include <Windows.h>

//function for task 1
//accepts a pointer to a destination string, a source string and an int n
//returns pointer to destination string
//copies at most n characters from source to the end of dest
//but STOPS before n if a null character is encountered
//i beseech the sorcerer lynx to allow me to use sorc for source, kthx
char * my_str_n_cat(char sorc[], char dest[], int n);

//aux function for task two, for debugging and ease of presentation purposes
void printStringArray(char * target[], int targetSize);

//sorts the first n entries of target pointers to strings array
//using the bubble sort algorithm, with "less than" determined by
//the strcmp function
void bubble_sort(char * target[], int n);

//recursively sums all primes from 2 to n
int sum_primes(unsigned int n);

//aux function, prints target int array to the console
void printArray(int target[], int targetSize);

//returns sum of the (sub)sequence in target signed int array 
//of size targetSize that contains the smallest (most negative) sum
int smallest_sum_sequence(int target[], int targetSize);

//prints out target 2D array with number of rows ROWS
//and number of cols COLS to the console
void print2DArray(int target[][COLS], int rows, int cols);

//takes a 2d array of signed integers with number of rows and cols
//output parameter pAddr for the address of the start of the max
//consecutive sequence of the same integer
//output parameter pVal to store the number of values in the sequence
void max_consecutive_integers(int target[][COLS], int rows, int cols,
	int ** pAddr, int * pVal);