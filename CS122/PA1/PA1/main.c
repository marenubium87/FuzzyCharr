/*
* James Liu
* CS122
* PA1 Data Sanitization
* 22 Oct 2020
*/

#include "dictionary.h"

int main() {
	printf("PA1 - Data Sanitization\n\n");
	system("pause");

	char * deletionCodeVerbose[15] = {
		"no change    ",
		"dup entry    ",
		"prefix/suffix",
		"singleLetter ",
		"pastParticip ",
		"presParticip ",
		"imperfTense  ",
		"adjective    ",
		"see alt.     ",
		"alt spelling ",
		"adverb w -ly ",
		"abbreviation ",
		"\"one who\"    ",
		"plural       ",
		"noun plural  "
	};

	char alphabetVerbose[NUM_LETTERS_IN_ENG_ALPHA] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
		's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	//array for deletion counts
	int deletionCounts[15] = { 0 };
	//array for single letter counts
	int alphaCounts[NUM_LETTERS_IN_ENG_ALPHA] = { 0 };
	//array for digraph counts
	int digraphCounts[NUM_LETTERS_IN_ENG_ALPHA][NUM_LETTERS_IN_ENG_ALPHA]
		= { 0 };

	//***PROCESS DICTIONARY ENTRIES

	//first dictionary file
	char infileString[20] = "A.csv";
	//write pruned words to this file
	char prunedWordListString[20] = "prunedWordList.txt";
	FILE * prunedWordList = fopen(prunedWordListString, "w");
	//write log to this file
	char logfileString[20] = "log.txt";
	FILE * logfile = fopen(logfileString, "w");
	
	//prune dictionary
	do {
		processDictionaryWrapper(infileString, prunedWordList,
			deletionCounts, deletionCodeVerbose);
		//cycle through alphabet
		infileString[0]++;
	} while (isalnum(infileString[0]));
	fclose(prunedWordList);
	printf("\nPruning complete.\n\n");

	//write results of pruning to log
	fprintf(logfile, "***Dictionary Processed Entry Counts***\n\n");
	for (int i = 0; i < 15; i++) {
		fprintf(logfile, "Deletion code %2d (%s): %6d\n", i,
			deletionCodeVerbose[i], deletionCounts[i]);
	}
	printf("Wrote deletion counts to %s.\n\n", logfileString);
	system("pause");

	//write cleaned entries to this file
	char cleanedWordListString[20] = "cleanedWordList.txt";
	cleanEntries(prunedWordListString, cleanedWordListString, alphaCounts,
		alphabetVerbose);
	printf("Entries cleaned.\n\n");

	//write results of alpha frequencies to logfile
	fprintf(logfile, "\n\n***Single Letter Frequencies***\n\n");
	for (int i = 0; i < NUM_LETTERS_IN_ENG_ALPHA; i++) {
		fprintf(logfile, "%c:%7d\n", alphabetVerbose[i], alphaCounts[i]);
	}
	fprintf(logfile, "\n\n");
	printf("Wrote single letter frequencies to %s.\n\n", logfileString);
	system("pause");

	//digraph analysis
	char digraphfileString[20] = "digraphs.csv";
	FILE * digraphfile = fopen(digraphfileString, "w");
	countDigraphs(cleanedWordListString, digraphCounts);
	printf("\nDigraphs counted.\n\n");
	printDigraphs(digraphCounts, alphabetVerbose, logfile, digraphfile);
	printf("Wrote digraph frequencies to %s.\n", logfileString);
	printf("Wrote digraph frequencies to %s.\n\n", digraphfileString);

	printf("***END OF PROGRAM\n\n");
	system("pause");

	fclose(logfile);
	fclose(digraphfile);
	return 0;
}