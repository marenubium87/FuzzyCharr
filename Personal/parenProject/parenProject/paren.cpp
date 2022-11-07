#include "paren.h"

bool isValid(string s) {
	stack<char> st;
	for (unsigned int i = 0; i < s.length(); i++) {
		//ascii for } and ] are two values above their { and } counterparts
		if (s[i] == '{' || s[i] == '[') {
			st.push(s[i] + 2);
		}
		//ascii for ) is one above its ( counterpart
		else if (s[i] == '(') {
			st.push(s[i] + 1);
		}
		else {
			//too many closing chars
			if (st.empty()) {
				return false;
			}
			//incorrect closing char
			else if (st.top() != s[i]) {
				return false;
			}
			else {
				st.pop();
			}
		}
	}
	//all opening chars should have a closing char
	if (st.empty()) {
		return true;
	}
	else {
		return false;
	}
}

string stringFixer(string s) {
	if (isValid(s)) {
		return s;
	}

	int leadingCloseParens = 0;
	//defined as nontrailing open parens minus nonleading close parens
	int netParens = 0;
	int trailingOpenParens = 0;

	unsigned int i = 0;
	//count leading close parens
	while (s[i] == ')') {
		leadingCloseParens++;
		i++;
	}
	//count netParens and trailingOpenParens for rest of string
	for (; i < s.length(); i++) {
		if (s[i] == '(') {
			netParens++;
			trailingOpenParens++;
		}
		else {
			netParens--;
			trailingOpenParens = 0;
		}
	}

	//open leading close parens and close trailing open parens
	s.insert(0, leadingCloseParens, '(');
	s.insert(s.end(), trailingOpenParens, ')');

	//correction for number of netParens
	netParens -= trailingOpenParens;
	//number of trailing parens greater
	if (netParens < 0) {
		s.insert(0, -netParens, '(');
	}
	else if (netParens > 0) {
		s.insert(s.end(), netParens, ')');
	}
	return s;

}

void stringFixerTest(void) {
	vector<string> strTestVector;
	strTestVector.push_back("()");
	strTestVector.push_back("))((((");
	strTestVector.push_back(")((()()((");
	strTestVector.push_back("))()()()");
	strTestVector.push_back("((())))))");
	strTestVector.push_back("(((((()))");
	strTestVector.push_back(")");

	for (unsigned int i = 0; i < strTestVector.size(); i++) {
		string fixedString = stringFixer(strTestVector[i]);
		cout << "Test " << i + 1 << endl;
		cout << "Original string: " << strTestVector[i] << endl;
		cout << "Replace string:  " << fixedString << endl;
		cout << "Test ";
		if (isValid(fixedString)) {
			cout << "passed";
		}
		else {
			cout << "FAILED!";
		}
		cout << endl << endl;
	}
}