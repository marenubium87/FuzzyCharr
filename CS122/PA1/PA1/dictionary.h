//header file for PA1

#define _CRT_SECURE_NO_WARNINGS

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
	int lineNumber);

//evaluates current line of dictionary, returns int based on code
//corresponding to entries of DeletionType
int evaluateEntry(char * currentLine);

//wrapper to process all lines of a single data file
void processDictionaryWrapper(char * infileString, char * outfileString,
	int deletionCounts[]);

