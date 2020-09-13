//header file for lab 9

#define _CRT_SECURE_NO_WARNINGS
#define FIRST 1
#define SECOND 2

#include <stdio.h>
#include <Windows.h>

//returns length of string s as int
//does not include null character
int my_strlen(const char * s);

//copies all characters from source char array to destination char array
//including the null character.
//returns the destination string
char * my_strcpy(char * dest, const char * source);

//strcat.  Mrow!
//appends copy of source char array onto the end of destination char array
//overwrites the original null char of destination char array and places
//a new null char at end of append.  returns destination string
char * my_strcat(char * dest, const char * source);

//compares char array pointed to by s1 with char array pointed to by s2
//if s1 comes before s2 in dictionary ordering, return -1
//if s2 comes before s1 in dictionary ordering, return 1
//if both strings are identical return 0
int my_strcmp(const char * s1, const char * s2);