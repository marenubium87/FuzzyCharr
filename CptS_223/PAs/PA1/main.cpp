/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 * Now also doing testing & height calculations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *  * Also doing height calculations
 *
 */

#include <iostream>
#include <iomanip>
#include <queue>
#include <cstring>
#include <fstream>
#include <math.h>
#include "BST.h"
#include "TestData.h"

using namespace std;
using std::fstream;

/*
 *  Interface to run all tests if --test is passed on command line
 */
void runTests() {
	cout << " [x] Running tests. " << endl;
	TestData *testing = new TestData();			// Create object with testing data and interfaces

  BST<int> *bst_test = new BST<int>;

	/* Should make a tree like this:
              10
         5          14
     1      7           17
                            19
                          18

   */
	int testval = testing->get_next_minitest();
	while( testval >= 0 ){
		bst_test->add( testval );
		testval = testing->get_next_minitest();
	}
	cout << " [x] Should print out in pre order: 10 5 1 7 14 17 19 18 " << endl;
  cout << " [x] Resulting print out test:      ";
	bst_test->printPreOrder();
  cout << endl;
  cout << "Number of nodes is " << bst_test->nodesCount() << endl;

	//changed to 4 with permission from instructor
	cout << " [x] Should print a tree height of  : 4" << endl;
  cout << " [x] Currently calculating height of: ";
  cout << bst_test->height();
  cout << endl;
}


/*
 * Generate the CSV file for the project output here
 */
void genCSV() {
	cout << " [x] Generating CSV output file. " << endl;

	TestData testValues;
	BST<int> sorted, balanced, scram0, scram1, scram2, scram3, scram4;

	fstream output;
	output.open("data.csv", std::ios::out);

	//write header line
	output << "N,log_2(N),Sorted,Balanced,Scrambled0,Scrambled1,"
		<< "Scrambled2,Scrambled3,Scrambled4" << endl;

	//write line for n = 0 (so that poor computer doesn't try to do log_2(0))
	output << "0,N/A,-1,-1,-1,-1,-1,-1,-1" << endl;

	int n = 0;
	int nextSortedVal = testValues.get_next_sorted();
	int nextBalancedVal = testValues.get_next_balanced();
	int nextScramVal0 = testValues.get_next_scrambled(0);
	int nextScramVal1 = testValues.get_next_scrambled(1);
	int nextScramVal2 = testValues.get_next_scrambled(2);
	int nextScramVal3 = testValues.get_next_scrambled(3);
	int nextScramVal4 = testValues.get_next_scrambled(4);

	while(nextSortedVal >= 0) {
		n++;

		if(n % 50 == 0) {
			cout << "\r" << "Inserted " << n << " elements into trees...";
		}

		sorted.add(nextSortedVal);
		balanced.add(nextBalancedVal);
		scram0.add(nextScramVal0);
		scram1.add(nextScramVal1);
		scram2.add(nextScramVal2);
		scram3.add(nextScramVal3);
		scram4.add(nextScramVal4);

		output << n << "," << setprecision(3) << log2(double(n)) << ","
			<< sorted.height() << "," << balanced.height() << ","
			<< scram0.height() << "," << scram1.height() << "," 
			<< scram2.height() << "," << scram3.height() << "," 
			<< scram4.height() << endl;

		nextSortedVal = testValues.get_next_sorted();
		nextBalancedVal = testValues.get_next_balanced();
		nextScramVal0 = testValues.get_next_scrambled(0);
		nextScramVal1 = testValues.get_next_scrambled(1);
		nextScramVal2 = testValues.get_next_scrambled(2);
		nextScramVal3 = testValues.get_next_scrambled(3);
		nextScramVal4 = testValues.get_next_scrambled(4);
	}

	/*  Sample of how to use the TestData structure for getting the test data sets
	int sorted = testing->get_next_sorted();  
	while(sorted >= 0){
		bst_sorted->add( sorted );
		sorted = testing->get_next_sorted();
	}
	cout << "Sorted height: " << bst_sorted->height() << endl;
  */

    // make a file: OutputData-BST.csv
		// make 7 trees (sorted, balanced, scrambled[0..4])
		// fill trees with data from TestData
		//  -- as you fill, get the heights and output to CSV file: log_2 N, height sorted, height balanced, height scrambled[0..4]
    //  -- fill until the get_next_* functions return -1


	cout << "\n";
	output.close();
}


/*
 *   Main function for execution
 */
int main( int argc, char* argv[] ) {
	if( argc > 1 && !strcmp(argv[1], "--test") )
	{
		cout << " [x] Program in test mode, doing simple tests. " << endl;

		runTests();  // testing should just do a simple tree insert set and search
	}
	else
	{
		cout << " [x] Program built and running in full CSV generation mode. " << endl;
		genCSV();
	}
	return 0;
}
