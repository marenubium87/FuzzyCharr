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
//returns true if all tests passed, false else
bool testGCD() {
	int numFails = 0;
	int numTests = 0;
	cout << "Testing find GCD ..." << endl;
	cout << "(Ignore all error messages until test passed/failed status)"
		<< endl;
	//testing both numbers = 1
	if (findGCD(1, 1) != 1) {
		numFails++;
	}
	numTests++;
	//testing both numbers same, prime, even
	if (findGCD(2, 2) != 2) {
		numFails++;
	}
	numTests++;
	//testing both numbers same, prime, odd
	if (findGCD(5, 5) != 5) {
		numFails++;
	}
	numTests++;
	//testing both numbers same, composite, even
	if (findGCD(12, 12) != 12) {
		numFails++;
	}
	numTests++;
	//testing both numbers same, composite, odd
	if (findGCD(21, 21) != 21) {
		numFails++;
	}
	numTests++;
	//testing n1 = 1, n2 = prime
	if (findGCD(1, 7) != 1) {
		numFails++;
	}
	numTests++;
	//testing n1 = prime, n2 = 1
	if (findGCD(7, 1) != 1) {
		numFails++;
	}
	numTests++;
	//testing n1 = 1, n2 = composite
	if (findGCD(1, 15) != 1) {
		numFails++;
	}
	numTests++;
	//testing n1 = composite, n2 = 1
	if (findGCD(18, 1) != 1) {
		numFails++;
	}
	numTests++;
	//testing GCD = n1
	if (findGCD(20, 60) != 20) {
		numFails++;
	}
	numTests++;
	//testing GCD = n2
	if (findGCD(90, 15) != 15) {
		numFails++;
	}
	numTests++;
	//testing GCD has no powers of 2
	if (findGCD(9, 21) != 3) {
		numFails++;
	}
	numTests++;
	if (findGCD(21, 9) != 3) {
		numFails++;
	}
	numTests++;
	//testing GCD has only powers of 2
	if (findGCD(16, 40) != 8) {
		numFails++;
	}
	numTests++;
	if (findGCD(40, 16) != 8) {
		numFails++;
	}
	numTests++;
	//testing GCD composite
	if (findGCD(36, 120) != 12) {
		numFails++;
	}
	numTests++;
	if (findGCD(120, 36) != 12) {
		numFails++;
	}
	numTests++;
	//testing GCD uncomputable
	if (findGCD(-6, 12) != 0) {
		numFails++;
	}
	numTests++;
	if (findGCD(5, 0) != 0) {
		numFails++;
	}
	numTests++;
	cout << endl;
	cout << numTests - numFails << " of " << numTests << 
		" GCD tests passed" << endl;
	if (numFails == 0) {
		cout << "ALL TESTS PASSED" << endl;
		return true;
	}
	else {
		cout << "TEST FAILED" << endl;
		return false;
	}
}

//aux test function for GCD, meant to be run in bulk
bool bulkTestGCD() {
	//list of 1 and primes, any two entries here are guaranteed to be co-prime
	int primes[14] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
	//pick two numbers x and y, x != y from the above list
	int x = primes[rand() % 14];
	int y = primes[rand() % 14];

	while (x == y) {
		y = primes[rand() % 14];
	}

	int randVal = rand() % 200000;
	//set up n1 and n2 such that the GCD will be 1 + randVal every time

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

//wrapper to test rational bool operations (== != >= <= > <)
void testRationalBoolOperations() {
	Rational r1(-6, 15), r2(-4, 5);
	cout << "r1 is " << r1 << " and r2 is " << r2 << endl << endl;
	cout << "==" << (r1 == r2) << endl;
	cout << "!=" << (r1 != r2) << endl;
	cout << ">=" << (r1 >= r2) << endl;
	cout << ">" << (r1 > r2) << endl;
	cout << "<=" << (r1 <= r2) << endl;
	cout << "<" << (r1 < r2) << endl;
}

//wrapper to run bulk GCD tests
void bulkGCDTestWrapper() {
	int passed = 0;
	int failed = 0;
	int i = 0;
	cout << endl << "Running bulk GCD tests ..." << endl;
	for (; i < 1000000; i++) {
		if (bulkTestGCD()) {
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

//wrapper function for all tests
void testWrapper() {
	//seed RNG
	srand((unsigned int)time_t(NULL));

	testGCD();
	bulkGCDTestWrapper();
	testRationalBoolOperations();
}