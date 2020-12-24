//source file for CS122 PA2

#include "sastruga.h"

//prints main Sastruga menu
void printMenu(void) {
	printf("Sastruga - A Text-based Game Organization Simulator\n");
	printf("   (c) 2021 by the Nefarious Kitty Corporation\n");
	printf("   (All rights reserved and protected by ");
	printf("shotgun-wielding kitties.)\n\n");
	printf("Select an option from the following:\n\n");
	printf("  1.  Read the new ancient scriptures\n");
	printf("  2.  Preserve the sacred teachings\n");
	printf("  3.  Unveil the forgotten records\n");
	printf("  4.  Collect a new artifact\n");
	printf("  5.  Banish the exile\n");
	printf("  6.  Rewrite the stone tablets\n");
	printf("  7.  Organize the troops\n");
	printf("  8.  Decree divine judgment\n");
	printf("  9.  Embark on your next quest\n");
	printf(" 10.  Open the gates of chaos\n");
	printf(" 11.  Retire to your chambers\n");
	printf(" \n\n");
}

//displays all attributes of targetGame to the console
void displayGameContents(Game targetGame) {
	printf("~~\n");
	printf("  Title:     %s\n", targetGame.title);
	printf("  Developer: %s\n", targetGame.developer);
	printf("  Genres:    ");
	printGenreList(targetGame.pGenres);
	printf("\n");
	printf("  Playtime:  %dh %02dm\n",
		targetGame.timePlayed.hours, targetGame.timePlayed.minutes);
	printf("  Achieves:  %d\n", targetGame.numAchieves);
	printf("  Rating:    %d\n", targetGame.rating);
	printf("\n*****\n");
}

//displays all games with minimim rating >= minGameRating in 
//game list pointed to by pGameHead to the console
void printGameList(GameNode * pGameHead, int minGameRating) {
	GameNode * pCurr = pGameHead;
	printf("  ***GAME LIST");
	if (minGameRating > 0) {
		printf(" with rating at least %d", minGameRating);
	}
	printf("***\n\n");

	while (pCurr != NULL) {
		if (pCurr->targetGame.rating >= minGameRating) {
			displayGameContents(pCurr->targetGame);
		}
		pCurr = pCurr->pNext;
	}
	printf("\n  ***END OF LIST***\n\n");
}

//wrapper function to do menu option 3 from the main menu
void unveilForgottenRecordsWrapper(GameNode * pGameHead) {
	int choice = 0;
	char tempCharr = '\0';

	printf("Hail, traveler.  Select from the following:\n\n");
	printf("1.  Unveil all of the forgotten records\n");
	printf("2.  Unveil all forgotten records with a rating of 6\n\n");

	scanf("%d%c", &choice, &tempCharr);
	system("cls");
	if (choice == 2) {
		printGameList(pGameHead, 6);
	}
	else if (choice == 1) {
		printGameList(pGameHead, 0);
	}
	else {
		printf("Kitty refuses to work if you cannot follow basic directions.\n\n");
	}
}

//allocates space on the heap for a new GameNode and initializes
//with information found in targetGame
//returns address of GameNode on the heap
//required for insertGameAtFront
GameNode * makeGame(Game targetGame) {
	GameNode * pMem = (GameNode *)malloc(sizeof(GameNode));
	pMem->pNext = NULL;
	pMem->pPrev = NULL;
	strcpy(pMem->targetGame.title, targetGame.title);
	strcpy(pMem->targetGame.developer, targetGame.developer);
	pMem->targetGame.pGenres = targetGame.pGenres;
	pMem->targetGame.timePlayed = targetGame.timePlayed;
	pMem->targetGame.numAchieves = targetGame.numAchieves;
	pMem->targetGame.rating = targetGame.rating;
	return pMem;
}

//inserts GameNode containing targetGame to front of game list
//remember to call *location* of pGameHead when calling
void insertGameAtFront(GameNode ** pGameList, Game targetGame) {
	GameNode * pMem = makeGame(targetGame);
	pMem->pNext = *pGameList;
	//need to check if list is not empty... if list is empty, 
	//not necessary (and in fact harmful) to set previous head node's pPrev
	if (*pGameList != NULL) {
		(*pGameList)->pPrev = pMem;
	}
	*pGameList = pMem;
}

//loads game library from infile via insert at front to list
//assumes infile already opened for read
void loadGameLibrary(GameNode ** pGameList, FILE * infile) {
	Game tempGame = { "", "", NULL, { 0, 0 }, 0, 0 };
	char nextLine[1701] = "";
	while (fgets(nextLine, 1700, infile) != NULL) {
		
		//read next game from file

		//set title and dev
		strcpy(tempGame.title, strtok(nextLine, ","));
		strcpy(tempGame.developer, strtok(NULL, ","));
		
		//tokenize genres list
		char * genresList = strtok(NULL, ",");
		//convert playtime, achieves, rating
		tempGame.timePlayed.hours = atoi(strtok(NULL, ":"));
		tempGame.timePlayed.minutes = atoi(strtok(NULL, ","));
		tempGame.numAchieves = atoi(strtok(NULL, ","));
		tempGame.rating = atoi(strtok(NULL, ","));

		//set up genres list
		GenreNode * pTempGenreList = NULL;
		char * tempGenre = NULL;
		tempGenre = strtok(genresList, "|");
		while (tempGenre != NULL) {
			insertGenreAtFront(&pTempGenreList, tempGenre);
			tempGenre = strtok(NULL, "|");
		}
		tempGame.pGenres = pTempGenreList;

		//insert next game into front of list
		insertGameAtFront(pGameList, tempGame);
	}
}

//stores all games in list pointed to by pGameHead to the outfile in csv format
void preserveSacredTeachings(GameNode * pGameHead, FILE * outfile) {
	GameNode * pGameCurr = pGameHead;
	while (pGameCurr != NULL) {
		//write stuff to outfile
		fprintf(outfile, "%s,", pGameCurr->targetGame.title);
		fprintf(outfile, "%s,", pGameCurr->targetGame.developer);
		printGenreListFile(pGameCurr->targetGame.pGenres, outfile);
		fprintf(outfile, "%d:%02d,", pGameCurr->targetGame.timePlayed.hours,
			pGameCurr->targetGame.timePlayed.minutes);
		fprintf(outfile, "%d,", pGameCurr->targetGame.numAchieves);
		fprintf(outfile, "%d", pGameCurr->targetGame.rating);

		pGameCurr = pGameCurr->pNext;

		if (pGameCurr != NULL) {
			fprintf(outfile, "\n");
		}
	}
}

//aux function for rewriteStoneTablets (modifying game)
//search for and lists all games corresponding to a particular developer
//stores the search list into gameResultsArray and also displays to console
void searchDeveloper(GameNode * pGameHead, GameNode * gameResultsArray[]) {
	char userSearchInput[70] = "";
	system("cls");
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	printf("Enter the game's developer:  ");
	fgets(userSearchInput, 69, stdin);
	//prune newline character
	userSearchInput[strlen(userSearchInput) - 1] = '\0';

	//create array storing pointers to nodes that correspond to search parameters
	
	//search through list
	GameNode * pGameCurr = pGameHead;
	int i = 0;
	while (pGameCurr != NULL) {
		
		//save all matches to game results array
		if (strcmp(pGameCurr->targetGame.developer, userSearchInput) == 0) {
			gameResultsArray[i] = pGameCurr;
			i++;
		}
		pGameCurr = pGameCurr->pNext;
	}
	if (i == 0) {
		printf("\nNo matches found.\n\n");
	}
	else if (i == 1) {
		printf("\n\nMatch found:\n\n");
		printf("Entry 1  ");
		displayGameContents(gameResultsArray[0]->targetGame);
	}
	else {
		//display contents of game results array
		printf("\n\nMatches found:\n\n");
		int j = 0;
		while (gameResultsArray[j] != NULL) {
			printf("Entry %d  ", j + 1);
			displayGameContents(gameResultsArray[j]->targetGame);
			j++;
		}
	}
}

//prompts user for new rating clamped to [1,6] for targetGame
//and modifies rating accordingly
//also aux function for modifyGame
void decreeDivineJudgment(Game * targetGame, int newRating) {
	if (newRating < 1 || newRating > 6) {
		printf("\nInvalid entry.  Check your input.\n");
	}
	else {
		targetGame->rating = newRating;
	}
}

//aux function for rewriteStoneTablets
//does what it says on the tin
void modifyGame(Game * targetGame) {
	char tempCharr = '\0';

	int modifyChoice = 0;
	do {
		system("cls");
		printf("You have selected:\n\n");
		displayGameContents(*targetGame);

		printf("\nMake a choice from the following options:\n\n");
		printf("1.  Modify title\n");
		printf("2.  Modify developer\n");
		printf("3.  Modify playtime\n");
		printf("4.  Modify, add or remove genres\n");
		printf("5.  Modify achievements\n");
		printf("6.  Modify rating\n");
		printf("7.  Exit\n\n");

		scanf("%d%c", &modifyChoice, &tempCharr);

		char tempString[100] = "";
		int num1 = 0, num2 = 0;

		switch (modifyChoice) {
		case 1:
			printf("Type new title:  ");
			fgets(tempString, 99, stdin);
			//prune newline char
			tempString[strlen(tempString) - 1] = '\0';
			strcpy(targetGame->title, tempString);
			printf("\n\nTitle updated.\n\n");
			break;
		case 2:
			printf("Type new developer:  ");
			fgets(tempString, 99, stdin);
			//prune newline char
			tempString[strlen(tempString) - 1] = '\0';
			strcpy(targetGame->developer, tempString);
			printf("\n\nDeveloper updated.\n\n");
			break;
		case 3:
			printf("Type in the playtime in the format(h m)\n");
			printf("(Leave a space between the hours and minutes.)  ");
			scanf("%d%d", &num1, &num2);
			if (num1 < 0 || num2 < 0 || num2 > 59) {
				printf("\nInvalid entry.  Check your input.\n\n");
			}
			else {
				targetGame->timePlayed.hours = num1;
				targetGame->timePlayed.minutes = num2;
				printf("\nPlaytime updated.\n\n");
			}
			break;
		case 4:
			do {
				system("cls");
				displayGameContents(*targetGame);
				printf("Type in an already listed genre to delete from list,\n");
				printf("type in a new genre to add to list, or\n");
				printf("type 'exit' to exit.\n\n");
				fgets(tempString, 99, stdin);
				//prune newline char
				tempString[strlen(tempString) - 1] = '\0';
				if (strcmp("exit", tempString) != 0) {
					modifyGenreList(&(targetGame->pGenres), tempString);
					system("pause");
				}
			} while (strcmp("exit", tempString) != 0); 
			break;
		case 5:
			printf("Type in the number of achievements:  ");
			scanf("%d", &num1);
			if (num1 < 0) {
				printf("\nInvalid entry.  Check your input.\n\n");
			}
			else {
				targetGame->numAchieves = num1;
				printf("Number of achievements updated.\n\n");
			}
			break;
		case 6:
			printf("Type in the new rating:  ");
			scanf("%d", &num1);
			decreeDivineJudgment(targetGame, num1);
			break;
		case 7:
			printf("\nOkay, bai.\n\n");
			break;
		default:
			printf("Enter a valid option.\n\n");
		}
		if (modifyChoice != 7) {
			system("pause");
		}
	} while (modifyChoice != 7);
}

//modifies a field in a target game from game list based on user input
void rewriteStoneTablets(GameNode * pGameHead) {
	
	//array to save results from developer search
	GameNode * gameResultsArray[12] = { NULL };
	
	//populates gameResultsArray with games based on developer search
	searchDeveloper(pGameHead, gameResultsArray);

	//if there are no matches found, returns to menu
	if (gameResultsArray[0] == NULL) {
		return;
	}
	//if second entry is null that means there was only one entry found
	else if (gameResultsArray[1] == NULL) {
		modifyGame(&(gameResultsArray[0]->targetGame));
	}
	else {
		printf("\n\nType in the entry number of the game to modify,\n");
		printf("or 0 to exit.  ");
		int gameChoice = 0;
		char tempCharr = '\0';
		scanf("%d%c", &gameChoice, &tempCharr);
		if (gameChoice == 0) {
			return;
		}
		else {
			modifyGame(&(gameResultsArray[gameChoice - 1]->targetGame));
		}
	}
}

//aux function for embarkOnQuest
//simulates adding of playtime to the currently played game
void addPlaytime(Game * targetGame) {
	//simulates playtime to add to current game
	int addHours = floor(0.5 * (rand() % 6 + rand() % 6));
	int addMinutes = rand() % 60;
	printf("You played %s for %d hours %02d minutes.\n",
		targetGame->title, addHours, addMinutes);
	printf("This time is being added to your total playtime.\n");

	//adds the playtime, being careful about carrying
	int carry = 0;
	targetGame->timePlayed.minutes += addMinutes;
	if (targetGame->timePlayed.minutes >= 60) {
		targetGame->timePlayed.minutes -= 60;
		carry++;
	}
	targetGame->timePlayed.hours =
		targetGame->timePlayed.hours + addHours + carry;

	printf("Your total playtime for %s is now %d hours %02d minutes.\n\n",
		targetGame->title, 
		targetGame->timePlayed.hours, 
		targetGame->timePlayed.minutes);
}

//function to "play" games in list order starting from
//user-selected game until end of list
void embarkOnQuest(GameNode * pGameHead) {
	system("cls");

	int choice = 0;
	char tempCharr = '\0';
	GameNode * pCurr = NULL;

	do {
		printf("Let's embark on your quest, fair traveler!\n\n");
		printf("Start playing from beginning of list,");
		printf(" or from a specific title ? \n");
		printf("  1.  Beginning of List\n");
		printf("  2.  Search for specific Title\n");
		scanf("%d%c", &choice, &tempCharr);
		if (choice < 1 || choice > 2) {
			printf("\nInvalid selection, try again\n");
			system("pause");
			system("cls");
		}
	} while (choice < 1 || choice > 2);

	//sets pCurr depending on user choice from previous prompt
	if (choice == 1) {
		pCurr = pGameHead;
		if (pCurr == NULL) {
			printf("You have no games to play.  You should add some!\n\n");
			return;
		}
	}
	else if (choice == 2) {
		
		//lets user find game by publisher and start from there
		int gameChoice = 0;
		GameNode * gameResultsArray[12] = { NULL };
		while (gameResultsArray[0] == NULL) {
			
			//populates gameResultsArray with games based on developer search
			searchDeveloper(pGameHead, gameResultsArray);

			if (gameResultsArray[0] != NULL) {
				printf("\nType in the entry number of the game to play,\n");
				printf("or 0 to decide to go outside ");
				printf("and get some fresh air instead.  ");
				int gameChoice = 0;
				char tempCharr = '\0';
				scanf("%d%c", &gameChoice, &tempCharr);
				if (gameChoice == 0) {
					return;
				}
				else {
					pCurr = gameResultsArray[gameChoice - 1];
				}
			}
			system("pause");
		}
	}

	//so now pCurr points to the first game that the user wants to play
	do {
		system("cls");
		printf("You are currently playing:\n\n");
		displayGameContents(pCurr->targetGame);

		//simulates game playtime
		addPlaytime(&(pCurr->targetGame));

		printf("\nMake a selection:\n\n");
		printf("1.  Play next game\n");
		printf("2.  Exit\n");
		scanf("%d%c", &choice, &tempCharr);
		if (choice == 1) {
			pCurr = pCurr->pNext;
		}
	} while (pCurr != NULL && choice == 1);

	system("cls");
	if (pCurr == NULL) {
		printf("You've reached the end of your game library.\n");
	}
	else {
		printf("I agree, that's enough gaming for one session.\n");
	}
	printf("So go outside and get some fresh air!\n\n");
}

//wrapper to ask user for identity of a new game
//and inserts it into the front of the game list
//remember to call *location* of pGameHead when calling
void collectNewArtifact(GameNode ** pGameList) {

	printf("Oooh, a new artifact... shiny!!");

	//set up target game based on user input
	Game targetGame = { "", "", NULL, { 0, 0 }, 0, 0 };
	char tempString[100] = "";
	int tempInt = 0;
	char tempCharr = '\0';

	//eats up the newline from making choice from main menu
	scanf("%c", &tempCharr);

	//title
	printf("\n\nType the title of the game:  ");
	fgets(tempString, 99, stdin);
	//prune newline char
	tempString[strlen(tempString) - 1] = '\0';
	strcpy(targetGame.title, tempString);

	//developer
	printf("\nType the game's developer:  ");
	fgets(tempString, 99, stdin);
	//prune newline char
	tempString[strlen(tempString) - 1] = '\0';
	strcpy(targetGame.developer, tempString);

	//assume since this is a new game, player has no playtime
	//if this is inaccurate, they can always modify the entry later

	//achievements
	do {
		printf("\nType in the number of achievements:  ");
		scanf("%d%c", &tempInt, &tempCharr);
		if (tempInt < 0) {
			printf("\nInvalid entry.  Check your input.");
		}
		else {
			targetGame.numAchieves = tempInt;
			printf("\nNumber of achievements updated.");
		}
	} while (tempInt < 0);

	//rating
	do {
		printf("\nType in the game's rating (1-6),\n");
		printf("or enter 0 to skip for now.  ");
		scanf("%d%c", &tempInt, &tempCharr);
		if (tempInt == 0) {
			break;
		}
		else {
			decreeDivineJudgment(&targetGame, tempInt);
		}
	} while (tempInt < 0 || tempInt > 6);

	//genres
	do {
		system("cls");
		displayGameContents(targetGame);
		printf("Type in a new genre to add to list,\n");
		printf("type in an already listed genre to delete from list, or\n");
		printf("type 'exit' to exit.\n\n");
		fgets(tempString, 99, stdin);
		//prune newline char
		tempString[strlen(tempString) - 1] = '\0';
		if (strcmp("exit", tempString) != 0) {
			modifyGenreList(&(targetGame.pGenres), tempString);
			system("pause");
		}
	} while (strcmp("exit", tempString) != 0);

	//targetGame is all set up to be inserted into list
	insertGameAtFront(pGameList, targetGame);
	printf("\nSuccess!  Your new artifact has been catalogued and saved.\n\n");
}

//aux function for banishing the exile
//searches pGameHead and returns the GameNode * containing
//targetGameString, or returns NULL if targetGameString not found
GameNode * searchGameList(GameNode * pGameHead, char * targetGameString) {
	GameNode * pCurr = pGameHead;
	while (pCurr != NULL) {
		if (strcmp(pCurr->targetGame.title, targetGameString) == 0) {
			return pCurr;
		}
		pCurr = pCurr->pNext;
	}
	//if we get to here we've traversed the whole list without finding a match
	return NULL;
}

//aux function for banishing the exile, handles search and removing
//target game from list pointed to by pGameList
//dependencies:  searchGameList
void removeSelectedGame(GameNode ** pGameList, char * targetGameString) {
	//search for game in list
	GameNode * pCurr = searchGameList(*pGameList, targetGameString);

	//handles invalid entry and empty list conditions
	if (pCurr == NULL) {
		printf("\nI cannot locate the one you speak of\n");
		printf("in my records.  My sincere apologies.\n\n");
		return;
	}

	//will need these to weave new pointer connections
	GameNode * pN = NULL;
	GameNode * pP = NULL;

	//setting links
	//are we deleting the first entry?
	if (pCurr->pPrev == NULL) {
		//are we deleting the ONLY entry?
		if (pCurr->pNext == NULL) {
			*pGameList = NULL;
		}
		else {
			pN = pCurr->pNext;
			*pGameList = pN;
			pN->pPrev = NULL;
		}
	}
	else {
		//are we deleting the last entry?
		if (pCurr->pNext == NULL) {
			pP = pCurr->pPrev;
			pP->pNext = NULL;
		}
		else {
			pP = pCurr->pPrev;
			pN = pCurr->pNext;
			pP->pNext = pN;
			pN->pPrev = pP;
		}
	}

	//clear out pCurr
	free(pCurr);
	printf("We have dealt with the exile, milord.\n");
}

//wrapper to prompt user to remove a game from the list
//remember to call *location* of pGameHead when calling
void banishExile(GameNode ** pGameList) {
	
	//eats up the newline char from when the user selects this choice
	char tempCharr = '\0';
	scanf("%c", &tempCharr);

	char userInput[100] = "";
	printf("Yes, yes... simply speak the name of that which \n");
	printf("you wish to banish, and it shall be done, milord...\n\n");
	fgets(userInput, 99, stdin);
	//prune newline char
	userInput[strlen(userInput) - 1] = '\0';

	removeSelectedGame(pGameList, userInput);
	printf("\n");
}

//aux function for organizing the troops, e.g. sorting
//swaps the pointers such that the positions of
//pTarget and the node immediately following it are swapped
//warning:  pass in the *location* of pGameList!
//warning:  do not call this function if either
//pTarget or pTarget->pNext are NULL
void swapElements(GameNode ** pGameList, GameNode * pTarget) {

	//schematically, in this function
	//pP -> p1 -> p2 -> pN
	//goal is to swap p1 and p2

	GameNode * pP = pTarget->pPrev;
	GameNode * p1 = pTarget;
	GameNode * p2 = p1->pNext;
	GameNode * pN = p2->pNext;
	
	//is pTarget the first element?
	if (pP == NULL) {
		*pGameList = p2;
	}
	else {
		pP->pNext = p2;
	}
	//main swap bits
	p1->pNext = p2->pNext;
	p2->pPrev = p1->pPrev;
	p2->pNext = p1;
	p1->pPrev = p2;

	//was p2 originally the last element?  if not, need a connection
	if (pN != NULL) {
		pN->pPrev = p1;
	}
}

//sorts pGameList by title using ascii sorting
//remember to pass in *location* of pGameList when calling
void organizingTroops(GameNode ** pGameList) {
	//is the list empty?

	printf("As you wish... I shall organize the troops.\n\n");

	GameNode * pCurr = *pGameList;
	if (pCurr == NULL) {
		return;
	}
	//does the list only have one element?
	else if (pCurr->pNext == NULL) {
		return;
	}
	else {
		//need to know how many elements are in the list
		int numUnsorted = 0;
		while (pCurr != NULL) {
			numUnsorted++;
			pCurr = pCurr->pNext;
		}

		//index of last element, if there were such a thing, would be
		//numUnsorted - 1, but we must guarantee there is always an
		//element to the right of target element for swaps, hence - 2
		int indexLastUnsorted = numUnsorted - 2;

		for (int i = indexLastUnsorted; i >= 0; i--) {
			pCurr = *pGameList;

			for (int j = 0; j <= i; j++) {
	
				if (strcmp(pCurr->targetGame.title,
					pCurr->pNext->targetGame.title) > 0) {
					swapElements(pGameList, pCurr);
				}
				else {
					//if we swapped elements above, that means
					//pCurr has already in essence incremented
					//and thus does not need to be incremented again
					pCurr = pCurr->pNext;
				}
			}
		}
	}

	printf("I have organized the troops, milord.\n\n");
}

//randomizes the order of element values in target int array
//akin to shuffle feature on music player
//aux function for openGatesofChaos
void randomizeArray(int * target, int targetSize) {
	int temp = 0;
	int randIndex = 0;
	for (int i = 0; i < targetSize; i++) {
		//swap current element with random element (can be itself)
		randIndex = rand() % targetSize;
		temp = target[i];
		target[i] = target[randIndex];
		target[randIndex] = temp;
	}
}

//shuffle feature
void openGatesOfChaos(GameNode * pGameHead) {
	//figure out number of games
	GameNode * pCurr = pGameHead;
	int numGames = 0;
	while (pCurr != NULL) {
		numGames++;
		pCurr = pCurr->pNext;
	}
	//returns on empty list and does not continue
	if (numGames == 0) {
		printf("You have no games to play.  You should add some!\n\n");
		return;
	}

	//allocate array with elements equal to number of games
	int * arrGameOrder = (int *)malloc(numGames * sizeof(int));
	//populate array
	for (int i = 0; i < numGames; i++) {
		arrGameOrder[i] = i;
	}

	//randomize array order
	randomizeArray(arrGameOrder, numGames);

	//find first game
	pCurr = pGameHead;
	for (int i = 0; i < arrGameOrder[0]; i++) {
		pCurr = pCurr->pNext;
	}

	//so now pCurr points to the first game that the user wants to play
	int choice = 0;
	char tempCharr = '\0';
	int gamesPlayed = 0;
	int offset = 0;
	do {
		system("cls");
		printf("You are currently playing:\n\n");
		displayGameContents(pCurr->targetGame);

		//simulates game playtime
		addPlaytime(&(pCurr->targetGame));
		gamesPlayed++;

		printf("\nMake a selection:\n\n");
		printf("1.  Play next game\n");
		printf("2.  Exit\n");
		scanf("%d%c", &choice, &tempCharr);
		if (choice == 1 && gamesPlayed <= numGames) {
			//write shuffle code here
		}
	} while (gamesPlayed <= numGames && choice == 1);

	system("cls");
	if (pCurr == NULL) {
		printf("You've reached the end of your game library.\n");
	}
	else {
		printf("I agree, that's enough gaming for one session.\n");
	}
	printf("So go outside and get some fresh air!\n\n");
}