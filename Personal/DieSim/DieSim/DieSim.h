#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;


void displayMainMenu();

void printDiePool(vector<int> & diePool);

void adjustDiePool(vector<int> & diePool);

void setSimMode(int & simMode);

class SimulationRun {

public:

protected:
	vector<int> diePool;

private:

};

SimulationRun * makeNewSim(int simMode);


class SimNumSuccesses : public SimulationRun {
public:
	SimNumSuccesses() {}

	~SimNumSuccesses() { }

protected:

private:
	RollAnalysis a;
	int numTrials;
	vector<vector<int>> cumResults;
};

class RollAnalysis {
public:
	RollAnalysis(vector<int> & diePool, 
		int inputSuccThresh, int inputFailThresh);
	~RollAnalysis() {}

	void roll();

	int getSuccesses();
	int getFails();
	int getNetSuccesses();
	bool isBotch();


private:
	vector<int> & rDiePool;
	vector<int> resultPool;
	//rolls >= to this count as successes
	int successThreshold;
	//rolls <= to this count as fails
	int failThreshold;
};

