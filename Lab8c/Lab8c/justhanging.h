//header file for Lab 8c

#define _CRT_SECURE_NO_WARNINGS
//last i checked.
#define LETTERSINALPHA 26
#define WORDARRAYSIZE 15
#define WRONGGUESSLIMIT 6

#include <stdio.h>

//debug/test function; prints out all of the values of target int array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { 1 2 3 ... } format
void printIntArray(int target[], int targetSize);

//debug/test function; prints out all of the values of target char array onto the console
//precondition:  target array and size in elements of target array need to be available
//postcondition:  target array is printed out in { a, b, c ... } format
//note: calling this function with wordSize instead of targetSize can print out 
//		just enough letters for the word
void printCharArray(char target[], int targetSize);

//populates target guess array with asterisks, i.e. { * * * * * * * }
//where the number of asterisks is the number of letters in the word
void populateGuessArray(char target[], int numberOfLetters);

//counts the number of letters present in word written in infile and returns it as an int
//also resets scan location at beginning of file
//prec:  infile must contain a SINGLE CONTIGUOUS WORD IN LOWERCASE and nothing else, including whitespace
int countLettersInFile(FILE * infile);

//puts in the word from infile into target
//prec:  infile must contain a SINGLE CONTIGUOUS WORD IN LOWERCASE and nothing else, including whitespace
//prec:  target size MUST be greater than or equal to word length
void eatWordFromFile(char target[], FILE * infile);

//helper function, determines the ascii value of target character by casting to int
int determineASCIIValue(char target);

//prec:  alreadyGuessedArray is an int array of size 26
//prec:  guess must be a lower case letter
//for any lower case letter that is the ith letter of the alphabet, checks alreadyGuessedArray in the (i-1)th element
//if that element is 0, guess has not been guessed before; return 0 and increment the (i-1)th element
//if that element is not 0, guess has been guessed before, return 1
//function dependencies:  determine ASCIIValue
int alreadyGuessed(char guess, int alreadyGuessedArray[]);

//exactly like what it says - counts the number of asterisks in a char array and returns that number as int
int countAsterisks(char target[], int targetSize);

//asks for a guess from user, makes sure it's a lower case character and hasn't been guessed before
//prec:  alreadyGuessedArray is an array of size 26 which should hold which letters have been guessed
//function dependencies:  alreadyGuessed
//post:  if guess passes both criteria above, returns character
//post:  alreadyGuessedArray will have the appropriate element incremented corresponding to the guess returned
char askForGuess(int alreadyGuessedArray[]);

//checks the word array for the character guessed, and pastes that letter into the appropriate locations
//in guess array
//prec: numberOfLetters is the number of letters in the word, 
//		word array contains the actual word, and guessArray is the asterisks array
//prec: guess should not have been guessed before - i.e. the function askForGuess should have already made sure
//		that guess is a unique guess
//post: returns 0 if there is at least one letter revealed in the word
//		returns 1 if there are no letters revealed
int processGuess(char guess, char wordArray[], char guessArray[], int numberOfLetters);

//wrapper function to loop/process guesses
//returns 0 if player wins, 1 if player loses
//function dependencies:  askForGuess, processGuess, printCharrArray, countAsterisks
int playHangman(char wordArray[], char guessArray[], int alreadyGuessedArray[], int numberOfLetters);

//prints out a message based on whether user won or lost the game
//userLost == 0 means win, userLost == 1 means loss
void endGameMessage(int userLost);