/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 8c
* 9 Aug 2018
*/

#include "justhanging.h"

int main()
{
	printf("Lab 8 Part C:  Hangman\n\n");
	//array declaration
	char wordArray[WORDARRAYSIZE] = { '\0' };
	char guessArray[WORDARRAYSIZE] = { '\0' };
	int alreadyGuessedArray[LETTERSINALPHA] = { 0 };

	//open infile for reading
	printf("Getting your word...\n");
	FILE * infile = NULL;
	infile = fopen("word.txt", "r");
	
	//figures out and assigns the number of letters in the word
	int numberOfLetters = countLettersInFile(infile);

	//gets the word and sticks it into wordArray
	printf("Generating arrays...\n\n");
	eatWordFromFile(wordArray, infile);
	populateGuessArray(guessArray, numberOfLetters);

	//prints out the virgin version of guessArray with all asterisks
	printf("Mk.  Here's your word... good luck.\n");
	printCharArray(guessArray, numberOfLetters);

	//plays the game, prints out message based on outcome
	int gameState = 0;
	gameState = playHangman(wordArray, guessArray, alreadyGuessedArray, numberOfLetters);
	endGameMessage(gameState);

	//end of program cleanup
	fclose(infile);
	printf("\nEnd of program; press Enter to continue");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}