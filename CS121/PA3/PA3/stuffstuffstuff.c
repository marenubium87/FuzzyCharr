//source file for PA3

//grabs header
#include "stuffstuffstuff.h"

//opens file input.dat for reading and returns FILE * var (pointer to input.dat)
FILE * open_input_file(void)
{
	FILE * input = NULL;
	input = fopen("input.dat", "r");
	return input;
}

//reads the next character from infile and returns as char
char read_character(FILE * infile)
{
	char tempCharr = '\0';
	fscanf(infile, "%c", &tempCharr);
	return tempCharr;
}

//casts character to int to extract ascii value
int determine_ascii_value(char character)
{
	int tempInt = 0;
	tempInt = character;
	return tempInt;
}

//determines if character is a newline
//returns NEWLINE if so, else returns NOT_NEWLINE
//dependencies:  determine_ascii_value
int is_line(char character)
{
	int numCharr = 0;
	//get ascii value for character
	numCharr = determine_ascii_value(character);

	//if ascii value = 10 it's a newline, else it's not
	if (numCharr == 10)
	{
		return NEWLINE;
	}
	else
	{
		return NOT_NEWLINE;
	}
}

//if char is a newline, add 1 to current number lines, else return current number lines
int number_lines(char character, int current_number_lines)
{
	if (is_line(character) == NEWLINE)
	{
		return current_number_lines + 1;
	}
	else
	{
		return current_number_lines;
	}
}

//prints "Number of Lines: #" to outfile, where # is the number of lines
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_lines(FILE * infile, FILE * outfile)
{
	//since by default everything starts with 1 line, not 0
	int numberOfLines = 1;

	//go to the beginning of the file
	rewind(infile);

	//reads the next character from infile, determines if it's a newline,
	//and updates numberOfLines accordingly
	numberOfLines = number_lines(read_character(infile), numberOfLines);

	//now do it 9 more times because apparently I hate loops
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);
	numberOfLines = number_lines(read_character(infile), numberOfLines);

	//display result
	print_stats(outfile, "Number of Lines", numberOfLines);
}

//determines if character is a vowel, upper or lower case
//if vowel, return VOWEL else reutrn NOT_VOWEL
//for reference, vowels are aeiou, b/c fuck you, y
int is_vowel(char character)
{
	if (character == 'a' ||
		character == 'e' ||
		character == 'i' ||
		character == 'o' ||
		character == 'u' ||
		character == 'A' ||
		character == 'E' ||
		character == 'I' ||
		character == 'O' ||
		character == 'U')
	{
		return VOWEL;
	}
	else
	{
		return NOT_VOWEL;
	}
}

//if char is a vowel, add 1 to current number of vowels, else return current number of vowels
int number_vowels(char character, int current_number_vowels)
{
	if (is_vowel(character) == VOWEL)
	{
		return current_number_vowels + 1;
	}
	else
	{
		return current_number_vowels;
	}
}

//prints "Number of vowels: #" to outfile, where # is the number of vowels
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_vowels(FILE * infile, FILE * outfile)
{
	int numberOfVowels = 0;

	//go to the beginning of the file
	rewind(infile);

	//reads the next character from infile, determines if it's a vowel,
	//and updates numberOfVowels accordingly
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);

	//now do it 9 more times because canIHazLoop = FALSE
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);
	numberOfVowels = number_vowels(read_character(infile), numberOfVowels);

	//display result
	print_stats(outfile, "Number of Vowels", numberOfVowels);
}

//returns DIGIT if character is a digit 0-9, else return NOT_DIGIT
//dependencies: determine_ascii_value
int is_digit(char character)
{
	int numCharr = 0;
	//get ascii value for character
	numCharr = determine_ascii_value(character);

	//ascii: 0 is 48, 9 is 57
	if (numCharr >= 48 && numCharr <= 57)
	{
		return DIGIT;
	}
	else
	{
		return NOT_DIGIT;
	}
}

//if character is a digit then increment current number of digits, else return current number of digits
int number_digits(char character, int current_number_digits)
{
	if (is_digit(character) == DIGIT)
	{
		return current_number_digits + 1;
	}
	else
	{
		return current_number_digits;
	}
}

//prints "Number of digits: #" to outfile, where # is the number of digits
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_digits(FILE * infile, FILE * outfile)
{
	int numberOfDigits = 0;

	//go to the beginning of the file
	rewind(infile);

	//reads the next character from infile, determines if it's a digit,
	//and updates numberOfDigits accordingly
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);

	//now do it 9 more times because we live in a loopless world
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);
	numberOfDigits = number_digits(read_character(infile), numberOfDigits);

	//display result to outfile
	print_stats(outfile, "Number of Digits", numberOfDigits);
}

//return ALPHA if char is UPPER or LOWER
//dependencies: is_lower, is_upper
int is_alpha(char character)
{
	//if character is lowercase or uppercase then it's alpha
	if (is_lower(character) == LOWER || is_upper(character) == UPPER)
	{
		return ALPHA;
	}
	else
	{
		return NOT_ALPHA;
	}
}

//if character is a-z or A-Z increment current_number_alphas, else return current_number_alphas
int number_alphas(char character, int current_number_alphas)
{
	if (is_alpha(character) == ALPHA)
	{
		return current_number_alphas + 1;
	}
	else
	{
		return current_number_alphas;
	}
}

//prints "Number of alphas: #" to outfile, where # is the number of alphas
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_alphas(FILE * infile, FILE * outfile)
{
	int numberOfAlphas = 0;

	//go to the beginning of the file
	rewind(infile);

	//reads the next character from infile, determines if it's an alpha,
	//and updates numberOfAlphas accordingly
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);

	//now do it 9 more times because loops escape me
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);
	numberOfAlphas = number_alphas(read_character(infile), numberOfAlphas);

	//display result
	print_stats(outfile, "Number of Alphas", numberOfAlphas);
}

//if character is lower case then return LOWER, else return NOT_LOWER
//dependencies: get_ascii_value
int is_lower(char character)
{
	int numCharr = 0;
	//get ascii value for character
	numCharr = determine_ascii_value(character);

	//a-z (97-122)
	if (numCharr >= 97 && numCharr <= 122)
	{
		return LOWER;
	}
	else
	{
		return NOT_LOWER;
	}
}

//if character is lowercase, increment current_number_lowers, else return current_number_lowers
int number_lowers(char character, int current_number_lowers)
{
	if (is_lower(character) == LOWER)
	{
		return current_number_lowers + 1;
	}
	else
	{
		return current_number_lowers;
	}
}

//prints "Number of lowers: #" to outfile, where # is the number of lowers
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_lowers(FILE * infile, FILE * outfile)
{
	int numberOfLowers = 0;

	//goto beginning (velociraptor rawr)
	rewind(infile);

	//reads the next character from infile, determines if it's a lower,
	//and updates numberOfLowers accordingly
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);

	//just kill me at this point
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);
	numberOfLowers = number_lowers(read_character(infile), numberOfLowers);

	//display result
	print_stats(outfile, "Number of Lowers", numberOfLowers);
}

//if character is upper case then return UPPER, else return NOT_UPPER
//dependencies: get_ascii_value
int is_upper(char character)
{
	int numCharr = 0;
	//get ascii value for character
	numCharr = determine_ascii_value(character);

	//A-Z  (65-90)
	if (numCharr >= 65 && numCharr <= 90)
	{
		return UPPER;
	}
	else
	{
		return NOT_LOWER;
	}
}

//if character is upper case then increment number of uppers, else return current number of uppers
int number_uppers(char character, int current_number_uppers)
{
	if (is_upper(character) == UPPER)
	{
		return current_number_uppers + 1;
	}
	else
	{
		return current_number_uppers;
	}
}

//prints "Number of uppers: #" to outfile, where # is the number of uppers
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_uppers(FILE * infile, FILE * outfile)
{
	int numberOfUppers = 0;

	//go to beginning of file
	rewind(infile);

	//reads the next character from infile, determines if it's an upper,
	//and updates numberOfUppers accordingly
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);

	//welp.
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);
	numberOfUppers = number_uppers(read_character(infile), numberOfUppers);

	//display results
	print_stats(outfile, "Number of Uppers", numberOfUppers);
}

//if character if \f \n \r \t \v ' ' return WHITESPACE else return NOT_WHITESPACE
//dependencies: get_ascii_value
int is_space(char character)
{
	int numCharr = 0;
	//get ascii value for character
	numCharr = determine_ascii_value(character);

	/*relevant ascii codes are
	*  \f  12
	*  \n  10
	*  \r  13
	*  \t  9
	*  \v  11
	*  space  32
	*/
	if ((numCharr >= 9 && numCharr <= 13) || numCharr == 32)
	{
		return WHITESPACE;
	}
	else
	{
		return NOT_WHITESPACE;
	}
}

//if character is \f \n \r \t \v ' ' increment number of spaces, else return without incrementing
int number_spaces(char character, int current_number_spaces)
{
	if (is_space(character) == WHITESPACE)
	{
		return current_number_spaces + 1;
	}
	else
	{
		return current_number_spaces;
	}
}

//prints "Number of spaces: #" to outfile, where # is the number of lines
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_spaces(FILE * infile, FILE * outfile)
{
	int numberOfSpaces = 0;

	//go to the beginning of the file
	rewind(infile);

	//reads the next character from infile, determines if it's whitespace,
	//and updates numberOfSpaces accordingly
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);

	//-hangs self-
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);
	numberOfSpaces = number_spaces(read_character(infile), numberOfSpaces);

	//-unhangs self, displays result-
	print_stats(outfile, "Number of Spaces", numberOfSpaces);
}

//if character is alpha or digit, then return ALNUM, else return NOT_ALNUM
int is_alnum(char character)
{
	//hmm, if only i already wrote the code to check for alpha or digit...
	if (is_alpha(character) == ALPHA || is_digit(character) == DIGIT)
	{
		return ALNUM;
	}
	else
	{
		return NOT_ALNUM;
	}
}

//if character is alphanumeric then increment current number alnums, else return without incrementing
int number_alnums(char character, int current_number_alnums)
{
	if (is_alnum(character) == ALNUM)
	{
		return current_number_alnums + 1;
	}
	else
	{
		return current_number_alnums;
	}
}

//prints "Number of alnums: #" to outfile, where # is the number of alnums
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_alnums(FILE * infile, FILE * outfile)
{
	int numberOfAlnums = 0;

	//go to beginning of file
	rewind(infile);

	//reads the next character from infile, determine if alnum,
	//updates numberOfAlnums accordingly
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);

	//i don't even have a joke at this point, sorry
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);
	numberOfAlnums = number_alnums(read_character(infile), numberOfAlnums);

	//displays result
	print_stats(outfile, "Number of Alnums", numberOfAlnums);
}

//if character is punctuation return PUNCT else return NOT_PUNCT
int is_punct(char character)
{
	int numCharr = 0;
	//get ascii value
	numCharr = determine_ascii_value(character);

	//punctuation is ASCII 33 - 47, 58 - 64, 91 - 96, 123 - 126
	if ((numCharr >= 33 && numCharr <= 47) ||
		(numCharr >= 58 && numCharr <= 64) ||
		(numCharr >= 91 && numCharr <= 96) ||
		(numCharr >= 123 && numCharr <= 126))
	{
		return PUNCT;
	}
	else
	{
		return NOT_PUNCT;
	}
}

//if character is PUNCT increment current_number_puncts, else return current_number_puncts
int number_puncts(char character, int current_number_puncts)
{
	if (is_punct(character) == PUNCT)
	{
		return current_number_puncts + 1;
	}
	else
	{
		return current_number_puncts;
	}
}

//prints "Number of puncts: #" to outfile, where # is the number of puncts
//infile must exist and be open for reading
//outfile must exist and be open for writing
void print_number_puncts(FILE * infile, FILE * outfile)
{
	int numberOfPuncts = 0;

	//go to beginning
	rewind(infile);

	//reads the next character from infile, determines whether it's a punct,
	//and updates numberOfPuncts accordingly
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);

	//i mean, i could draw an ascii penis here, i suppose...
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);
	numberOfPuncts = number_puncts(read_character(infile), numberOfPuncts);

	//displays result
	print_stats(outfile, "Number of Puncts", numberOfPuncts);
}

//prints an integer to outfile, followed by a newline
void print_int(FILE * outfile, int number)
{
	fprintf(outfile, "%d\n", number);
}

//generates ascii value for a character and prints it to outfile
//infile must exist and be open for reading
//outfile must exist and be open for writing
//dependencies: read_character, determine_ascii_value
void do_ascii_shit(FILE * infile, FILE * outfile)
{
	//check out the next character and store it to kitty
	char kittyCharr = '\0';
	kittyCharr = read_character(infile);

	//figure out the ascii value for kitty and print it to outfile
	print_int(outfile, determine_ascii_value(kittyCharr));
}

//do ascii shit ten times, since loops hate me
void do_ascii_shit_ten(FILE * infile, FILE * outfile)
{
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
	do_ascii_shit(infile, outfile);
}

//prints string header and number in following format: "string here": number
//prints that line to outfile
//also prints a newline
void print_stats(FILE * outfile, char header[], int number)
{
	fprintf(outfile, "%s: %d", header, number);
	fprintf(outfile, "\n");
}