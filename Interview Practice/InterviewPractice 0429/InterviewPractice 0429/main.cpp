#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <unordered_map>

using std::string;
using std::vector;
using std::endl;
using std::fstream;
using std::getline;
using std::cout;
using std::stack;
using std::unordered_map;

//grabs queries from input file and parses them for solution fcn
vector<vector<string>> parser(void) {
	fstream input;
	string tempString;
	vector<vector<string>> commands;

	//temp vector that will be pushed into commands vector of vectors
	vector<string> inputCommand;

	input.open("inputlvl2.txt", std::ios::in);

	while (!input.eof()) {
		inputCommand.clear();
		std::getline(input, tempString);

		inputCommand.push_back(tempString);

		if (tempString == "APPEND" || tempString == "MOVE") {
			std::getline(input, tempString);
			inputCommand.push_back(tempString);
		}
		else if (tempString == "SELECT") {
			std::getline(input, tempString);
			inputCommand.push_back(tempString);
			std::getline(input, tempString);
			inputCommand.push_back(tempString);
		}

		commands.push_back(inputCommand);
	}
	input.close();
	return commands;
}

class Document {
public:

	Document(string newName);

	string name;

	void process(vector<string> command, vector<string> & solution);

private:

	class Command {
	public:

		Command(string inputString, int newCursorPos,
			int newLeft, int newRight, int newActiveSelection);

		string currentString;
		int cursorPos;
		int left;
		int right;
		bool activeSelection;

	private:

	};

	int cursorPos;
	int left;
	int right;
	bool activeSelection;

	string currentString;

	stack<Command> undoHistory;
	stack<Command> redoHistory;

	void prepareText (void);

	void append(string input);
	void move(string newCursorPos);
	void backspace();
	void select(string left, string right);
	void copy();
	void paste();
	void undo();
	void redo();

};

Document::Document(string newName) {

	name = newName;
	cursorPos = 0;
	left = 0;
	right = 0;
	activeSelection = false;
	currentString = "";
}

Document::Command::Command(string inputString, int newCursorPos,
		int newLeft, int newRight, int newActiveSelection) {

	currentString = inputString;
	cursorPos = newCursorPos;
	left = newLeft;
	right = newRight;
	activeSelection = newActiveSelection;
}

void Document::prepareText(void) {
	
	if (solution.size() > 0) {
		currentString = solution[solution.size() - 1];
	}
}

void Document::process(vector<string> command, vector<string> & solution) {

	if (command[0] == "APPEND") {
		//do appendy things involving command[1]
		append(command[1]);
		undoHistory.push(Command(currentString, cursorPos, left, right,
			activeSelection));
		while (!redoHistory.empty()) {
			redoHistory.pop();
		}

	}
	else if (command[0] == "MOVE") {
		//do movey things involving command[1]
		move(command[1]);
	}
	else if (command[0] == "BACKSPACE") {
		//do backspacey things
		backspace();
		undoHistory.push(Command(currentString, cursorPos, left, right,
			activeSelection));
		while (!redoHistory.empty()) {
			redoHistory.pop();
		}
	}
	else if (command[0] == "SELECT") {
		//do selecty things involving command 1, 2
		select(command[1], command[2]);
	}
	else if (command[0] == "COPY") {
		//do copy things
		copy();
	}
	else if (command[0] == "PASTE") {
		//do pasty things
		paste();
		undoHistory.push(Command(currentString, cursorPos, left, right,
			activeSelection));
		while (!redoHistory.empty()) {
			redoHistory.pop();
		}
	}
	else if (command[0] == "UNDO") {
		undo();
	}
	else if (command[0] == "REDO") {
		redo();
	}

	solution.push_back(currentString);
}

void Document::append(string input) {

	prepareText();

	if (activeSelection) {
		currentString.replace(left, right - left, input);
		cursorPos = left + input.size();
		activeSelection = false;
	}
	else {
		currentString.insert(cursorPos, input);
		cursorPos += input.size();
	}
}

void Document::move(string newCursorPos) {
	prepareText();

	cursorPos = stoi(newCursorPos);

	if (cursorPos < 0) {
		cursorPos = 0;
	}
	else if (cursorPos > (int) currentString.size()) {
		cursorPos = currentString.size();
	}

	if (activeSelection) {
		activeSelection = false;
	}

}

void Document::backspace(void) {
	prepareText();

	if (activeSelection) {
		currentString.erase(left, right - left);

		cursorPos = left;
		activeSelection = false;
	}
	else if (cursorPos > 0) {
		currentString.erase(cursorPos - 1, 1);
		cursorPos--;
	}

}

void Document::select(string newLeft, string newRight) {
	prepareText();

	left = stoi(newLeft);
	right = stoi(newRight);
	if (left < 0) {
		left = 0;
	}
	if (right > currentString.size()) {
		right = currentString.size();
	}

	if (right > left) {
		activeSelection = true;
	}
	else if (right == left) {
		cursorPos = left;
	}

}

void Document::copy(void) {
	prepareText();
	if (activeSelection) {
		clipboard = currentString.substr(left, right - left);
	}

}

void Document::paste(void) {
	prepareText();

	append(clipboard);
}

void Document::undo(void) {
	prepareText();

	if (!undoHistory.empty()) {
		redoHistory.push(undoHistory.top());
		undoHistory.pop();

		if (!undoHistory.empty()) {
			Command & last = undoHistory.top();
			currentString = last.currentString;
			cursorPos = last.cursorPos;
			left = last.left;
			right = last.right;
			activeSelection = last.activeSelection;
		}
		else {
			currentString = "";
			cursorPos = 0;
			activeSelection = false;
		}
	}
}

void Document::redo(void) {
	prepareText();

	if (!redoHistory.empty()) {
		Command & next = redoHistory.top();
		currentString = next.currentString;
		cursorPos = next.cursorPos;
		left = next.left;
		right = next.right;
		activeSelection = next.activeSelection;

		undoHistory.push(next);
		redoHistory.pop();

	}
}

class TextEditor {
public:
	void process(vector<string> command);

	vector<string> getSolution(void) const {
		return solution;
	}

private:

	vector<string> solution;

	Document & activeDocument;

	//key is document name
	unordered_map<string, Document> files;
	string clipboard;

	string create(string newName);
	string switchDoc(string targetDoc);

};

void TextEditor::process(vector<string> command) {

	if (command[0] == "CREATE") {
		//proposed file not found, make new
		if (files.find(command[1]) == files.end()) {
			files[command[1]] = Document(command[1]);
			activeDocument = files[command[1]];
		}
		solution.push_back("");
	}
	else if (command[0] == "SWITCH") {

	}
	else {
		activeDocument.process(command, solution);
	}

}

vector<string> solution(vector<vector<string>> queries) {
	
	Document myText;


	for (vector<string> command : queries) {
		myText.process(command);
	}

	return myText.getSolution();
}

int main() {

	vector<string> stuffs = solution(parser());

	for (string stuff : stuffs) {
		cout << stuff << endl;
	}

	return 0;
}

