//Header file for Lab 6

#define _CRT_SECURE_NO_WARNINGS
#define INTMAX 100
#define INTMIN -100

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//for rand seed
#include <time.h>

//opens input.txt for READING
FILE * getInput(void);

//reads and computes the sum of integers in infile, returns as int
int sumOfIntegers(FILE * infile);

//returns 1 if testNum is prime, 0 if testNum isn't prime
//also returns 0 if testNum is <=0 with an error message
int isPrime(int testNum);

//prints out if testNum is prime USING PRIMEFLAG
//if primeFlag = 1, will print out testNum is prime
//THIS FUNCTION DOES NOT CHECK IF TESTNUM IS PRIME!
//it only goes by primeFlag
void printPrime(int testNum, int primeFlag);

//computes the sum of the digits in testNum and returns as int
//assumes testNum is positive
int sumOfDigits(int testNum);

//takes the fuc... er, factorial of num
//num needs to be an int >= 0
//if num < 0 will return 0 and print out an error
unsigned long int fuctorial(int num);

//returns the nth term of the Fibonacci sequence, where F(0) = 0 and F(1) = 1
//and all subsequent F(n) = F(n-1) + F(n-2), so F(2) = 1, F(3) = 2, F(4) = 3, etc.
int fib(int n);

//makes a random number between INTMIN and INTMAX (inclusive)
//asks user if they want to cheat, to see the number
int makeRand();

//prompts user for a guess between INTMAX and INTMIN and returns it as int
//yells at user if they guessed outside INTMAX and INTMIN
int getGuess();

//yells at user if their guess is too high or too low
//yells at user anyway if their guess is correct
void guessResponse(int guess, int actual);