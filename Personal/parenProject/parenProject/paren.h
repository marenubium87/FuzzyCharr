#include <iostream>
#include <stack>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::vector;

//determines if an input string s containing only characters from
//the following set:  ()[]{}  is valid, i.e. fits the following criteria:
//open brackets must be closed by same type of brackets
//open brackets must be closed in the correct order
bool isValid(string s);

//given an input string of some number of ( and )s, returns a string
//that is valid, i.e. passes the valid string criteria given by the
//isValid function above
string stringFixer(string s);

//testing function for string fixer
void stringFixerTest(void);

