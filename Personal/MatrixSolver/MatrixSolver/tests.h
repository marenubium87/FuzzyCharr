//header for test functions for rational class and matrix solver
#pragma once

#include "rational.h"

//test function for GCD
bool testGCD();

//aux test function for GCD, meant to be run in bulk
bool bulkTestGCD();

//wrapper to run bulk GCD tests
void bulkGCDTestWrapper();

//wrapper to test rational bool operations (== != >= <= > <)
void testRationalBoolOperations();

//tests rational constructors
void testRationalConstructors();

//tests setting values and signs
void testSetValSetSign();

//tests reduce fcn
void testReduce();

//wrapper function for all tests
void testWrapper();