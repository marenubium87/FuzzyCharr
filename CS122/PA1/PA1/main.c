/*
* Aerie, CS122
* Instructor: Reynx <3
* PA1 Data Sanitization
* 22 Oct 2020
*/

#include "dictionary.h"

int main() {
	printf("PA1 - Data Sanitization\n\n");

	FILE * infile = NULL;
	FILE * outfile = NULL;
	FILE * logfile = NULL;

	char infileString[15] = "A.csv";
	char outfileString[15] = "testoutput.txt";

	//keeps track of number of deletions and keeps for log file
	int deletionCounts[15] = { 0 };

	processDictionaryWrapper(infileString, outfileString, 
		deletionCounts);

		//open infile for read
		//open outfile for write
		//get line from infile
		//hit it with all the functions
		//write line to outfile
		//update action array
		//write current status to console

	//write final status to logfile
	//get next file, repeat process


	system("pause");
	return 0;
}