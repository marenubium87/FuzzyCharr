void updateCats(vector<int> islandCounts) {

	//counts cats
	int numCats = 0;
	int numberEmpty = 0;
	for (int island : islandCounts) {
		if (island == 0) {
			numberEmpty++;
		}
		else {
			numCats += island;
		}
	}

	//migrate cats
	if (numCats < 3 * islandCounts.size()) {

		for (int & island : islandCounts) {
			island += 2;
		}

		numberEmpty = 0;
	}

	//redistribute cats
	double propEmptyIslands = numberEmpty / islandCounts.size();
	if (propEmptyIslands > 0.75) {

		int numDist = numCats / islandCounts.size();
		int numRemainder = numCats % islandCounts.size();

		for (int i = 0; i < islandCounts.size(); i++) {
			islandCounts[i] = numDist;
			if (numRemainder > 0) {
				islandCounts[i]++;
				numRemainder--;
			}
		}
	}
}