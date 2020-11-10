//header file for PA1

#define _CRT_SECURE_NO_WARNINGS
#define NUM_LETTERS_IN_ENG_ALPHA 26

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

//15 types (including no change)
typedef enum deletionType {
	noChange, duplicateEntry, preAndSuffix,
	singleLetter, pastParticip, presParticip, imperfTense, adjective,
	seeAlt, altSpelling, adverb, abbrev, personProfession, plural, nounPlural
} DeletionType;

//aux function for evaluateEntry, evaluates the word part of the entry
int evaluateWord(char * word, char * previousWord);

//aux fucntion for evaluateEntry, evaluates the part of speech
//and definition parts of the entry
int evaluatePoSandDefn(char * word, char * PoS, char * defn);

//prints out results to the console
void outputResults(char * infileString, int deletionCounts[],
	int lineNumber, char * deletionCodeVerbose[]);

//evaluates current line of dictionary, returns int based on code
//corresponding to entries of DeletionType
int evaluateEntry(char * currentLine);

//wrapper to process all lines of a single data file
void processDictionaryWrapper(char * infileString, FILE * outfile,
	int deletionCounts[], char * deletionCodeVerbose[]);

//cleans the data file given by infileString and writes to
//the data file given by outfileString
//removes punctuation and all not-alpha characters
//also makes count of alpha characters
void cleanEntries(char * infileString, char * outfileString,
	int alphaCounts[], char alphabetVerbose[]);

//prints running tally of digraphs to the console for debugging purposes
void printDigraphs(int digraphCounts[][NUM_LETTERS_IN_ENG_ALPHA],
	char alphabetVerbose[], FILE * logfile);

//does what it says on the tin
//requires words in file referred to by infileString to all be
//in lower case.
void countDigraphs(char * infileString,
	int digraphCounts[][NUM_LETTERS_IN_ENG_ALPHA]);