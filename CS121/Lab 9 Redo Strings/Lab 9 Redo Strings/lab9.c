//source file for lab 9

#include "lab9.h"

//returns length of string s as int
//does not include null character
int my_strlen(const char * s) {

	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

//copies all characters from source char array to destination char array
//including the null character.
//returns the destination string
char * my_strcpy(char * dest, const char * source) {
	int i = 0;
	while (source[i] != '\0') {
		dest[i] = source[i];
		i++;
	}
	//i is now at the location where we need to place a null char
	dest[i] = '\0';
	return dest;
}

//strcat.  Mrow!
//appends copy of source char array onto the end of destination char array
//overwrites the original null char of destination char array and places
//a new null char at end of append.  returns destination string
char * my_strcat(char * dest, const char * source) {
	
	//finds index location of null char on destination string
	int i = 0;
	while (dest[i] != '\0') {
		i++;
	}

	//i is now the index of null char on destination, so start copying
	//from source to that location on the destination
	int j = 0;
	while (source[j] != '\0') {
		dest[i + j] = source[j];
		j++;
	}

	//i is now in the location where we need to place a new null char
	dest[i + j] = '\0';
	return dest;
}

//compares char array pointed to by s1 with char array pointed to by s2
//if s1 comes before s2 in dictionary ordering, return -1
//if s2 comes before s1 in dictionary ordering, return 1
//if both strings are identical return 0
int my_strcmp(const char * s1, const char * s2) {
	
	int i = 0;
	//stop and do not enter loop if s1[i] and s2[i] are both null
	while ( s1[i] > 0 || s2[i] > 0 ) {      //2 instructions

		if (s1[i] != s2[i]) {	 // 3 instructions
			if (s1[i] < s2[i]) { // 3 instructions
				return -1;
			}
			else if (s1[i] > s2[i]) {  //3 instructions
				return 1;
			}
		}
		//if both equal, check next character
		i++;					//1 instruction
	}
	//if exited the while loop without returning something already,
	//then both arrays are equal up to and including the null char
	//and thus both strings are equal
	return 0;
}