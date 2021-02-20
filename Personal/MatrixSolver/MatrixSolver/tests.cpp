//source for test functions for rational class and matrix solver

#include "tests.h"

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::fstream;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;

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

//wrapper to test rational operations + - * /
//on r1 and r2; visible flag outputs all results when on
//by default, successful test will not output results
void testRationalOperations(Rational r1, Rational r2, int visibleFlag) {
	if (visibleFlag) {
		cout << "Testing rational operations..." << endl << endl;
	}

	double act, exp;
	Rational r3(0);

	r3 = r1 + r2;
	act = double(r3.getSign() * r3.getNum()) / r3.getDen();
	exp = double((r1.getSign() * r1.getNum() * r2.getDen()
		+ r2.getSign() * r2.getNum() * r1.getDen())) /
		(r1.getDen() * r2.getDen());
	if (act != exp || visibleFlag == 1) {
		if (visibleFlag == 0) {
			cout << "Test error!" << endl;
		}
		cout << "r1 is:  " << r1 << endl;
		cout << "r2 is:  " << r2 << endl << endl;
		cout << "r1 + r2 = " << r3 << " or approx. " << act
			<< " (" << exp << " expected)" << endl;
		system("pause");
		system("cls");
	}

	r3 = r1 - r2;
	act = double(r3.getSign() * r3.getNum()) / r3.getDen();
	exp = double((r1.getSign() * r1.getNum() * r2.getDen()
		- r2.getSign() * r2.getNum() * r1.getDen())) /
		(r1.getDen() * r2.getDen());
	if (act != exp || visibleFlag == 1) {
		if (visibleFlag == 0) {
			cout << "Test error!" << endl;
		}
		cout << "r1 is:  " << r1 << endl;
		cout << "r2 is:  " << r2 << endl << endl;
		cout << "r1 - r2 = " << r3 << " or approx. " << act
			<< " (" << exp << " expected)" << endl;
		system("pause");
		system("cls");
	}

	r3 = r1 * r2;
	act = double(r3.getSign() * r3.getNum()) / r3.getDen();
	exp = double(r1.getSign() * r2.getSign() * r1.getNum() * r2.getNum()) /
		(r1.getDen() * r2.getDen());
	if (act != exp || visibleFlag == 1) {
		if (visibleFlag == 0) {
			cout << "Test error!" << endl;
		}
		cout << "r1 is:  " << r1 << endl;
		cout << "r2 is:  " << r2 << endl << endl;
		cout << "r1 * r2 = " << r3 << " or approx. " << act
			<< " (" << exp << " expected)" << endl;
		system("pause");
		system("cls");
	}

	if (r2.getNum() != 0) {
		r3 = r1 / r2;
		act = double(r3.getSign() * r3.getNum()) / r3.getDen();
		exp = double(r1.getSign() * r2.getSign() * r1.getNum() * r2.getDen()) /
			(r1.getDen() * r2.getNum());
	}

	if (act != exp || visibleFlag == 1) {
		if (visibleFlag == 0) {
			cout << "Test error!" << endl;
		}
		cout << "r1 is:  " << r1 << endl;
		cout << "r2 is:  " << r2 << endl << endl;
		cout << "r1 / r2 = " << r3 << " or approx. " << act
			<< " (" << exp << " expected)" << endl;
		system("pause");
		system("cls");
	}
}

//wrapper to run bulk rational operations tests
void bulkRationalOperationsTest() {
	
	int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
	int trialsMax = 200000, range = 20, offset = range / 2;
	int visibleFlag = 0;
	
	for (int i = 1; i <= trialsMax; i++) {
		if (i % 1000 == 0) {
			system("cls");
			cout << "Bulk rational operations test..." << endl
			<< "Failed scenarios will be displayed below." << endl
			<< "Running test " << i << " of " << trialsMax
				<< " ..." << endl;
		}

		n1 = rand() % range - offset;
		n2 = rand() % range - offset;
		n3 = rand() % range - offset;
		n4 = rand() % range - offset;
		while (n2 == 0) {
			n2 = rand() % 2000 - 1000;
		}
		while (n4 == 0) {
			n4 = rand() % 2000 - 1000;
		}

		Rational r1(n1, n2);
		Rational r2(n3, n4);
		testRationalOperations(r1, r2, visibleFlag);
	}
	cout << endl << "Bulk testing complete." << endl;
}

//wrapper to test rational bool operations (== != >= <= > <)
void testRationalBoolOperations() {
	cout << "Testing rational boolean operations..." << endl << endl
		<< "Given: " << endl << endl;

	Rational r1(-4), r2(12, -3);
	cout << "r1 is " << r1 << endl << "r2 is " << r2 << endl << endl;
	cout << r1 << "== " << r2 << setw(10);
	if (r1 == r2) {
		cout << "TRUE";
	}
	else {
		cout << "FALSE";
	}
	cout << endl;

	cout << r1 << "!= " << r2 << setw(10);
	if (r1 != r2) {
		cout << "TRUE";
	}
	else {
		cout << "FALSE";
	}
	cout << endl;

	cout << r1 << ">= " << r2 << setw(10);
	if (r1 >= r2) {
		cout << "TRUE";
	}
	else {
		cout << "FALSE";
	}
	cout << endl;

	cout << r1 << "<= " << r2 << setw(10);
	if (r1 <= r2) {
		cout << "TRUE";
	}
	else {
		cout << "FALSE";
	}
	cout << endl;

	cout << r1 << ">  " << r2 << setw(10);
	if (r1 > r2) {
		cout << "TRUE";
	}
	else {
		cout << "FALSE";
	}
	cout << endl;

	cout << r1 << "<  " << r2 << setw(10);
	if (r1 < r2) {
		cout << "TRUE";
	}
	else {
		cout << "FALSE";
	}
	cout << endl;
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

//tests setNum, setDen, setSign
void testSetNumDenSign() {
	cout << "TESTING SETTING NUM, DEN, SIGN..." << endl
		<< "(Ignore all error messages until test passed/failed status)" << endl << endl;
	int numTestsFailed = 0;
	int numTestsTotal = 0;

	Rational a;
	//guaranteed to work for positive num and positive den
	//if this test fails the remaining tests should be aborted
	a.setVal(3, 5, 0);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//*************************************
	//testing setNum
	a.setNum(10, 0);
	if (!(a.getSign() == 1 && a.getNum() == 10 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//setting numerator to zero
	a.setVal(3, 5, 0);
	a.setNum(0, 0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//degenerate zero should not flip sign
	a.setNum(-0, 0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//setting numerator negative
	a.setVal(3, 5, 0);
	a.setNum(-8, 0);
	if (!(a.getSign() == -1 && a.getNum() == 8 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//set numerator positive again
	a.setNum(9, 0);
	if (!(a.getSign() == -1 && a.getNum() == 9 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//*************************************
	//testing setDen
	a.setVal(3, 5, 0);
	a.setDen(7, 0);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 7)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//illegal attempt to set den = 0
	a.setDen(0, 0);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 7)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//set den negative
	a.setDen(-5, 0);
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//set den positive again, but fraction should still be negative
	a.setDen(13, 0);
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 13)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//set den negative again, to flip fraction back positive
	a.setDen(-17, 0);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 17)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//*************************************
	//testing setSign
	a.setVal(3, 5, 0);
	//attempting to set sign to nonsensical value
	a.setSign(3);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//setting sign to -1
	a.setSign(-1);
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//setting sign to +1 again
	a.setSign(1);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	a.setVal(0, 4, 0);
	//trying to flip the sign when the fraction is zero should do nothing
	a.setSign(-1);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 4)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	cout << endl << "Total tests complete: " << numTestsTotal << endl
		<< "Tests Passed: " << numTestsTotal - numTestsFailed
		<< ", Tests Failed: " << numTestsFailed << endl;
	if (numTestsFailed == 0) {
		cout << "ALL SET NUM, DEN, SIGN TESTS PASSED";
	}
	else {
		cout << "SET NUM, DEN, SIGN TESTS FAILED";
	}
	cout << endl << endl;
}

//tests setVal fcn
void testSetVal() {
	cout << "TESTING SETVAL..." << endl
		<< "(Ignore all error messages until test passed/failed status)" << endl << endl;
	int numTestsFailed = 0;
	int numTestsTotal = 0;

	Rational a;
	//positive num and den
	a.setVal(3, 5, 0);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//negative num and den
	a.setVal(-3, -5, 0);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//one of num or den positive
	a.setVal(-3, 5, 0);
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	a.setVal(3, -5, 0);
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//illegally setting den to zero
	a.setVal(3, 0, 0);
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//setting numerator to zero, denominator negative
	a.setVal(0, -6, 0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 6)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//degenerate zero scenarios
	a.setVal(-0, -6, 0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 6)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	a.setVal(-0, 6, 0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 6)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//setting to whole numbers
	a.setVal(3);
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	a.setVal(-7);
	if (!(a.getSign() == -1 && a.getNum() == 7 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	a.setVal(0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	a.setVal(-0);
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	cout << endl << "Total tests complete: " << numTestsTotal << endl
		<< "Tests Passed: " << numTestsTotal - numTestsFailed
		<< ", Tests Failed: " << numTestsFailed << endl;
	if (numTestsFailed == 0) {
		cout << "ALL SETVAL TESTS PASSED";
	}
	else {
		cout << "SETVAL TESTS FAILED";
	}
	cout << endl << endl;
}

//tests reduce fcn
void testReduce() {
	cout << "TESTING REDUCE METHOD..." << endl
		<< "(Ignore all error messages until test passed/failed status)" << endl << endl;
	int numTestsFailed = 0;
	int numTestsTotal = 0;

	Rational a;
	//already in lowest terms
	a.setVal(3, 5, 0);
	a.reduce();
	if (!(a.getSign() == 1 && a.getNum() == 3 && a.getDen() == 5)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//whole number, no reduction
	a.setVal(7);
	a.reduce();
	if (!(a.getSign() == 1 && a.getNum() == 7 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//reduce zero, should do nothing
	a.setVal(0);
	a.reduce();
	if (!(a.getSign() == 1 && a.getNum() == 0 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//reduce
	a.setVal(6, 9, 0);
	a.reduce();
	if (!(a.getSign() == 1 && a.getNum() == 2 && a.getDen() == 3)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//reduce negative
	a.setVal(-18, 24, 0);
	a.reduce();
	if (!(a.getSign() == -1 && a.getNum() == 3 && a.getDen() == 4)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	//reduce into whole number
	a.setVal(55, 55, 0);
	a.reduce();
	if (!(a.getSign() == 1 && a.getNum() == 1 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;
	a.setVal(-16, 4, 0);
	a.reduce();
	if (!(a.getSign() == -1 && a.getNum() == 4 && a.getDen() == 1)) {
		numTestsFailed++;
	}
	numTestsTotal++;

	cout << endl << "Total tests complete: " << numTestsTotal << endl
		<< "Tests Passed: " << numTestsTotal - numTestsFailed
		<< ", Tests Failed: " << numTestsFailed << endl;
	if (numTestsFailed == 0) {
		cout << "ALL REDUCE TESTS PASSED";
	}
	else {
		cout << "REDUCE TESTS FAILED";
	}
	cout << endl << endl;
}

//wrapper function for all tests
void testWrapper() {
	//seed RNG
	srand((unsigned int)time_t(NULL));
	
	testGCD();
	bulkGCDTestWrapper();
	system("pause");
	system("cls");
	
	Rational r1(5, 3);
	Rational r2(-2, 1);
	testRationalOperations(r1, r2, 1);
	system("cls");
	
	bulkRationalOperationsTest();
	system("pause");
	system("cls");
	
	testRationalBoolOperations();
	system("pause");
	system("cls");
	
	testRationalConstructors();
	system("pause");
	system("cls");
	
	testSetNumDenSign();
	system("pause");
	system("cls");
	
	testSetVal();
	system("pause");
	system("cls");
	
	testReduce();
	system("pause");
	system("cls");
}

