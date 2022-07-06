/*
 *  dictionary.h -- A hash-based dictionary for searching definitions
 *   Copyright 2017 - Aaron S. Crandall <acrandal@gmail.com>
 */

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::rand;


class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store

	void parseline( string line ) {
		//isolates out command
		string command = line.substr(0, line.find(' '));
		if(command == "quit") {
			//skip
			return;
		}
		//done for now
		else if(command == "size") {
			cout << " Current dictionary size is " <<
				_dict.size() << endl;
		}
		//done for now
		else if(command == "clear") {
			cout << "Clearing dictionary contents... ";
			_dict.clear();
			cout << "DONE." << endl;
		}
		//done for now
		else if(command == "random") {
			//prevents an infinite loop if no words in dictionary
			if(_dict.size() == 0) {
				cout << "Unable; no words in dictionary." << endl;
				return;
			}
			Word * randomWord = _dict.random();
			cout << randomWord->to_string() << endl;
		}
		//done for now
		else if(command == "help") {
			help();
		}
		else {
			//the rest of the commands need args
			string args = line.substr(line.find(' ') + 1);

			//done for now
			if(command == "remove") {
				args = stripQuotes(args);
				_dict.remove(args);
			}
			//done for now
			else if (command == "define") {
				args = stripQuotes(args);
				if(_dict.contains(args)) {
					Word * targetWord = _dict.find(args);
					targetWord->to_string();
				}
				else {
					cout << "Unknown word." << endl;
				}
			}
			//work on this
			else if (command == "load") {

			}
			//work on this
			else if(command == "unload") {

			}
			//done for now
			else if(command == "print") {
				if(_dict.size() == 0) {
					cout << "No words in dictionary." << endl;
					return;
				}
				//this means that args substr was same as original string
				//in other words, no second (numerical) arg was given
				if(args == "print") {
					//this will print everything, be advised!
					//wtf doesn't this work?
					//_dict.print();
				}
				else {
					_dict.print(stoi(args));
				}
			}
			//done for now
			else if(command == "add") {
				//args needs to be broken up into two arguments
				size_t pos = args.find(" \"");
				string myWord = args.substr(0, pos);
				string myDefn = args.substr(pos + 1);
				myWord = stripQuotes(myWord);
				myDefn = stripQuotes(myDefn);

				_dict.insert(myWord, Word(myWord, myDefn));
			}
		}
		
		//cout << " [d] Parsing line: " << line << endl;
        cout << endl;
	}

	//done for now
	void help(void) {
		cout << "      |\\      _,,,---,,_" << endl;
		cout << "ZZZ   /,`.-'`'    -.  ;-;;,_" << endl;
		cout << "     |,4.  ) )-,_. ,\\ (  `'-'" << endl;
		cout << "    '---''(_/--'  `-'\\_) " << endl;
	}

	//aux function to strip quotes from targets if they exist
	string stripQuotes(string target) {
		if(target[0] == '"') {
			return target.substr(1, target.length() - 2);
		}
		else {
			return target;
		}
	}

	public:
		Dictionary()	// Default constructor
		{
			std::srand(std::time(nullptr));
		}

	/**
	 *  Run the main dictionary user interface
	 */



	void run_ui() {
		// print out header
		cout << "+------------------------------------------+" << endl;
		cout << "|-- Welcome to the best dictionary evar! --|" << endl;
		cout << "+------------------------------------------+" << endl;

		string instr;
		cout << " Enter command (^D or EOF quits): ";

		// read in user input until eof
		while (getline(cin, instr)) {
			cout << endl << " --debug-- Entered command: " << instr << endl;
			parseline(instr);
			// call function based on line contents
			// print results

			cout << "Enter command: ";
		}
		cout << endl;
	}

};



#endif
