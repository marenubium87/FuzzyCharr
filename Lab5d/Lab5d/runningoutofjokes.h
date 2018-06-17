//Header file for Lab 5 Part 4

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//opens input.txt for READING
FILE * getInputFile(void);

//yep, no idea what this function does.  none at all.
//okay, but seriously, reads next double from infile
//infile must be open for reading, obviously
double readNextNumber(FILE * infile);

//prints out highest double in infile
//infile must be open for reading
//dependencies:  readNextNumber
void printHighest(FILE * infile);

//prints out lowest double in infile
//infile must be open for reading
//dependencies: readNext Number
void printLowest(FILE * infile);

//all the typical shit I do to end a program, now with 100% more functions!
void typicalEndingShit(void);