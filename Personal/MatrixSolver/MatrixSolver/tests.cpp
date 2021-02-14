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
	cout << "TESTING FIND GCD ..." << endl;
	cout << "(Ignore all error messages until test passed/failed status)"
		<< endl << endl;
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

//tests rational constructors
void testRationalConstructors() {
	cout << "TESTING RATIONAL CONSTRUCTION..." << endl
		<< "(Ignore all error messages until test passed/failed status)" << endl << endl;
	int numTestsFailed = 0;
	int numTestsTotal = 0;
	//default construction
	Rational a;
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//construction with denominator = 0
	Rational b(3, 0);
	if (!(b.getSign() == 1 && b.getNum() == 0 && b.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//construction of whole number
	Rational b1(-4);
	if (!(b1.getSign() == -1 && b1.getNum() == 4 && b1.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//construction of nonreduced whole number
	Rational c(18, 3);
	if (!(c.getSign() == 1 && c.getNum() == 6 && c.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//construction with various degenerate versions of zero
	Rational c1(-0, 4);
	if (!(c1.getSign() == 1 && c1.getNum() == 0 && c1.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	Rational c2(0, -5);
	if (!(c2.getSign() == 1 && c2.getNum() == 0 && c2.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	Rational c3(-0, -3);
	if (!(c3.getSign() == 1 && c3.getNum() == 0 && c3.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//construction of various negative sign combinations
	Rational d(-5, 6);
	if (!(d.getSign() == -1 && d.getNum() == 5 && d.getDen() == 6)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	Rational e(5, -6);
	if (!(e.getSign() == -1 && e.getNum() == 5 && e.getDen() == 6)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	
	Rational f(-5, -6);
	if (!(f.getSign() == 1 && f.getNum() == 5 && f.getDen() == 6)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	cout << endl << "Total tests complete: " << numTestsTotal << endl
		<< "Tests Passed: " << numTestsTotal - numTestsFailed
		<< ", Tests Failed: " << numTestsFailed << endl;
	if (numTestsFailed == 0) {
		cout << "ALL RATIONAL CONSTRUCTOR TESTS PASSED";
	}
	else {
		cout << "RATIONAL CONSTRUCTOR TESTS FAILED";
	}
	cout << endl << endl;
}

//tests setting values and signs
void testSetValSetSign() {
	cout << "TESTING SETTING SIGNS AND VALUES..." << endl
		<< "(Ignore all error messages until test passed/failed status)" << endl << endl;
	int numTestsFailed = 0;
	int numTestsTotal = 0;

	Rational a;
	a.setVal(3, 5);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;



}

//tests reduce fcn
void testReduce() {

}

//wrapper function for all tests
void testWrapper() {
	//seed RNG
	srand((unsigned int)time_t(NULL));

	testGCD();
	bulkGCDTestWrapper();
	testRationalBoolOperations();
	system("pause");
	system("cls");
	testRationalConstructors();
	system("pause");
}

