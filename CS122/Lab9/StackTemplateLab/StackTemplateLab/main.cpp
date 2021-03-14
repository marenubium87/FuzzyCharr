// This example illustrates how to define a Stack class template.

#include "TestStack.h"
#include <ctype.h>

//#include <vector>

//postfix calculator
void postfixCalc() {
	Stack<int> opStack;
	char tempCharr = '\0';
	int n1 = 0, n2 = 0;
	while (1) {

		cout << endl <<
			"Type a postfix string with each integer or operand " << endl <<
			"separated by a space, or type 'q' to quit." << endl << endl;

		cin.get(tempCharr);
		if (tempCharr == 'q') {
			return;
		}
		
		while (tempCharr != '\n' && tempCharr != '=') {
			if (isdigit(tempCharr)) {
				n1 = (int)(tempCharr - '0');
				opStack.push(n1);
			}
			//if not a digit, tempCharr must be an operator or a space
			else if (tempCharr != ' ') {
				if (opStack.getSize() < 2) {
					tempCharr = '\n';
					break;
				}
				opStack.pop(n2);
				opStack.pop(n1);
				switch (tempCharr) {
				case '+':
					n1 = n1 + n2;
					break;
				case '-':
					n1 = n1 - n2;
					break;
				case '*':
					n1 = n1 * n2;
					break;
				case '/':
					n1 = n1 / n2;
					break;
				}
				opStack.push(n1);
			}
			cin.get(tempCharr);
		}

		//is there no character to read?
		if (tempCharr == '\n') {
			cout << "Postfix expression malformed... aborting operation." << endl;
			
		}
		//if we hit the = symbol
		else if (tempCharr == '=') {
			if (opStack.getSize() != 1) {
				cout << "Postfix expression malformed... aborting operation." << endl;
			}
			else {
				opStack.pop(n1);
				cout << "Answer is " << n1 << endl;
			}
		}
		//clears cin buffer and stack after successful or unsuccessful op
		cin.ignore();
		while (!opStack.isEmpty()) {
			opStack.pop(n1);
		}
	}
}

int main(void)
{
	int item1 = 31, item2 = 65;
	//	vector<int> my_vector; // vector<> is from the Standard Template Library (STL)
	TestStack<int> tester;
	tester.Test(item1, item2);

	cout << endl << endl << "Postfix Evaluation";
	postfixCalc();

	system("pause");

	return 0;
}