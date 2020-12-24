//header file for functions to deal with genres

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <math.h>

//genre structure (singly-linked list)
typedef struct genreNode {
	char genre[40];
	struct genreNode * pNext;
} GenreNode;

//allocates space on the heap for a new GenreNode and initializes
//with information found in targetGenre
//returns address of GenreNode on the heap
GenreNode * makeGenre(char * targetGenre);

//inserts genreNode contaniing targetGenre in front of genre list
//remember to pass in the *location* of pGenreHead when calling
void insertGenreAtFront(GenreNode ** pList, char * targetGenre);

//deletes node containing targetGenre, if found from the list
//returns true if fcn found a match and deleted, false if it didn't
//remember to pass in the *location* of pHead when calling
int deleteGenre(GenreNode ** pList, char * targetGenre);

//lists out all contents of genre linked list to console
void printGenreList(GenreNode * pHead);

//lists out all contents of genre linked list to outfile
void printGenreListFile(GenreNode * pHead, FILE * outfile);

//function called by the rewriting stone tablets functionality
//if targetGenre is found in pGenreList, deletes it UNLESS targetGenre
//is the last genre in pGenreList
//if targetGenre is not found in pGenreList, will add targetGenre to pGenreList
void modifyGenreList(GenreNode ** pGenreList, char * targetGenre);