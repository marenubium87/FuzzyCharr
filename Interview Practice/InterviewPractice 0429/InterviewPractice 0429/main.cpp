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

//grabs queries from input file and parses them for solution fcn
vector<string> parser(void) {
	fstream input;
	string tempString;
	vector<string> commands;


	input.open("input.txt", std::ios::in);
	
	int delimLocation;

	while (!input.eof()) {
		std::getline(input, tempString);
		delimLocation = tempString.find(',');

		//cut string into two and insert into vector, trimming quotation marks
		//unless command is backspace (nothing after delim in that case)
		commands.push_back(tempString.substr(0, delimLocation));
		if (tempString.size() > delimLocation + 1) {
			tempString = tempString.substr(delimLocation + 2);
			tempString.pop_back();
			commands.push_back(tempString);
		}
	}

	input.close();
	return commands;
}

void appendFcn(vector<string> & solution, string input, unsigned int & cursorPos) {
	string tempString = "";
	
	//does a previous nonzero string exist to append to?
	if (solution.size() > 0) {
		tempString = solution[solution.size() - 1];
	}

	//if cursor isn't at start, append first part of string into next
	//element in vector
	if (cursorPos > 0) {
		solution.push_back(tempString.substr(0, cursorPos));
		//append input into vector
		solution[solution.size() - 1].append(input);
	}
	else {
		//if cursor is at start, just place the input in
		solution.push_back(input);
	}

	//if the cursor was not at the end of the string, add the second part
	//of the original string after the input string
	if (cursorPos < tempString.size()) {
		solution[solution.size() - 1].append(tempString.substr(cursorPos));
	}

	//move cursor to end of added string
	cursorPos += input.size();
}

void moveFcn(vector<string> & solution, string input, unsigned int & cursorPos) {
	//convert input to number
	cursorPos = std::stoi(input);

	if (cursorPos < 0) {
		cursorPos = 0;
	}
	else if (cursorPos > solution[solution.size() - 1].size()) {
		cursorPos = solution[solution.size() - 1].size();
	}
}

void backspaceFcn(vector<string> & solution, unsigned int & cursorPos) {
	string tempStr = solution[solution.size() - 1];
	if (cursorPos == 0) {
		//can't delete if already at front
		return;
	}
	//if cursor position > 1 then need to break into substrings,
	//otherwise simply append the "second" part since there's only one substr
	else if (cursorPos > 1) {
		solution.push_back(tempStr.substr(0, cursorPos - 1));
		solution[solution.size() - 1].append(tempStr.substr(cursorPos));
	}
	else {
		solution.push_back(tempStr.substr(cursorPos));
	}

	cursorPos -= 1;
}


vector<string> solution(vector<string> queries) {
	
	unsigned int cursorPos = 0;
	vector<string> soln;

	for (unsigned int i = 0; i < queries.size(); i++) {
		//read next command
		if (queries[i] == "APPEND") {
			appendFcn(soln, queries[i + 1], cursorPos);
			cout << soln[soln.size() - 1] << endl;
			i++;
		}
		else if (queries[i] == "MOVE") {
			moveFcn(soln, queries[i + 1], cursorPos);
			i++;
		}
		else if (queries[i] == "BACKSPACE") {
			backspaceFcn(soln, cursorPos);
		}
		cout << "Cursor position now at " << cursorPos << endl;
	}

	return soln;
}




int main() {


	vector<string> temp;
	/*temp = parser();
	for (auto var : temp) {
		cout << var << endl;
	}*/

	solution(parser());
	return 0;
}