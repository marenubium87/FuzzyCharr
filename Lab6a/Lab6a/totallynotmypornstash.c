//Source file for Lab 6

#include "totallynotmypornstash.h"

//opens input.txt for READING
FILE * getInput(void)
{
	FILE * infile = NULL;
	infile = fopen("input.txt", "r");
	return infile;
}

//adds all integers in infile and returns as int
int sumOfIntegers(FILE * infile)
{
	int sum = 0, nextNum = 0;
	while (fscanf(infile, "%d", &nextNum) > 0)
	{
		sum += nextNum;
	}
	return sum;
}

//returns 1 if testNum is prime, 0 if testNum isn't prime
//also returns 0 if testNum is <=0 with an error message
int isPrime(int testNum)
{
	if (testNum <= 0)
	{
		printf("Error - can only determine if positive integers are prime\n\n");
		return 0;
	}

	//takes the floor of the square root of testNum and purposefully casts it to an int
	//to figure out the last potential factor to check to determine primeness
	int maxFactor = floor(sqrt(testNum));

	for (int i = 2; i <= maxFactor; i++)
	{
		//this means that i was a factor of testNum and thus testNum is not prime
		if (testNum % i == 0)
		{
			return 0;
		}
	}
	//if it survives the for loop without returning 0, then testNum must be prime
	return 1;
}

//prints out if testNum is prime USING PRIMEFLAG
//if primeFlag = 1, will print out testNum is prime
//THIS FUNCTION DOES NOT CHECK IF TESTNUM IS PRIME!
//it only goes by primeFlag
void printPrime(int testNum, int primeFlag)
{
	printf("%d is ", testNum);
	if (primeFlag == 0)
	{
		printf("not ");
	}
	printf("prime\n\n");
}

//computes the sum of the digits in testNum and returns as int
//assumes testNum is positive, will return 0 if testNum <= 0
int sumOfDigits(int testNum)
{
	int digitSum = 0, currentNum = 0;
	currentNum = testNum;

	//after extraction of all digits integer division by 10 will make currentNum 0 and break the loop
	while (currentNum > 0)
	{
		//extracts current digit's ones place, and adds it to digitSum
		digitSum += currentNum % 10;

		//integer division "deletes" the current ones place and makes the next place over the new ones place
		//so that it can be extracted by the next pass through the loop
		currentNum = currentNum / 10;
	}

	return digitSum;
}

//takes the fuc... er, factorial of num
//num needs to be an int >= 0
//if num < 0 will return 1 and print out an error
unsigned long int fuctorial(int num)
{
	unsigned long int aggregator = 1;
	//1! and 0! = 1
	if (num <= 1)
	{
		if (num < 0)
		{
			printf("Error: cannot take factorial of negative integer\n");
		}
		return 1;
	}
	else
	{
		//num has to be at least 2 to go in here so it'll go through this while at least once
		for (int i = num; i > 1; i--)
		{
			aggregator *= i;
		}
	}
	return aggregator;
}

//returns the nth term of the Fibonacci sequence, where F(0) = 0 and F(1) = 1
//and all subsequent F(n) = F(n-1) + F(n-2), so F(2) = 1, F(3) = 2, F(4) = 3, etc.
int fib(int n)
{
	if (n == 0 || n == 1)
	{
		return n;
	}
	else
	{
		int fibA = 0, fibB = 1, fibCurrent = 0;
		for (int i = 2; i <= n; i++)
		{
			//fib current is the sum of the previous two fibs
			fibCurrent = fibA + fibB;

			//now resets the "previous two" fib numbers for the next go through the loop
			fibA = fibB;
			fibB = fibCurrent;
		}
		return fibCurrent;
	}
}

//makes a random number between INTMIN and INTMAX (inclusive)
//asks user if they want to cheat, to see the number
int makeRand()
{
	int myRand = 0;
	//figures out the range between INTMIN and INTMAX
	int range = INTMAX - INTMIN;
	
	//there are range + 1 distinct values inside range
	//e.g. between 2 and 5 there are 4 distinct values, not 3
	myRand = rand() % (range + 1);
	//makes it so that the range starts with INTMIN (and will correctly end with INTMAX)
	myRand = myRand + INTMIN;

	//tells user about it and asks if they want to cheat for debugging purposes
	printf("Made a rand between %d and %d.\n", INTMIN, INTMAX);
	printf("Would you like to see it? (y/n) ");
	char userResponse = '\0';
	scanf(" %c", &userResponse);

	if (userResponse == 'y' || userResponse == 'Y')
	{
		printf("Fine, you filthy cheater.\n");
		printf("The rand I gots is %d\n\n", myRand);
	}

	return myRand;
}

//prompts user for a guess between INTMAX and INTMIN and returns it as int
//yells at user if they guessed outside INTMAX and INTMIN
int getGuess()
{
	int guess = 0;
	do
	{
		printf("Guess a number between %d and %d: ", INTMIN, INTMAX);
		scanf("%d", &guess);
		//if guess is valid, return it
		if (guess >= INTMIN && guess <= INTMAX)
		{
			return guess;
		}
		//otherwise, berate user
		else
		{
			printf("\nPlease don't make me import my threats from the craps program.\n\n");
		}
	} while (guess < INTMIN || guess > INTMAX);
}

//yells at user if their guess is too high or too low
//yells at user anyway if their guess is correct
void guessResponse(int guess, int actual)
{
	if (guess > actual)
	{
		printf("Too high, dumbass.\n\n");
	}
	else if (guess < actual)
	{
		printf("Too low, dumbass.\n\n");
	}
	else
	{
		printf("Hmm.  You must have cheated.\n\n");
	}
}