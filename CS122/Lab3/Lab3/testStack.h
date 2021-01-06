//header for stack test functions

#include "lab3.h"

//aux function for testing
//clears targetStack's contents and frees memory
void deleteStack(StackNode ** targetStack);

//test function for stack push
//returns TRUE if all tests passed, FALSE else
int testPush();

//test function for isEmpty
//returns TRUE if tests passed, FALSE else
//requires push function to work, so test after that
int testIsEmpty();

//test function for stack pop
//returns TRUE if all tests passed, FALSE else
//requires push and isEmpty functions to work, so test after those
int testPop();

//test function for peek
//returns TRUE if tests passed, FALSE else
//requires all previous tests to work, so test after those
int testPeek();

//wrapper to conduct all tests
void testWrapper();