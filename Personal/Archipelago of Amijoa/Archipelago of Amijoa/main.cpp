#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;
using std::endl;
using std::sort;
using std::reverse;

class Island {

public:
	Island(int newKitties) {
		numKitties = newKitties;
	}
	int numKitties;

private:
	
};

class Archipelago {
public:
	Archipelago(vector<int> counts) {
		totalKitties = 0;

		for (int element : counts) {
			islands.push_back(Island(element));
			totalKitties += element;
		}
	}

	//returns # of days to satisfy all entries in clients
	int deliverCats(vector<int> & clients);

private:
	vector<Island> islands;
	int totalKitties;


	//returns true if island pops modified
	bool migrateKitties();
	bool redistributeKitties();
	void sortIslandsDesc();

	//returns true if i1 contains MOAR kittehs than i2, false else
	//bool compareIslandsDesc(Island & i1, Island & i2);
};

bool Archipelago::migrateKitties(void) {
	if (totalKitties < 3 * islands.size()) {

		for (Island & island : islands) {
			island.numKitties += 2;
		}

		totalKitties = totalKitties + 2 * islands.size();
		return true;
	}
	return false;
}

bool Archipelago::redistributeKitties(void) {
	int numberEmpty = 0;
	for (Island island : islands) {
		if (island.numKitties == 0) {
			numberEmpty++;
		}
	}
	double propEmptyIslands = (double) numberEmpty / islands.size();

	if (propEmptyIslands >= 0.75) {

		int numDist = totalKitties / islands.size();
		int numRemainder = totalKitties % islands.size();

		for (int i = 0; i < islands.size(); i++) {
			islands[i].numKitties = numDist;
			if (numRemainder > 0) {
				islands[i].numKitties++;
				numRemainder--;
			}
		}
		return true;
	}
	return false;
}

bool operator>(Island & lhs, Island & rhs) {
	return lhs.numKitties > rhs.numKitties;
}

bool operator<(Island & lhs, Island & rhs) {
	return lhs.numKitties < rhs.numKitties;
}

//bool Archipelago::compareIslandsDesc(Island & i1, Island & i2) {
//	return i1 > i2;
//}

//sorts islands from moar kittehs to less kittehs
void Archipelago::sortIslandsDesc(void) {
	sort(islands.begin(), islands.end());
	reverse(islands.begin(), islands.end());
}

int Archipelago::deliverCats(vector<int> & clients) {
	
	int numDays = 0;
	sort(clients.begin(), clients.end());
	reverse(clients.begin(), clients.end());
	bool redistOccurred = true;

	while (!clients.empty()) {
		if (redistOccurred) {
			sortIslandsDesc();
		}
		bool singleIslandFound = false;

		//find client
		int i = 0;
		for (; i < clients.size(); i++) {
			if (clients[i] <= islands[0].numKitties) {
				singleIslandFound = true;
				break;
			}
		}

		//deliver cats
		if (singleIslandFound) {
			islands[0].numKitties -= clients[i];
			clients.erase(clients.begin() + i);
			numDays++;
		}
		//go to multiple islands
		else {
			
			int i = 0;
			while (clients[0] > 0) {

				if (redistOccurred) {
					sortIslandsDesc();
					i = 0;
				}

				if (clients[0] > islands[i].numKitties && 
							islands[i].numKitties != 0) {
					clients[0] -= islands[i].numKitties;
					islands[i].numKitties = 0;
				}
				else if(clients[0] <= islands[i].numKitties) {
					islands[i].numKitties -= clients[0];
					clients[0] = 0;
				}
				else {
					numDays--;
				}
				i++;
				numDays++;

				redistOccurred = migrateKitties() || redistributeKitties();
			}
			clients.erase(clients.begin());
		}

		redistOccurred = migrateKitties() || redistributeKitties();
	}
	
	return numDays;

}

int main() {

	vector<int> archipelago3{ 0, 2, 8, 5 };
	vector<int> clients{ 17, 16, 14, 13 };


	Archipelago amijoa(archipelago3);
	amijoa.deliverCats(clients);
	
	



	return 0;
}

