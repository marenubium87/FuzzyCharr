//Source file for Lab 8c

#include "justhanging.h"

//debug/test function; prints out all of the values of target int array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { 1 2 3 ... } format
void printIntArray(int target[], int targetSize)
{
	printf("\nTarget array composition is:\n");
	printf("{ ");
	for (int i = 0; i < targetSize; i++)
	{
		printf("%d ", target[i]);
	}
	printf("}");
}

//debug/test function; prints out all of the values of target char array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { a, b, c ... } format
//note: calling this function with wordSize instead of targetSize can print out 
//		just enough letters for the word
void printCharArray(char target[], int targetSize)
{
	printf("\nCurrent array composition is:\n");
	printf("{ ");
	for (int i = 0; i < targetSize; i++)
	{
		printf("%c ", target[i]);
	}
	printf("}");
}

//populates target guess array with asterisks, i.e. { * * * * * * * }
//where the number of asterisks is the number of letters in the word
void populateGuessArray(char target[], int numberOfLetters)
{
	for (int i = 0; i < numberOfLetters; i++)
	{
		target[i] = '*';
	}
}

//counts the number of letters present in word written in infile and returns it as an int
//also resets scan location at beginning of file
//prec:  infile must contain a SINGLE CONTIGUOUS WORD IN LOWERCASE and nothing else, including whitespace
int countLettersInFile(FILE * infile)
{
	//temp kitty to hold next letter
	char nextCharr = '\0';
	int numberOfLetters = 0;
	while (fscanf(infile, "%c", &nextCharr) > 0)
	{
		numberOfLetters++;
	}
	//go back to beginning of file so that the function that actually needs to read the letters doesn't fuck up
	rewind(infile);

	return numberOfLetters;
}

//puts in the word from infile into target
//prec:  infile must contain a SINGLE CONTIGUOUS WORD IN LOWERCASE and nothing else, including whitespace
//prec:  target size MUST be greater than or equal to word length
void eatWordFromFile(char target[], FILE * infile)
{
	//temp kitty to hold next letter
	char nextCharr = '\0';
	//counter variable for array
	int i = 0;
	while (fscanf(infile, "%c", &nextCharr) > 0)
	{
		target[i] = nextCharr;
		i++;
	}
}

//helper function, determines the ascii value of target character by casting to int
int determineASCIIValue(char target)
{
	int tempVal = target;
	return tempVal;
}

//prec:  alreadyGuessedArray is an int array of size 26
//prec:  guess must be a lower case letter
//for any lower case letter that is the ith letter of the alphabet, checks alreadyGuessedArray in the (i-1)th element
//if that element is 0, guess has not been guessed before; return 0 and increment the (i-1)th element
//if that element is not 0, guess has been guessed before, return 1
//function dependencies:  determine ASCIIValue
int alreadyGuessed(char guess, int alreadyGuessedArray[])
{
	int guessAsInt = determineASCIIValue(guess);
	//ascii 97 is 'a' and 122 is 'z'
	if (alreadyGuessedArray[guessAsInt - 97] == 0)
	{
		alreadyGuessedArray[guessAsInt - 97] += 1;
		return 0;
	}
	else if (alreadyGuessedArray[guessAsInt - 97] > 0)
	{
		return 1;
	}
	else
	{
		printf("Error - something went wrong in the alreadyGuessed function.\n\n");
	}
}

//exactly like what it says - counts the number of asterisks in a char array and returns that number as int
int countAsterisks(char target[], int targetSize)
{
	int asteriskCount = 0;
	for (int i = 1; i < targetSize; i++)
	{
		if (target[i] == '*')
		{
			asteriskCount++;
		}
	}
	return asteriskCount;
}

//asks for a guess from user, makes sure it's a lower case character and hasn't been guessed before
//prec:  alreadyGuessedArray is an array of size 26 which should hold which letters have been guessed
//function dependencies:  alreadyGuessed
//post:  if guess passes both criteria above, returns character
//post:  alreadyGuessedArray will have the appropriate element incremented corresponding to the guess returned
char askForGuess(int alreadyGuessedArray[])
{
	char tempCharr = '\0';
	int flag = 0;
	int isAlreadyGuessed = 0;
	do
	{
		printf("\n\nMake a guess (enter a valid lower case letter):  ");
		scanf(" %c", &tempCharr);
		//ascii 97 is 'a' and 122 is 'z'
		//makes sure input is a valid lower case letter
		if (determineASCIIValue(tempCharr) < 97 || determineASCIIValue(tempCharr) > 122)
		{
			printf("\nThat's not a valid lower case letter, you dumb shit.\n");
			flag = 1;
		}
		//if input is a valid lower case letter...
		else
		{
			//figure out if letter is already guessed
			isAlreadyGuessed = alreadyGuessed(tempCharr, alreadyGuessedArray);

			if (isAlreadyGuessed == 1)
			{
				printf("\nYou already tried that, you dumb shit.\n");
				flag = 1;
			}
			else if (isAlreadyGuessed == 0)
			{
				flag = 0;
			}
			else
			{
				printf("Uh... something went wrong here, in the askForGuess function.\n\n");
				flag = 0;
			}
		}

	} while (flag > 0);
	
	return tempCharr;
}

//checks the word array for the character guessed, and pastes that letter into the appropriate locations
//in guess array
//prec: numberOfLetters is the number of letters in the word, 
//		word array contains the actual word, and guessArray is the asterisks array
//prec: guess should not have been guessed before - i.e. the function askForGuess should have already made sure
//		that guess is a unique guess
//post: returns 0 if there is at least one letter revealed in the word
//		returns 1 if there are no letters revealed
//		also gives feedback to user depending on whether guess was good or not
int processGuess(char guess, char wordArray[], char guessArray[], int numberOfLetters)
{
	//counts how many times letter shows up in word
	int countLetter = 0;

	for (int i = 0; i < numberOfLetters; i++)
	{
		//if guess matches the ith element in wordArray, write the guess onto guessArray in the ith element
		if (wordArray[i] == guess)
		{
			guessArray[i] = wordArray[i];
			countLetter += 1;
		}
	}

	//after looping through all letters in word...

	//letter appears at least once
	if (countLetter > 0)
	{
		printf("\n  Yay!  There is/are %d %c's in the word.\n", countLetter, guess);
		return 0;
	}
	//letter never appears
	else
	{
		printf("\n  Onoes!  There are no %c's in the word.\n", guess);
		return 1;
	}
}

//wrapper function to loop/process guesses
//returns 0 if player wins, 1 if player loses
//function dependencies:  askForGuess, processGuess, printCharrArray, countAsterisks
int playHangman(char wordArray[], char guessArray[], int alreadyGuessedArray[], int numberOfLetters)
{
	char currentGuess = '\0';
	int guessedIncorrectly = 0;
	int wrongGuesses = 0;
	while (wrongGuesses < WRONGGUESSLIMIT)
	{
		
		currentGuess = askForGuess(alreadyGuessedArray);
		guessedIncorrectly = processGuess(currentGuess, wordArray, guessArray, numberOfLetters);

		//if user guessed incorrectly increment number of wrong guesses and display number of wrong guesses message
		if (guessedIncorrectly == 1)
		{
			wrongGuesses += guessedIncorrectly;
			printf("\nYou have used up %d of your %d allowed incorrect guesses.\n", wrongGuesses, WRONGGUESSLIMIT);
		}

		//if user's hit the incorrect guesses limit break out and return 1
		if (wrongGuesses == WRONGGUESSLIMIT)
		{
			return 1;
		}

		//shows user after guess what the board looks like, and their current progress
		printCharArray(guessArray, numberOfLetters);

		int numberAsterisks = countAsterisks(guessArray, numberOfLetters);
		//if there are no asterisks left they've gotten the word; jump out of function
		if (numberAsterisks == 0)
		{
			return 0;
		}
	}
}

//prints out a message based on whether user won or lost the game
//userLost == 0 means win, userLost == 1 means loss
void endGameMessage(int userLost)
{
	if (userLost == 0)
	{
		printf("\n\nHmm... you won... somehow.\n");
	}
	else
	{
		printf("\nYou've used up all of your incorrect guesses; maow maow, you lose.\n");
	}
}