//source for Lab 1

#include "moo.h"

//aux function, prints target string to console
void printString(char * target) {
	int i = 0;
	printf("\"");
	while (target[i] != '\0') {
		printf("%c", target[i]);
		i++;
	}
	printf("\"\n");
}

//reverses target string recursively
//when calling, pass in 0 and strlen - 1 for left and right respectively
//returns reversed string
char * recurRevString(char * target, int left, int right) {
	if (right - left <= 0) {
		return target;
	}
	else {
		char mrow = target[left];
		target[left] = target[right];
		target[right] = mrow;
		return recurRevString(target, left + 1, right - 1);
	}
}

//implementation of strTok for task 2b
char * myStrTok(char * str, char * delim) {
	
	//if NULL was passed in for str, treat as subsequent call to strtok
	//starting at location of pToken
	static char * pToken = NULL;
	if (str == NULL) {
		//no more tokens in string
		if (pToken == NULL) {
			return NULL;
		}
		else {
			str = pToken;
		}
	}
	else {
		//if this is the first call, need to check if string is empty
		if (*str == '\0') {
			return NULL;
		}
	}

	int containedInDelim = 0;
	do {
		containedInDelim = 0;
		for (unsigned int i = 0; i < strlen(delim); i++) {
			//does current char in str match any element in delim?
			if (*str == delim[i]) {
				//if so we skip current char in str
				//and start checking next one
				str += 1;
				containedInDelim = 1;
				break;
			}
		}
		//by advancing, did we hit the end of the string?
		if (*str == '\0') {
			return NULL;
		}
		
	} while (containedInDelim);
	//now we're at first char not contained in delim
	pToken = str;
	containedInDelim = 0;
	//find where this token ends
	do {
		str++;
		//is this next character in delim?
		if (*str == '\0') {
			//reached end of string without finding delim char
			//returns the pointer to beginning of token
			str = pToken;
			pToken = NULL;
			return str;
		}
		else {
			for (unsigned int i = 0; i < strlen(delim); i++) {
				if (*str == delim[i]) {
					containedInDelim = 1;
					break;
				}
			}
		}
	} while (containedInDelim == 0);
	//str is now at the location of the first delim char post-start
	char * pTemp = str;
	*str = '\0';
	//set location of str to start of token for immiment return
	str = pToken;
	//places token at next character assuming not end
	if (*(pTemp + 1) != '\0') {
		pToken = pTemp + 1;
	}
	else {
		pToken = NULL;
	}
	return str;
}

//comparison function required by qsort
int takeBothObjectsAndExamineThemThenDecideWhichGoesAheadOfTheOther(
	const char * a, const char * b) {
	if (*a < *b) {
		return -1;
	}
	if (*a == *b) {
		return 0;
	}
	if (*a > *b) {
		return 1;
	}
}

//precondition - strings sorcerer and wizard must be presorted
//target needs to have size at least strlen(sorcerer) + strlen(wizard) + 1
//returns target string which is the merge of sorcerer and wizard
char * mergeStrings1(char * sorcerer, char * wizard, char * target) {
	//i is sorcerer index, j is wizard index, k is target index
	int i = 0, j = 0, k = 0;
	//both strings still have characters left to assign
	while (sorcerer[i] != '\0' && wizard[j] != '\0') {
		if (sorcerer[i] <= wizard[j]) {
			target[k] = sorcerer[i];
			i++;
		}
		else {
			target[k] = wizard[j];
			j++;
		}
		k++;
	}
	//now one of the strings has no more elements, so append remaining
	//from other string (until we also hit the null char)
	if (sorcerer[i] == '\0') {
		while (wizard[j] != '\0') {
			target[k] = wizard[j];
			j++;
			k++;
		}
	}
	else {
		while (sorcerer[i] != '\0') {
			target[k] = sorcerer[i];
			i++;
			k++;
		}
	}
	//append null to end of combined
	target[k] = '\0';
	return target;
}

//precondition - strings sorcerer and wizard must be presorted
//returns target string (on the heap) which is the merge of sorcerer and wizard
char * mergeStrings2(char * sorcerer, char * wizard) {
	char * target = NULL;
	//please sir, i would like some memory
	target = (char *)malloc(sizeof(char));

	//i is sorcerer index, j is wizard index, k is target index
	int i = 0, j = 0, k = 0;
	//both strings still have characters left to assign
	while (sorcerer[i] != '\0' && wizard[j] != '\0') {
		if (sorcerer[i] <= wizard[j]) {
			target[k] = sorcerer[i];
			i++;
		}
		else {
			target[k] = wizard[j];
			j++;
		}
		//at this step target has k + 1 elements, and we need to allocate
		//one additional element, thus k + 2
		target = (char *)realloc(target, (k + 2) * sizeof(char));
		k++;
	}
	//now one of the strings has no more elements, so append remaining
	//from other string (until we also hit the null char)
	if (sorcerer[i] == '\0') {
		while (wizard[j] != '\0') {
			target[k] = wizard[j];
			j++;
			//pls sir, may i have some more
			target = (char *)realloc(target, (k + 2) * sizeof(char));
			k++;
		}
	}
	else {
		while (sorcerer[i] != '\0') {
			target[k] = sorcerer[i];
			i++;
			//pls sir, may i have some more
			target = (char *)realloc(target, (k + 2) * sizeof(char));
			k++;
		}
	}
	//append null to end of combined
	target[k] = '\0';
	return target;
}

//precondition - strings sorcerer and wizard must be presorted
//merges wizard into sorcerer in sorted order
//returns sorcerer, the string that was merged into
char * mergeStrings3(char * sorcerer, char * wizard) {
	//let i deal with current location of sorcerer
	//let j deal with current location of wizard
	//let sorcEnd be the ending element (the null char) of sorcerer
	int i = 0;
	for (unsigned int j = 0; j < strlen(wizard); j++) {
		
		//there is no off by one error here b/c the value of 
		//strlen(sorcerer) is also the location of the null element in sorcerer
		int sorcEnd = strlen(sorcerer);
		//find where we need to insert j
		while (sorcerer[i] <= wizard[j]) {
			i++;
		}
		//sorcerer[i] is now the first element greater than wizard[j]
		//allocate space by shifting all elements backward including i
		for (; sorcEnd >= i; sorcEnd--) {
			sorcerer[sorcEnd + 1] = sorcerer[sorcEnd];
		}
		//insert element from wizard
		sorcerer[i] = wizard[j];
	}
	return sorcerer;
}

