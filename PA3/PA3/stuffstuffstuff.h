//header file for PA3

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//stuff that needs to be defined as per PA instructions
#define NEWLINE 1
#define NOT_NEWLINE 0
#define VOWEL 2
#define NOT_VOWEL 0
#define DIGIT 3
#define NOT_DIGIT 0
#define ALPHA 4
#define NOT_ALPHA 0
#define LOWER 5
#define NOT_LOWER 0
#define UPPER 6
#define NOT_UPPER 0
#define WHITESPACE 7
#define NOT_WHITESPACE 0
#define ALNUM 8
#define NOT_ALNUM 0
#define PUNCT 9
#define NOT_PUNCT 0

//opens input.data for reading
FILE * open_input_file(void);

//reads the next character from the input file
char read_character(FILE * infile);

//returns ASCII value of character as int
int determine_ascii_value(char character);

//determines if character is a newline
//if so return NEWLINE, if not return NOT_NEWLINE
int is_line(char character);

//if character is a newline, add 1 to current number of lines, else return current number of lines
int number_lines(char character, int current_number_lines);

//prints "Number of Lines: #" to outfile, where # is the number of lines
void print_number_lines(FILE * infile, FILE * outfile);

//return VOWEL if vowel, NOT_VOWEL else
int is_vowel(char character);

//adds 1 to current_number_vowels if character is a vowel, else returns current number of vowels
int number_vowels(char character, int current_number_vowels);

//prints "Number of Vowels: #" to outfile, where # is the number of vowels
void print_number_vowels(FILE * infile, FILE * outfile);

//if character is a digit 0-9 return DIGIT else return NOT_DIGIT
int is_digit(char character);

//if character is a digit then increment current number of digits, else return current number
int number_digits(char character, int current_number_digits);

//prints "Number of Digits: #" to outfile, where # is the number of digits
void print_number_digits(FILE * infile, FILE * outfile);

//return ALPHA if char is btwn a-z or A-Z, else return NOT_ALPHA
int is_alpha(char character);

//if character is btwn a-z or A-Z increment current number alphas, else return current number alphas
int number_alphas(char character, int current_number_alphas);

//prints "Number of Alphas: #" to outfile, where # is the number of alphas
void print_number_alphas(FILE * infile, FILE * outfile);

//if character is lower case then return LOWER, else return NOT_LOWER
int is_lower(char character);

//if character is lowercase, increment current number lowers, else return current number lowers
int number_lowers(char character, int current_number_lowers);

//prints "Number of lowers: #" to outfile, where # is the number of lines
void print_number_lowers(FILE * infile, FILE * outfile);

//if character is upper case then return UPPER, else return NOT_UPPER
int is_upper(char character);

//if character is upper then increment number of uppers, else return current number of uppers
int number_uppers(char character, int current_number_uppers);

//prints "Number of uppers: #" to outfile, where # is the number of uppers
void print_number_uppers(FILE * infile, FILE * outfile);

//if character is \f \n \r \t \v return WHITESPACE else return NOT_WHITESPACE
int is_space(char character);

// if character is a space then increment current number of spaces, else return current number of spaces
int number_spaces(char character, int current_number_spaces);

//prints "Number of Spaces: #" to outfile, where # is the number of lines
void print_number_spaces(FILE * infile, FILE * outfile);

// if character is alpha or digit, then return ALNUM, else return NOT_ALNUM
int is_alnum(char character);

// if character is alphanumeric then increment current number alnums, else return without incrementing
int number_alnums(char character, int current_number_alnums);

//prints "Number of alnums: #" to outfile, where # is the number of alnums
void print_number_alnums(FILE * infile, FILE * outfile);

// if character is punctuation return PUNCT else return NOT_PUNCT
int is_punct(char character);

// if character is punct then increment current number puncts, else return without incrementing
int number_puncts(char character, int current_number_puncts);

//prints "Number of puncts: #" to outfile, where # is number of puncts
void print_number_puncts(FILE * infile, FILE * outfile);

// prints number (integer) to outfile
void print_int(FILE * outfile, int number);

// generates ascii value for next character in infile, and prints it to outfile
void do_ascii_shit(FILE * infile, FILE * outfile);

//literally does ascii shit 10 times since I don't love life enough to write loops.
void do_ascii_shit_ten(FILE * infile, FILE * outfile);

// prints string header and number in following format:  "string here": number
// prints that line to outfile
void print_stats(FILE * outfile, char header[], int number);