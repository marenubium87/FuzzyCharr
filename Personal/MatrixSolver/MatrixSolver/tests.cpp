//source for test functions for rational class and matrix solver

#include "tests.h"

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;

//test function for GCD
bool bulkTestGCD() {
	//list of 1 and primes, any two entries here are guaranteed to be co-prime
	int primes[14] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
	//pick two numbers x and y, x != y from the above list
	int x = primes[rand() % 14];
	int y = primes[rand() % 14];

	while (x == y) {
		y = primes[rand() % 14];
	}

	int randVal = rand() % 20000;
	//set up n1 and n2 such that the GCD will be randVal every time

	int n1 = (1 + randVal) * x;
	int n2 = (1 + randVal) * y;

	int GCDResult = findGCD(n1, n2);
	if (randVal + 1 == GCDResult) {
		return true;
	}
	else {
		cout << "Failure for n1 = " << n1 << " and n2 = " << n2 << endl;
		cout << "Expected GCD is " << randVal << ", result is " << GCDResult;
		cout << endl;
		return false;
	}
}

//wrapper function for all tests
void testWrapper() {
	//seed RNG
	srand((unsigned int)time_t(NULL));
	int passed = 0;
	int failed = 0;
	int i = 0;
	cout << "Running tests ..." << endl;
	for (; i < 1000000; i++) {
		if (testGCD()) {
			passed++;
		}
		else {
			failed++;
		}
	}
	cout << "Tests complete." << endl;
	cout << passed << " successes, " << failed << " failures";
	cout << endl << endl;
}