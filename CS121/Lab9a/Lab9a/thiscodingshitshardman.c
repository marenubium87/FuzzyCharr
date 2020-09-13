//source file for lab 9a

#include "thiscodingshitshard.h"

//returns the length of the string pointed to by s as an int
//length does not include the null character
int my_strlen(const char *s)
{
	int count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return count;
}

//written using array notation only
//reverses the non-null elements of target string, then returns pointer to target
//dependencies: my_strlen
char * string_reverse(char target[])
{
	//figure out the length of the string and then the location of
	//the element before the halfway element, using integer division
	int strLength = my_strlen(target);
	int halfString = strLength / 2;
	//need a temp container for the swapping
	char tempCharr = '\0';

	//the strictly less than is correct; b/c the ith element in the array is in the (i-1)th location
	for (int i = 0; i < halfString; i++)
	{
		//musical chairs; place the trailing element to the temp location, put forward element
		//into slot occupied by trailing element, and then finally put temp location storage into leading element
		
		//remember that the last non-null element has index strLength - 1, NOT strLength!!
		tempCharr = target[(strLength-1) - i];
		target[(strLength - 1) - i] = target[i];
		target[i] = tempCharr;
	}
	return target;
}

//written using pointer notation/arithmetic only
//reverses the non-null elements of target string, then returns pointer to target
//dependencies: my_strlen
char * string_reverse_redux(char * target)
{
	//figure out the length of the string and then the location of
	//the element before the halfway element, using integer division
	int strLength = my_strlen(target);
	int halfString = strLength / 2;
	//need a temp container for swapping
	char tempCharr = '\0';

	for (int i = 0; i < halfString; i++)
	{
		//musical chairs; place the trailing element to the temp location, put forward element
		//into slot occupied by trailing element, and then finally put temp location storage into leading element

		//remember that the last non-null element has index strLength - 1, NOT strLength!!
		tempCharr = *(target + strLength - 1 - i);
		*(target + strLength - 1 - i) = *(target + i);
		*(target + i) = tempCharr;
	}
	return target;
}

//copies all characters in array pointed to by source into the array pointed to by destination
//including the null character
//returns the pointer to the destination string
//WARNING!!! destination must have enough length to fit source (including the null character)
//or very bad things can happen
//dependencies: my_strlen
char * my_strcpy(char destination[], const char source[])
{
	//figure out length of source
	int strLength = my_strlen(source);
	//this time we want to carry over the null character too, so this is why we're going to use
	//strLength as the stop condition, not strLength - 1
	for (int i = 0; i <= strLength; i++)
	{
		destination[i] = source[i];
	}
	return destination;
}

//maow maow!
//appends a copy of string pointed to by source (including the null char) to the end of the string
//pointed to by destination, overwriting the original null char of the destination
//returns pointer to destination
//WARNING!!! destination must have enough length to append source, including the null character
//or the universe will like, explode or something, man
//dependencies: my_strlen
char * my_strcat(char destination[], const char source[])
{
	int sourceLen = my_strlen(source);
	int destLen = my_strlen(destination);
	
	//simba, remember...
	//sourceLen is also where the null char is on the source string, and
	//destLen is also where the null char is on the destination string
	for (int i = 0; i <= sourceLen; i++)
	{
		destination[destLen + i] = source[i];
	}
	return destination;
}


//compares two strings s1 and s2
//if string pointed to by s1 comes before string pointed to by s2, then return -1
//if string pointed to by s2 comes before string pointed to by s1, then return 1
//if string pointed to by s1 is identical to string pointed to by s2, then return 0
//dependencies:  my_strlen
int my_strcmp(const char s1[], const char s2[])
{
	//picks the longest of the two lengths
	int max_len = my_strlen(s1);
	if (my_strlen(s2) > max_len)
	{
		max_len = my_strlen(s2);
	}
	for (int i = 0; i < max_len; i++)
	{
		if (s1[i] < s2[i])
		{
			return -1;
		}
		else if (s1[i] > s2[i])
		{
			return 1;
		}
	}
	//if we've gone through the whole loop and didn't trigger either of those returns ever
	//then the two strings are the same at this point
	return 0;
}

//alternate string compare without using my_strlen fcn
//compares two strings s1 and s2
//if string pointed to by s1 comes before string pointed to by s2, then return -1
//if string pointed to by s2 comes before string pointed to by s1, then return 1
//if string pointed to by s1 is identical to string pointed to by s2, then return 0
int my_strcmp_alt(const char s1[], const char s2[])
{
	int i = 0;

	//this will only break out if s1 and s2 both hit a null character on the same index,
	//i.e. they are the same length, and also haven't already jumped out inside the loop
	while (!(s1[i] == 0 && s2[i] == 0))
	{
		if (s1[i] < s2[i])
		{
			return -1;
		}
		else if (s1[i] > s2[i])
		{
			return 1;
		}
		i++;
	}

	//if it does make it to here, that means all elements were the same and they both hit
	//a null character on the same index, so the two strings must be equal
	return 0;
}

//comparison wrapper b/c I'm too lazy to write a million printf statements
void comparisonWrapper(char s1[], char s2[])
{
	printf("Comparing string \"%s\" with string \"%s\"...\n", s1, s2);
	printf("my_strcmp returns %d\n", my_strcmp(s1, s2));
	printf("my_strcmp_alt returns %d\n\n", my_strcmp_alt(s1, s2));
}