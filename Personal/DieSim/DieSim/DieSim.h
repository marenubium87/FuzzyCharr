#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;


void displayMainMenu();

void printDiePool(vector<int> & diePool);

//completely rewrites elements of die pool based on user input
void adjustDiePool(vector<int> & diePool);