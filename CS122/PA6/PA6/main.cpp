//PA6 21 Mar 2021

#include "PA6.h"


int main() {
	
	fstream inputFileA("MorseTable.txt", std::ios::in);
	fstream inputFileB("worseMorseTable.txt", std::ios::in);
	BST<char, string> const goodMorse(inputFileA);
	BST<char, string> const badMorse(inputFileB);
	
	string tempStr;
	char tempCharr;
	fstream convertText("Convert.txt", std::ios::in);
	numTraversals = 0;
	cout << "Conversion using better Morse tree..." << endl << endl;
	while (getline(convertText, tempStr)) {
		for (unsigned int i = 0; i < tempStr.length(); i++) {
			tempCharr = (char)tempStr[i];
			tempCharr = toupper(tempCharr);
			if (tempCharr == ' ') {
				cout << "   ";
			}
			else {
				cout << goodMorse.search(tempCharr) << " ";
			}
		}
		cout << endl;
	}
	cout << "Number of edge traversals: " << numTraversals << endl << endl;
	convertText.close();

	convertText.open("Convert.txt", std::ios::in);
	numTraversals = 0;
	cout << "Conversion using worse Morse tree..." << endl << endl;
	while (getline(convertText, tempStr)) {
		for (unsigned int i = 0; i < tempStr.length(); i++) {
			tempCharr = (char)tempStr[i];
			tempCharr = toupper(tempCharr);
			if (tempCharr == ' ') {
				cout << "   ";
			}
			else {
				cout << badMorse.search(tempCharr) << " ";
			}
		}
		cout << endl;
	}
	cout << "Number of edge traversals: " << numTraversals << endl << endl;
	
	convertText.close();

	system("pause");
	return 0;
}