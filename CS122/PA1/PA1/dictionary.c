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
	else if (strncmp(defn, "Of or pertaining", 16) == 0 ||
		strncmp(defn, "Pertaining to", 13) == 0) {
		if (strncmp(PoS, "a.", 2) == 0) {
		//value = 7
			return adjective;
		}
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
		return noChange;
	}
}

//evaluates current line of dictionary, returns int based on code
//corresponding to entries of DeletionType
int evaluateEntry(char * currentLine) {
	static char previousWord[50] = "";

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

//prints out results to the console
void outputResults(char * infileString, int deletionCounts[],
	int lineNumber) {
	system("cls");
	printf("Processing %s...\n\n", infileString);
	printf("Reading line %d...\n\n", lineNumber);
	printf("Deletion counts:\n");
	for (int i = 0; i < 15; i++) {
		printf("Deletion code %2d: %6d\n", i, deletionCounts[i]);
	}
}

//wrapper to process all lines of a single data file
void processDictionaryWrapper(char * infileString, char * outfileString,
	int deletionCounts[]) {

	FILE * infile = fopen(infileString, "r");
	FILE * outfile = fopen(outfileString, "w");

	int i = 0;
	char nextLine[1401] = "";
	//copy that strtok will not chop up
	char nextLineDuplicate[1401] = "";

	while (fgets(nextLine, 1400, infile) != NULL) {
		strcpy(nextLineDuplicate, nextLine);
		
		//process next line and evaluate deletion code here
		int deletionCode = evaluateEntry(nextLine);
		fprintf(outfile, "%2d  ", deletionCode);
		fprintf(outfile, "%s", nextLineDuplicate);

		//update deletion counts array
		deletionCounts[deletionCode]++;
		i++;
		if (i % 100 == 0) {
			outputResults(infileString, deletionCounts, i);
		}
	}
	fclose(infile);
	fclose(outfile);
	system("pause");
}