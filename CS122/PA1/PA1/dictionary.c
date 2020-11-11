//source file for PA1

#include "dictionary.h"

//aux function for evaluateEntry, evaluates the word part of the entry
int evaluateWord(char * word, char * previousWord) {
	//is word the same as the previous non-deleted word?
	if (strcmp(previousWord, word) == 0) {
		//value is 1
		return duplicateEntry;
	}
	else if(word[0] == '-' || word[(strlen(word) - 1)] == '-') {
		//value is 2
		return preAndSuffix;
	}
	if (strlen(word) == 1) {
		//value is 3
		return singleLetter;
	}
	//word token is fine if it doesn't trigger any of the above returns.
	return 0;
}

//aux fucntion for evaluateEntry, evaluates the part of speech
//and definition parts of the entry
int evaluatePoSandDefn(char * word, char * PoS, char * defn) {
	if (strncmp(PoS, "p. p.", 5) == 0 && strncmp(defn, "of ", 3) == 0) {
		//value = 4
		return pastParticip;
	}
	else if (strncmp(PoS, "p. pr.", 6) == 0 && strncmp(defn, "of ", 3) == 0) {
		//value = 5
		return presParticip;
	}
	else if (strncmp(PoS, "imp.", 4) == 0 && word[strlen(word) - 1] == 'd') {
		//value = 6
		return imperfTense;
	}
	else if ((strncmp(defn, "Of or pertaining", 16) == 0 || 
		strncmp(defn, "Pertaining to", 13) == 0) 
		&& (strncmp(PoS, "a.", 2) == 0)) {
		//value = 7
		return adjective;
	}
	else if (strncmp(defn, "See", 3) == 0 && defn[4] == word[0]) {
		//value = 8
		return seeAlt;
	}
	else if (strncmp(defn, "Alt. of", 7) == 0) {
		//value = 9
		return altSpelling;
	}
	else if (strncmp(PoS, "adv.", 4) == 0 && 
		word[strlen(word) - 2] == 'l' && word[strlen(word) - 1] == 'y') {
		//value = 10
		return adverb;
	}
	else if (strncmp(defn, "An abbreviation", 15) == 0) {
		//value = 11
		return abbrev;
	}
	else if (strncmp(defn, "One who", 7) == 0) {
		//value = 12
		return personProfession;
	}
	else if (strncmp(PoS, "pl.", 3) == 0 && strncmp(defn, "of ", 3) == 0) {
		//value = 13
		return plural;
	}
	else if (strncmp(PoS, "n. pl.", 6) == 0) {
		//value = 14
		return nounPlural;
	}
	//so if none of those things get caught, word is fine
	else {
		//value = 0
		return noChange;
	}
}

//evaluates current line of dictionary, returns int based on code
//corresponding to entries of DeletionType
int evaluateEntry(char * currentLine) {
	static char previousWord[120] = "";

	//marker if previous word was deleted
	static int previousDeleted = 0;
	//grab word through tokenization
	char * word = strtok(currentLine, "\"");
	
	//check the word part of the entry
	int deletionCode = evaluateWord(word, previousWord);
	
	//so word is fine, but need to check part of speech and defn
	//for reference, a line in the dictionary has this as a typical form:
	//"Word", "imp. & p. p.", "definition"
	//"Word", "", "definition"
	if (deletionCode == 0) {
		//deletes the comma bit after word 
		strtok(NULL, "\"");
		//grab part of speech
		char * PoS = strtok(NULL, "\"");
		//this means part of speech portion exists
		if (isalnum(PoS[0])) {
			//so tokenize again to get rid of the next comma
			strtok(NULL, "\"");
		}
		//part of speech portion does not exist
		else {
			char * emptyString = "";
			PoS = emptyString;
		}
		//tokenize again for defn
		char * defn = strtok(NULL, "\"");
		//check out the remaining parts of the word
		deletionCode = evaluatePoSandDefn(word, PoS, defn);
	}
	//if word isn't to be deleted, set it as the previous word for the
	//next run of this function.
	if (deletionCode == 0) {
		strcpy(previousWord, word);
	}
	return deletionCode;
}

//prints out pruning results to the console
void outputPruningResults(char * infileString, int deletionCounts[],
	int lineNumber, char * deletionCodeVerbose[]) {
	system("cls");
	printf("Pruning dictionary...\n\n");
	printf("Processing %s...\n\n", infileString);
	printf("Reading line %d...\n\n", lineNumber);
	printf("Deletion counts:\n");
	for (int i = 0; i < 15; i++) {
		printf("Deletion code %2d (%s): %6d\n", i, 
			deletionCodeVerbose[i], deletionCounts[i]);
	}
}

//wrapper to process all lines of a single data file
void processDictionaryWrapper(char * infileString, FILE * outfile,
	int deletionCounts[], char * deletionCodeVerbose[]) {

	FILE * infile = fopen(infileString, "r");
	
	int i = 0;
	char nextLine[3000] = "";
	//copy that strtok will not chop up
	char nextLineDuplicate[3000] = "";

	while (fgets(nextLine, 2950, infile) != NULL) {
		strcpy(nextLineDuplicate, nextLine);
		
		//process next line and evaluate deletion code here
		int deletionCode = evaluateEntry(nextLine);
		
		//write word to outfile?
		if (deletionCode == 0) {
			fprintf(outfile, "%s\n", strtok(nextLineDuplicate, "\""));
		}

		//update deletion counts array
		deletionCounts[deletionCode]++;
		i++;
		if (i % 100 == 0) {
			outputPruningResults(infileString, deletionCounts, 
				i, deletionCodeVerbose);
		}
	}
	fclose(infile);
}

//outputs alpha count results to the console
//requires alphaCounts to be of size NUM_LETTERS_IN_ENG_ALPHA
void outputAlphaCountResults(int alphaCounts[], char alphabetVerbose[]) {
	printf("Letter counts:\n\n");
	for (int i = 0; i < NUM_LETTERS_IN_ENG_ALPHA; i++) {
		printf("%c:%7d\n", alphabetVerbose[i], alphaCounts[i]);
	}
}

//cleans the data file given by infileString and writes to
//the data file given by outfileString
//removes punctuation and all not-alpha characters
//also makes count of alpha characters
void cleanEntries(char * infileString, char * outfileString,
	int alphaCounts[], char alphabetVerbose[]) {
	FILE * infile = fopen(infileString, "r");
	FILE * outfile = fopen(outfileString, "w");

	
	char nextWord[101] = "";
	int i = 0;
	while (fgets(nextWord, 100, infile) != NULL) {
		for (unsigned int i = 0; i < strlen(nextWord); i++) {
			nextWord[i] = tolower(nextWord[i]);
			//is the next character not a letter?
			if (!isalpha(nextWord[i])) {
				//is it an apostrophe?
				if (nextWord[i] == '\'') {
					//does it contain an s afterward?
					if (nextWord[i + 1] == 's') {
						nextWord[i] = ' ';
						nextWord[i + 1] = ' ';
					}
				}
				//all else, just replace w/ space
				else {
					nextWord[i] = ' ';
				}
			}
			else {
				//97 is ASCII 'a'
				alphaCounts[nextWord[i] - 97]++;
			}
		}
		//write cleaned word to outfile
		fprintf(outfile, "%s\n", nextWord);
		i++;
		if (i % 100 == 0) {
			system("cls");
			printf("Cleaning lines and generating single letter counts...\n");
			printf("Cleaning line %d...\n\n", i);
			outputAlphaCountResults(alphaCounts, alphabetVerbose);
		}
	}
	fclose(infile);
	fclose(outfile);
}

//prints tally of digraphs to the logfile
//and also prints tally of digraphs to separate csv file
void printDigraphs(int digraphCounts[][NUM_LETTERS_IN_ENG_ALPHA],
	char alphabetVerbose[], FILE * logfile, FILE * digraphfile) {
	
	//write digraph frequencies to logfile
	fprintf(logfile, "***Digraph Frequencies***\n\n");
	//print column labels
	fprintf(logfile, "\t\t");
	for (int x = 0; x < NUM_LETTERS_IN_ENG_ALPHA - 1; x++) {
		fprintf(logfile, "%c\t\t", alphabetVerbose[x]);
	}
	fprintf(logfile, "z");
	fprintf(logfile, "\n\n");

	for (int i = 0; i < NUM_LETTERS_IN_ENG_ALPHA; i++) {
		fprintf(logfile, "%c", alphabetVerbose[i]);
		for (int j = 0; j < NUM_LETTERS_IN_ENG_ALPHA - 1; j++) {
			fprintf(logfile, "%8d", digraphCounts[i][j]);
		}
		fprintf(logfile, "%8d\n", digraphCounts[i][25]);
	}

	//write digraph frequencies to csv file
	//delimiter character
	char delim = ',';
	for (int i = 0; i < NUM_LETTERS_IN_ENG_ALPHA; i++) {
		for (int j = 0; j < NUM_LETTERS_IN_ENG_ALPHA; j++) {
			fprintf(digraphfile, "%c%c%c%d\n",
				i + 'a', j + 'a', delim, digraphCounts[i][j]);
		}
	}
}

//does what it says on the tin
//requires words in file referred to by infileString to all be
//in lower case.
void countDigraphs(char * infileString, 
	int digraphCounts[][NUM_LETTERS_IN_ENG_ALPHA]) {
	FILE * infile = fopen(infileString, "r");
	
	char nextWord[150] = "";
	int i = 0;
	while (fgets(nextWord, 145, infile) != NULL) {
		//-2 because we're looking at first letter of digraphs
		for (unsigned int i = 0; i < strlen(nextWord) - 2; i++) {
			//is the current char an alphabet character?
			if (isalpha(nextWord[i])) {
				//what about the next one?
				if (isalpha(nextWord[i + 1])) {
					//ascii 'a' = 97
					digraphCounts[nextWord[i] - 97][nextWord[i + 1] - 97]++;
				}
				//if apostrophe, read character after that if able and
				//consider that a digraph
				else if (nextWord[i + 1] == '\'') {
					if (isalpha(nextWord[i + 2])) {
						//ascii 'a' = 97
						digraphCounts[nextWord[i] - 97][nextWord[i + 2] - 97]++;
					}
				}
			}
		}
		i++;
		if (i % 200 == 0) {
			system("cls");
			printf("Counting digraphs...\n\n");
			printf("Processing word %d...", i);
		}
	}
	fclose(infile);
}