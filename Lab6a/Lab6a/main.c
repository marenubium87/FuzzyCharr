/*
* Aerie, CS121
* Instructor: Reynx
* Lab 6
* 20 Jun '18
*/

#include "totallynotmypornstash.h"

int main()
{
	//seed dat RNG for part D
	srand((unsigned int)time(NULL));

	printf("  Lab 6 Part A\n\n");
	
	//open input file
	FILE * infile = NULL;
	infile = getInput();

	//finds and prints sum of integers in input file
	int sum = 0;
	sum = sumOfIntegers(infile);
	printf("The sum of integers in input.txt is %d\n", sum);

	//tells whether that sum is a prime number
	printPrime(sum, isPrime(sum));

	//figures out the sum of digits of the sum above, prints that, and tells whether it's prime
	int digitSum = 0;
	digitSum = sumOfDigits(sum);
	printf("The sum of digits in the sum of integers is %d\n", digitSum);
	printPrime(digitSum, isPrime(digitSum));

	printf("  Lab 6 Part B\n\n");
	
	//the factorial bit
	int testNum = 0, factorial = 0;
	printf("Testing factorial\n");
	printf("Enter a number:  ");
	scanf("%d", &testNum);
	factorial = fuctorial(testNum);
	printf("\n%d! = %d\n\n", testNum, factorial);

	printf("  Lab 6 Part C\n\n");

	//fibonacci
	int testFib = 0, fibResult = 0;
	printf("Type an integer n >= 0 to get F(n), where F(n) is the nth Fib number: ");
	scanf("%d", &testFib);
	fibResult = fib(testFib);
	printf("\nF(%d) = %d\n\n", testFib, fibResult);

	printf("  Lab 6 Part D\n\n");
	//makes a rand and asks user if they want to see it
	int myRand = makeRand();
	int guess = 0;
	do
	{
		//while user hasn't gotten it right, get a guess and print out a response
		guess = getGuess();
		guessResponse(guess, myRand);

	} while (guess != myRand);

	//close everything down
	printf("End of program; press Enter to continue");
	char endCharr = '\0';
	scanf("%c", &endCharr);
	scanf("%c", &endCharr);

	return 0;
}