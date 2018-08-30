//header file for lab 9a
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//returns the length of the string pointed to by s as an int
//length does not include the null character
int my_strlen(const char *s);

//written using array notation only
//reverses the non-null elements of target string, then returns pointer to target
//dependencies: my_strlen
char * string_reverse(char target[]);

//written using pointer notation/arithmetic only
//reverses the non-null elements of target string, then returns pointer to target
//dependencies: my_strlen
char * string_reverse_redux(char * target);

//copies all characters in array pointed to by source into the array pointed to by destination
//including the null character
//returns the pointer to the destination string
//WARNING!!! destination must have enough length to fit source (including the null character)
//or very bad things can happen
//dependencies: my_strlen
char * my_strcpy(char destination[], const char source[]);

//maow maow!
//appends a copy of string pointed to by source (including the null char) to the end of the string
//pointed to by destination, overwriting the original null char of the destination
//returns pointer to destination
//WARNING!!! destination must have enough length to append source, including the null character
//or the universe will like, explode or something, man
//dependencies: my_strlen
char * my_strcat(char destination[], const char source[]);

//compares two strings s1 and s2
//if string pointed to by s1 comes before string pointed to by s2, then return -1
//if string pointed to by s2 comes before string pointed to by s1, then return 1
//if string pointed to by s1 is identical to string pointed to by s2, then return 0
int my_strcmp(const char s1[], const char s2[]);

//comparison wrapper b/c I'm too lazy to write a million printf statements
void comparisonWrapper(char s1[], char s2[]);