#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::getline;
using std::stringstream;
using std::setw;
using std::setprecision;

//initializes simulation mode names
enum SimMode { noMode, netSuccessesNoBotch };

void displayMainMenu();

void printDiePool(vector<int> & diePool);

void adjustDiePool(vector<int> & diePool);

void displayModesSelection(void);

void setSimMode(int & simMode);

class RollAnalysis {
public:
	RollAnalysis(vector<int> & diePool);
	~RollAnalysis() {}

	void roll();

	int getSuccesses();
	int getFails();
	int getNetSuccesses();
	bool isBotch();

	int getSuccessThreshold(void) { return successThreshold; }
	int getFailThreshold(void) { return failThreshold; }
	void setSuccessThreshold(int const val) { successThreshold = val; }
	void setFailThreshold(int const val) { failThreshold = val; }

private:
	vector<int> & rDiePool;
	vector<int> resultPool;
	//rolls >= to this count as successes
	int successThreshold;
	//rolls <= to this count as fails
	int failThreshold;
};

class SimulationRun {

public:
	SimulationRun(vector<int> & diePool);
	
	virtual void displayConfig(void) = 0;
	virtual void displayConfigSettings(void) = 0;
	virtual void setConfig(void) = 0;

	virtual void commenceSimulation(void) = 0;

protected:
	vector<int> & rDiePool;
	vector<vector<int>> cumResults;
	int numTrials;
	RollAnalysis * analysis;
private:

};

SimulationRun * makeNewSim(int simMode, vector<int> & diePool);

class SimNumSuccesses : public SimulationRun {
public:
	SimNumSuccesses(vector<int> & diePool);

	~SimNumSuccesses() { }
	virtual void displayConfig(void);
	virtual void displayConfigSettings(void);
	virtual void setConfig(void);

	virtual void commenceSimulation(void);

protected:

private:
	
};

