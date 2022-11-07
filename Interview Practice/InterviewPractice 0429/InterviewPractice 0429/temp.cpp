//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//
//using std::vector;
//using std::string;
//using std::cin;
//using std::cout;
//using std::fstream;
//using std::endl;
//
////grabs queries from input file and parses them for solution fcn
//vector<vector<string>> parser(void) {
//	fstream input;
//	string tempString;
//	vector<vector<string>> commands;
//
//	//temp vector that will be pushed into commands vector of vectors
//	vector<string> inputCommand;
//
//	input.open("input.txt", std::ios::in);
//
//	while (!input.eof()) {
//		inputCommand.clear();
//		std::getline(input, tempString);
//
//		inputCommand.push_back(tempString);
//
//		if (tempString == "APPEND" || tempString == "MOVE") {
//			std::getline(input, tempString);
//			inputCommand.push_back(tempString);
//		}
//		else if (tempString == "SELECT") {
//			std::getline(input, tempString);
//			inputCommand.push_back(tempString);
//			std::getline(input, tempString);
//			inputCommand.push_back(tempString);
//		}
//
//		commands.push_back(inputCommand);
//	}
//	input.close();
//	return commands;
//}
//
//
//void append(vector<string> & solution, string input, unsigned int & cursorPos,
//			bool & activeSelection, int & left, int & right) {
//	string tempString = "";
//	
//	//does a previous nonzero string exist to append to?
//	if (solution.size() > 0) {
//		tempString = solution[solution.size() - 1];
//	}
//	if (activeSelection) {
//		tempString.replace(left, right - left, input);
//	}
//	else {
//		tempString.insert(cursorPos, input);
//	}
//
//	solution.push_back(tempString);
//	//move cursor to end of added string
//	cursorPos += input.size();
//	activeSelection = false;
//}
//
//void move(vector<string> & solution, string input, unsigned int & cursorPos,
//			bool & activeSelection) {
//	//convert input to number
//	cursorPos = std::stoi(input);
//
//	string tempString = "";
//
//	//does a previous nonzero string exist?
//	if (solution.size() > 0) {
//		tempString = solution[solution.size() - 1];
//	}
//	
//	solution.push_back(tempString);
//
//	//prevents cursor from being out of bounds
//	if (cursorPos > tempString.size()) {
//		cursorPos = tempString.size();
//	}
//	activeSelection = false;
//}
//
//void backspace(vector<string> & solution, unsigned int & cursorPos,
//			bool & activeSelection, int & left, int & right) {
//	string tempString = "";
//
//	//does a previous nonzero string exist to delete from?
//	if (solution.size() > 0) {
//		tempString = solution[solution.size() - 1];
//	}
//	
//	if (activeSelection) {
//		tempString.erase(left, right - left);
//		cursorPos = left;
//	}
//	//no active selection, cursor not at front
//	//(do nothing if cursor at front)
//	else if (cursorPos > 0) {
//		//forces erase (which is del behavior) into backsp behavior
//		tempString.erase(cursorPos - 1, 1);
//		cursorPos -= 1;
//	}
//
//	solution.push_back(tempString);
//	activeSelection = false;
//}
//
//void select(vector<string> & solution, unsigned int & cursorPos, 
//		bool & activeSelection,	int & left, int & right) {
//	string tempString = "";
//
//	//does a previous nonzero string exist to append to?
//	if (solution.size() > 0) {
//		tempString = solution[solution.size() - 1];
//	}
//	
//	if (left < 0) {
//		left = 0;
//	}
//	if (right < 0) {
//		right = 0;
//	}
//	if (left > tempString.size()) {
//		left = tempString.size();
//	}
//	if (right > tempString.size()) {
//		right = tempString.size();
//	}
//
//	solution.push_back(tempString);
//	
//	if (left == right) {
//		cursorPos = left;
//		activeSelection = false;
//	}
//	else {
//		activeSelection = true;
//	}
//	
//}
//
//void copy(vector<string> & solution, string & clipboard, 
//		bool & activeSelection, int & left, int & right) {
//
//	string tempString = "";
//
//	//does a previous nonzero string exist to append to?
//	if (solution.size() > 0) {
//		tempString = solution[solution.size() - 1];
//	}
//
//	if (activeSelection && left < right) {
//		clipboard = tempString.substr(left, right - left);
//	}
//
//	solution.push_back(tempString);
//
//}
//
//void paste(vector<string> & solution, string & clipboard,
//		unsigned int & cursorPos, bool & activeSelection,
//		int & left, int & right) {
//
//	string tempString = "";
//
//	//does a previous nonzero string exist to append to?
//	if (solution.size() > 0) {
//		tempString = solution[solution.size() - 1];
//	}
//	if (activeSelection) {
//		tempString.replace(left, right - left, clipboard);
//	}
//	else {
//		tempString.insert(cursorPos, clipboard);
//	}
//
//	solution.push_back(tempString);
//	//move cursor to end of added string
//	cursorPos = left + clipboard.size();
//	activeSelection = false;
//
//}
//
//
//vector<string> solution(vector<vector<string>> queries) {
//	
//	unsigned int cursorPos = 0;
//	int selectionLeft = 0;
//	int selectionRight = 0;
//
//	bool activeSelection = false;
//
//	string clipboard = "";
//	vector<string> soln;
//
//	for (vector<string> command : queries) {
//		//read next command
//		if (command[0] == "APPEND") {
//			append(soln, command[1], cursorPos, activeSelection, 
//				selectionLeft, selectionRight);
//		}
//		if (command[0] == "MOVE") {
//			move(soln, command[1], cursorPos, activeSelection);
//		}
//		if (command[0] == "BACKSPACE") {
//			backspace(soln, cursorPos, activeSelection,
//				selectionLeft, selectionRight);
//		}
//		if (command[0] == "SELECT")	{
//			selectionLeft = std::stoi(command[1]);
//			selectionRight = std::stoi(command[2]);
//			select(soln, cursorPos, activeSelection, 
//				selectionLeft, selectionRight);
//		}
//		if (command[0] == "COPY") {
//			copy(soln, clipboard, activeSelection, 
//				selectionLeft, selectionRight);
//		}
//		if (command[0] == "PASTE") {
//			paste(soln, clipboard, cursorPos, activeSelection,
//				selectionLeft, selectionRight);
//		}
//	}
//
//	return soln;
//}
//
//int main() {
//
//	/*
//	vector<vector<string>> temp;
//	temp = parser();
//	for (auto i : temp) {
//		for (auto j : i) {
//			cout << j << endl;
//		}
//	}
//	*/
//
//	vector<string> soln;
//	soln = solution(parser());
//
//	for (auto i : soln) {
//		cout << i << endl;
//	}
//	
//	return 0;
//}