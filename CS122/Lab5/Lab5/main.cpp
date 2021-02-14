//CS122 Lab 5
//17 Jan 2021

#include "lab5.h"
//#include "lab5task2.h"

int main() {
	Complex c1(5.5, 3.2);
	Complex c2(-2.1, 6.8);
	Complex c3;

	//c3 = c1.add(c2);
	//c3 = add(c1, c2);
	//c3 = c1 + c2;
	//c3 = c1 - c2;
	/*cout << "Enter a complex number in the form a +/- bi: ";
	c1.read();
	cout << "Enter a complex number in the form a +/- bi: ";
	c2.read();*/

	cout << "Enter two complex numbers in the form a + bi" << endl;
	cout << "(each separated by whitespace)" << endl;
	cin >> c1 >> c2;
	c1.print();
	cout << " ";
	c2.print();
	cout << endl;
	//cout << c1 << " " << c2 << endl;

	system("pause");
	return 0;
}

