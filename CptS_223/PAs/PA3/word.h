/**
 *
 *  Word object for storing a single word in our dictionary hash table
 *   Aaron S. Crandall <acrandal@gmail.com>
 *   Copyright 2017 - Educational use only
 *
 */

#ifndef __WORD_H
#define __WORD_H

#include <string>
#include <algorithm>

using namespace std;

class Word
{
	public:

	string myword;
	string definition;

	Word( ) : myword( "" ), definition( "" ) { }
	Word( string w, string def ) : myword( w ), definition( def ) { }

	string to_string()
	{
		string ret = myword + " : " + definition;
		return ret;
	}
};

//returns true if two Words have the same myword string
//after conversion to lowercase
bool operator==(Word lhs, Word rhs) {
	string lhsWord = lhs.myword;
	string rhsWord = rhs.myword;

	transform(lhsWord.begin(), lhsWord.end(), lhsWord.begin(), 
				[](unsigned char c) {return tolower(c);});

	transform(rhsWord.begin(), rhsWord.end(), rhsWord.begin(), 
				[](unsigned char c) {return tolower(c);});

	return (lhsWord == rhsWord);
}

#endif
