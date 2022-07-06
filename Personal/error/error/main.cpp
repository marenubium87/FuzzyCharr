#include <iostream>
#include <exception>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::exception;
using std::vector;

int main() {

	int test = 1;
	// temp = 10;
	vector<int> a;
	a.resize(10);
	test = a.capacity();

	try {
		//test = test / 0;
		a.at(a.capacity() + 5);

	}
	catch (exception& e) {
		cout << e.what();
	}

	return 0;
}