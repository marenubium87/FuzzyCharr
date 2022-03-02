#include <algorithm>
#include <stdio.h>
#include <vector>
using std::vector;

vector<vector<int>> combinationSum(vector<int>& candidates, int target);
bool isSorted(vector<int>& v);
int vectorSum(vector<int>& v);
void insertVal(vector<int>& candidates, int n, int target,
	vector<int>& solnVector, vector<vector<int>>& allSolns);

int main() {
	vector<int> candidates{ 2, 3, 5 };
	
	combinationSum(candidates, 8);

}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	//ensure candidates is sorted
	if (!isSorted(candidates)) {
		sort(candidates.begin(), candidates.end());
	}

	//the potential solution that will be inserted into the set of all solutions
	vector<int> nextSoln;

	vector<vector<int>> allSolns;

	insertVal(candidates, candidates.size() - 1, target, nextSoln, allSolns);

	return allSolns;
}

//returns true if vector v is sorted
bool isSorted(vector<int>& v) {
	for (int i = 0; i < v.size() - 1; i++) {
		if (v[i] > v[i + 1]) {
			return false;
		}
	}
	return true;
}

//sums up all elements of vector v and returns sum
int vectorSum(vector<int>& v) {
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
	}
	return sum;
}

//inserts candidates[n] into solnVector and performs checking operations
void insertVal(vector<int>& candidates, int n, int target,
	vector<int>& solnVector, vector<vector<int>>& allSolns) {


	solnVector.push_back(candidates[n]);
	int s = vectorSum(solnVector);

	if (s < target) {
		//add another of the same element and try again
		insertVal(candidates, n, target, solnVector, allSolns);
	}
	else {
		if (s == target) {
			//save our results
			allSolns.push_back(solnVector);
		}
	}

	//remove the element and try an element one smaller
	solnVector.pop_back();

	if (n - 1 >= 0) {
		insertVal(candidates, n - 1, target, solnVector, allSolns);
	}

}