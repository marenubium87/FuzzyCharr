#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::fstream;
using std::endl;

//rewrite to create a vector<vector<string>>
//grabs queries from input file and parses them for solution fcn
vector<vector<string>> parser(void) {
	fstream input;
	string tempString;
	vector<vector<string>> commands;

	//temp vector that will be pushed into commands vector of vectors
	vector<string> inputCommand;

	input.open("input.txt", std::ios::in);

	while (!input.eof()) {
		inputCommand.clear();
		std::getline(input, tempString);

		inputCommand.push_back(tempString);

		if (tempString == "APPEND" || tempString == "MOVE") {
			std::getline(input, tempString);
			inputCommand.push_back(tempString);
		}

		commands.push_back(inputCommand);
	}
	input.close();
	return commands;
}


void append(vector<string> & solution, string input, unsigned int & cursorPos) {
	string tempString = "";
	
	//does a previous nonzero string exist to append to?
	if (solution.size() > 0) {
		tempString = solution[solution.size() - 1];
	}

	tempString.insert(cursorPos, input);
	solution.push_back(tempString);

	//move cursor to end of added string
	cursorPos += input.size();

}

void move(vector<string> & solution, string input, unsigned int & cursorPos) {
	//convert input to number
	cursorPos = std::stoi(input);

	string tempString = "";

	//does a previous nonzero string exist?
	if (solution.size() > 0) {
		tempString = solution[solution.size() - 1];
	}
	
	solution.push_back(tempString);

	//prevents cursor from being out of bounds
	if (cursorPos > tempString.size()) {
		cursorPos = tempString.size();
	}
}

void backspace(vector<string> & solution, unsigned int & cursorPos) {
	string tempString = "";

	//does a previous nonzero string exist to delete from?
	if (solution.size() > 0) {
		tempString = solution[solution.size() - 1];
	}
	
	if (cursorPos == 0) {
		//can't delete if already at front
		solution.push_back(tempString);
		return;
	}
	
	//forces erase (which is del behavior) into backsp behavior
	tempString.erase(cursorPos - 1, 1);
	solution.push_back(tempString);

	cursorPos -= 1;
}

//rewrite to accept a vector<vector<string>>
vector<string> solution(vector<vector<string>> queries) {
	
	unsigned int cursorPos = 0;
	vector<string> soln;

	for (vector<string> command : queries) {
		//read next command
		if (command[0] == "APPEND") {
			append(soln, command[1], cursorPos);
		}
		if (command[0] == "MOVE") {
			move(soln, command[1], cursorPos);
		}
		if (command[0] == "BACKSPACE") {
			backspace(soln, cursorPos);
		}
	}

	return soln;
}

int main() {

	/*
	vector<vector<string>> temp;
	temp = parser();
	for (auto i : temp) {
		for (auto j : i) {
			cout << j << endl;
		}
	}
	*/

	vector<string> soln;
	soln = solution(parser());

	for (auto i : soln) {
		cout << i << endl;
	}
	
	return 0;
}