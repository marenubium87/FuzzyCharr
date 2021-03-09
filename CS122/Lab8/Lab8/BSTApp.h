//header for app to read and sort names

#include "BST.h"

//wrapper to test tree operations in main
void treeOperations(void);

//reads names from input file until all names exhausted, and stores them
//into namesArray
//precondition:  namesArray has enough elements to store all entries from input
void readNames(ifstream & input, string namesArray[]);

//prints elements of target string array to console
void printArray(string target[]);

//uses a BST to sort source array
//calls insertIntoTree and extract method
void BSTSort(string source[]);

//wrapper to test bst sort operations in main
void sortOperations(void);