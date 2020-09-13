//source file for poker

#include "pokeypoke.h"

/* shuffle cards in deck */
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int col = 0;    /*column number */
	int card = 0;   /* card counter */

					/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			col = rand() % 13;
		} while (wDeck[row][col] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][col] = card;
	}
}

//prints out target player's hand to the console
//if hide = 0, hand will be printed; if 1, hand will be obfuscated
//playerID prints "your hand" for 1, "my hand" for 2
void printHand(Card targetHand[], 
	const char *wFace[], const char *wSuit[], int hide, int playerID) {

	if (playerID == 1) {
		printf("****Your hand****\n\n");
	}
	else {
		printf("****My hand****\n\n");
	}

	printf("Card ID\t\tCard\t\tDiscard?\n\n");
	//loop through cards in hand
	for (int i = 0; i < 5; i++) {
		printf("%d\t", targetHand[i].cardOrder);
		//obfuscates dealer's hand, prints player hand as normal
		if (hide == 0) {
			printf("%5s of %-8s\t", wFace[targetHand[i].cardFace],
				wSuit[targetHand[i].cardSuit]);
		}
		else {
			printf("%5s of %-8s\t", "Sqrt(2)", "Dildos");
		}
		if (targetHand[i].cardKeep == 0) {
			printf("   *");
		}
		printf("\n");
	}
	printf("\n");
}

//function to mark all cards as to be discarded...
//helpful for between rounds of poker
void discardAll(Card targetHand[]) {
	for (int i = 0; i < 5; i++) {
		targetHand[i].cardKeep = 0;
	}
}

//deals numCardsToDeal from deck to targetHand, keeping track
//of card position (as output param) so that future deals can
//start from the correct location.
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[],
	Card targetHand[], int numCardsToDeal, int * cardPosition) {
	int row = 0;    /* row number */
	int col = 0; /*column number */

	printf("\nDealt %d cards.\n\n", numCardsToDeal);
	//deals numCardsToDeal cards starting at cardPosition
	//mind the potential off by 1 error... e.g. dealing 3 cards
	//starting from position 5 deals out 5, 6, 7

	int endIndex = *cardPosition + numCardsToDeal;
	for (; *cardPosition < endIndex; (*cardPosition)++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (col = 0; col <= 12; col++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][col] == *cardPosition)
				{
					//depreciated, see "printHand" function instead
					/*printf("%5s of %-8s%c", wFace[col], wSuit[row],
						*cardPosition % 2 == 0 ? '\n' : '\t');*/
					//puts card into targetHand, which is a size 5
					//array consisting of Card
					placeNextCard(cardPosition, targetHand, row, col);
				}
			}
		}
	}
}

//auxiliary function for deal
//places next card from deck into next available position (keep == 0)
//in targetHand array, by assigning the card position, the rowID (suit)
//and the columnID (face), and also flips cardKeep to 1
void placeNextCard(int * cardPosition, Card targetHand[], 
	int row, int col) {

	//finds next location in targetHand array that we can insert a card
	int i = 0;
	while (targetHand[i].cardKeep != 0) {
		i++;
	}
	targetHand[i].cardOrder = *cardPosition;
	targetHand[i].cardSuit = row;
	targetHand[i].cardFace = col;
	//cards are kept by default, not discarded
	targetHand[i].cardKeep = 1;
}

//returns the number of the highest face multiplicity in targetHand
//e.g. will return 1 if hand contains no pairs
//will return 2 if a pair is found
//will return 3 if 3 of a kind is found, 4 if 4 of a kind is found
//if this function return 5, someone cheated or code is borked
//takes care of hands:  one pair, three of a kind, four of a kind
int highestFaceMultiplicity(Card targetHand[]) {
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//loops through freqArray to find highest multiple
	int highestMult = 0;
	for (int i = 0; i < 13; i++) {
		if (frequencyArray[i] > highestMult) {
			highestMult = frequencyArray[i];
		}
	}
	return highestMult;
}

//returns the number of the highest suit multiplicity in targetHand
//e.g. if hand is S S H C D then fcn will return 2
//takes care of flushes
int highestSuitMultiplicity(Card targetHand[]) {
	//since we're counting suits here, freqArray now is size 4
	int frequencyArray[4] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardSuit]++;
	}
	int highestMult = 0;
	for (int i = 0; i < 4; i++) {
		if (frequencyArray[i] > highestMult) {
			highestMult = frequencyArray[i];
		}
	}
	return highestMult;
}

//returns the highest contiguous sequence in targetHand
//e.g. if hand is 3 4 7 8 9, will return 3 (for 7 8 9)
//note that 2 is low and Ace is high, no wrap-around sequences
int highestContiguousSequence(Card targetHand[]) {
	//set up frequency array counting face values
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	int highestContiguous = 0;
	int currentContiguous = 0;
	//basic idea - go through array, whenever we hit a 1 (or more),
	//start a counter, and reset the counter upon hitting a 0.
	//upon hitting a zero, if counter's value is higher than
	//the saved highest value, replace.
	for (int i = 0; i < 13; i++) {
		if (frequencyArray[i] > 0) {
			currentContiguous++;
		}
		else {
			currentContiguous = 0;
		}

		if (currentContiguous > highestContiguous) {
			highestContiguous = currentContiguous;
		}
	}
	return highestContiguous;
}

//returns 1 if targetHand contains two pair, 0 else
//takes care of two pair, obviously
int containsTwoPair(Card targetHand[]) {
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//count number of pairs found
	int numOfPairs = 0;
	for (int i = 0; i < 13; i++) {
		if (frequencyArray[i] > 1) {
			numOfPairs++;
		}
	}
	//returns based on number of pairs found
	if (numOfPairs > 1) {
		return 1;
	}
	else {
		return 0;
	}
}

//returns 1 if targetHand contains a full house, 0 else
//takes care of full house situation, obviously
int containsFullHouse(Card targetHand[]) {
	//we need a three of a kind, else hand does not contain full house
	if (highestFaceMultiplicity(targetHand) == 3) {
		
		//establish frequency array
		int frequencyArray[13] = { 0 };
		for (int i = 0; i < 5; i++) {
			frequencyArray[targetHand[i].cardFace]++;
		}
		//we already know a three of a kind exists, does hand also
		//contain exactly a pair?
		for (int i = 0; i < 13; i++) {
			if (frequencyArray[i] == 2) {
				return 1;
			}
		}
	}
	//no full house if code execution makes it to here
	return 0;
}

//evaluates targetHand and returns the following values
//0:  nothing (high card)	1:  one pair
//2:  two pair				3:  three of a kind
//4:  straight				5:  flush
//6:  full house			7:  four of a kind
//8:  straight flush
int evaluateHand(Card targetHand[]) {
	//straight and flush components
	if (highestContiguousSequence(targetHand) == 5 ||
		highestSuitMultiplicity(targetHand) == 5) {

		//straight flush
		if (highestContiguousSequence(targetHand) == 5 &&
			highestSuitMultiplicity(targetHand) == 5) {

			return 8;
		}
		//straight
		else if (highestContiguousSequence(targetHand) == 5) {
			return 4;
		}
		//flush
		else if (highestSuitMultiplicity(targetHand) == 5) {
			return 5;
		}
		else {
			printf("You should never see this message.  ");
			printf("Something is fucked\n\n");
		}
	}
	//four of a kind
	else if (highestFaceMultiplicity(targetHand) == 4) {
		return 7;
	}
	//full house and three of a kind branch
	else if (highestFaceMultiplicity(targetHand) == 3) {
		//does it also happen to be a full house?
		if (containsFullHouse(targetHand)) {
			return 6;
		}
		else {
			return 3;
		}
	}
	//check for two pair
	else if (containsTwoPair(targetHand)) {
		return 2;
	}
	//one pair
	else if (highestFaceMultiplicity(targetHand) == 2) {
		return 1;
	}
	//high card
	else if (highestFaceMultiplicity(targetHand) == 1) {
		return 0;
	}
	//umm.
	else {
		printf("You should never see this message.  ");
		printf("Something is fucked\n\n");
	}
}

//aux function for compareHands
//finds the column (face) value of the highest card with multiplicity mult
//ex: if mult == 1, TT862 would return 6, b/c 8 is the highest single card
//		and is in position 6 in the face array
//ex2:  if mult == 2, AQTT8 will return 8, b/c T is the highest card face
//		with multiplicity 2 and is in position 8 in the face array.
int findHighestCard(Card targetHand[], int mult) {
	//fill and populate frequencyArray
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}

	//look backwards through array and stop at first face value index
	//with value equal to mult
	for (int j = 12; j >= 0; j--) {
		if (frequencyArray[j] == mult) {
			return j;
		}
	}
}

//aux function for compareHands
//compares two hands element by element running from high card to low
//at the first discrepency, returns 1 if handA has higher value,
//returns -1 if handB has the higher value, returns 0 if both hands
//have exact same face value (since suits don't matter in poker)
int rankSimilarHands(Card HandA[], Card HandB[]) {
	//build freq arrays for both hands
	int frequencyArrayA[13] = { 0 };
	int frequencyArrayB[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArrayA[HandA[i].cardFace]++;
		frequencyArrayB[HandB[i].cardFace]++;
	}

	//run through freq arrays backwards (i.e. highest to lowest card)
	//and figure out first discrepency
	for (int i = 12; i >= 0; i--) {
		if (frequencyArrayA[i] > frequencyArrayB[i]) {
			return 1;
		}
		else if (frequencyArrayA[i] < frequencyArrayB[i]) {
			return -1;
		}
	}
	//if after all of that we haven't returned anything,
	//we are in the (super unlikely) scenario where both hands
	//have the exact same face values for each card and thus are tied
	return 0;
}

//compares handA and handB
//returns 1 if handA is better in value than handB
//returns -1 if handB is better in value than handA
//returns 0 if hands are equal in value
int compareHands(Card handA[], Card handB[]) {
	//the easy part
	if (evaluateHand(handA) > evaluateHand(handB)) {
		return 1;
	}
	else if (evaluateHand(handA) < evaluateHand(handB)) {
		return -1;
	}
	//the annoying part... if the two hands have the same rank value
	else {
		int mult = -1;
		//doesn't matter which hand we evaluate since at this point
		//the two hands are equal
		switch (evaluateHand(handA)) {

			//for straight flush, flush, straight, high card
			//we care about the highest card with multiplicity 1
		case 8:
		case 5:
		case 4:
		case 0:
			mult = 1;
			break;
			//four of a kind
		case 7:
			mult = 4;
			break;
			//full house and three of a kind, we care about highest card
			//with multiplicity 3
		case 6:
		case 3:
			mult = 3;
			break;
			//for pair and two pair, we care about highest card
			//with multiplicity 2
		case 2:
		case 1:
			mult = 2;
			break;
		default:
			printf("Lord, may this line never print.\n\n");
			break;
		}
		//so now evaluate the hands based on the mult number
		int highestA = findHighestCard(handA, mult);
		int highestB = findHighestCard(handB, mult);

		//did that resolve the tie?
		if (highestA > highestB) {
			return 1;
		}
		else if (highestA < highestB) {
			return -1;
		}
		else {
			int handValue = evaluateHand(handA);
			//if it's tied on the highest card for a
			//straight or a straight flush
			//then the conclusion is that this is indeed a tie
			if (handValue == 8 || handValue == 4) {
				return 0;
			}
			else if (handValue == 5 || handValue == 2 || 
				handValue == 1 || handValue == 0) {
				//rankSimilarHands function will take care of 
				//flush, two pair, one pair, high card cases
				return rankSimilarHands(handA, handB);
			}
			else {
				printf("Seeing this text means you dun fuc'd up\n\n");
			}
		}
	}
}

//aux function for player discards
//handles user selection of cards to discard and
//gives user feedback on which cards are currently marked for discard
//returns 1 when user is ready to continue, 0 else
int handleDiscards(Card targetHand[], const int wDeck[][13],
	const char *wFace[], const char *wSuit[]) {

	system("cls");
	printHand(targetHand, wFace, wSuit, 0, 1);
	printf("Toggle cards to discard by typing their ID\n");
	printf("to the left, or type 0 to continue:  ");
	int chosenCardID = 0;
	scanf("%d", &chosenCardID);

	if (chosenCardID == 0) {
		//user ready to continue
		return 1;
	}
	else {
		//finds and toggles the card user entered
		for (int i = 0; i < 5; i++) {
			if (targetHand[i].cardOrder == chosenCardID)
			{
				targetHand[i].cardKeep = 1 - targetHand[i].cardKeep;
			}
		}
		//assume user not ready to continue
		return 0;
	}
}

//function to handle player discards
//returns number of cards player discarded
int playerDiscard(Card targetHand[], const int wDeck[][13], 
	const char *wFace[], const char *wSuit[]) {

	printf("Would you like to discard cards? (y/n)  ");
	char tempCharr = '\0';
	scanf(" %c", &tempCharr);

	if (tempCharr == 'y') {
		do {
			//allows user to toggle cards for discard
			//until they are ready to continue
			int discardSentinel = 0;
			do {
				discardSentinel = 
					handleDiscards(targetHand, wDeck, wFace, wSuit);
			} while (discardSentinel == 0);
			//add up number of discards, warn user accordingly
			int numCardsKept = 0;
			for (int i = 0; i < 5; i++) {
				numCardsKept += targetHand[i].cardKeep;
			}
			//if all warnings get bypassed, will exit outer do loop
			tempCharr = 'y';
			if (numCardsKept == 5) {
				printf("Warning!  You haven't selected any cards ");
				printf("to discard.\nContinue anyway?  (y/n)  ");
				scanf("%c", &tempCharr);
				scanf("%c", &tempCharr);
			}
			if (numCardsKept < 2) {
				printf("Warning!  You can only discard up to ");
				printf("three cards.\n  Try again.\n\n");
				system("pause");
				tempCharr = 'n';
			}
		//if there are still issues, dumps user back into
		//card discard dialogue
		} while (tempCharr != 'y');
		//start with 5 and then minus 1 for every card kept
		int numDiscarded = 5;
		for (int i = 0; i < 5; i++) {
			numDiscarded -= targetHand[i].cardKeep;
		}
		return numDiscarded;
	}
	//no cards discarded
	else {
		return 0;
	}
}

//AI for situation where hand contains three of a kind
//goal:  drop the lower of the two single cards and hope for FH
//will returns 1 since 1 card is discarded
int dealerAIThreeOfKind(Card targetHand[]) {
	//make freq array
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//check array low to high and stop at first entry that is a one
	for (int i = 0; i < 13; i++) {
		if (frequencyArray[i] == 1) {
			//loop through array to find the card with that particular
			//face value
			for (int j = 0; j < 5; j++) {
				if (targetHand[j].cardFace == i) {
					targetHand[j].cardKeep = 0;
					return 1;
				}
			}
		}
	}
	//we should never make it here
	printf("Something went wrong in three of a kind function.\n\n");
	return 0;
}

//AI for situation where hand contains two pair
//goal:  drop the singleton and hope for a full house on the draw
//returns 1 since 1 card is discarded
int dealerAITwoPair(Card targetHand[]) {
	//make freq array
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//check array low to high and stop at first entry that is a one
	for (int i = 0; i < 13; i++) {
		if (frequencyArray[i] == 1) {
			//loop through array to find the card with that particular
			//face value
			for (int j = 0; j < 5; j++) {
				if (targetHand[j].cardFace == i) {
					targetHand[j].cardKeep = 0;
					return 1;
				}
			}
		}
	}
	//we should never make it here
	printf("Something went wrong in two pair function.\n\n");
	return 0;
}

//AI for situation where hand contains one pair
//goal:  drop two lowest singletons and hope for a match with the
//highest singleton.
//returns 2 since 2 cards are discarded.
int dealerAIOnePair(Card targetHand[]) {
	//make freq array
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//check array low to high and grab the first two
	//entries with multiplicity one
	int i = 0;
	int count = 0;
	do {
		if (frequencyArray[i] == 1) {
			//if a match, find where in hand that match is
			//and toggle that card to discard
			for (int j = 0; j < 5; j++) {
				//both conditions are necessary, else code will just
				//see the first discarded card again and never hit
				//the second one that it needs to discard.
				if (targetHand[j].cardFace == i &&
					targetHand[j].cardKeep == 1) {

					targetHand[j].cardKeep = 0;
					count++;
				}
			}
		}
		i++;
	} while (count < 2);
	//so now we've picked both cards we want to discard
	return 2;
}

//AI for situation where hand has four cards in a row
//goal:  find and drop the card not contiguous w/ the others
//returns 1 since 1 card is discarded
int dealerAIAlmostStraight(Card targetHand[]) {
	//make freq array
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//idea: loop through array, and use 0's to delimit sequences of 1's
	int streakCount = 0;
	for (int i = 0; i < 13; i++) {
		//if we detect a 1 in the ith element, add 1 to the counter
		if (frequencyArray[i] == 1) {
			streakCount++;
		}
		else {
			//otherwise we hit a 0, so
			//is the streak counter at 1?  
			//if so, we found the noncontiguous card
			if (streakCount == 1) {
				//but remember we hit the 0 after the 1, so we now need the
				//entry just before this current one
				//we need to find the card whose value is i-1
				for (int j = 0; j < 5; j++) {
					if (targetHand[j].cardFace == i - 1) {
						targetHand[j].cardKeep = 0;
						return 1;
					}
				}
			}
			//if the streak count is anything else and we hit a 0
			//then just reset the streak count
			else {
				streakCount = 0;
			}
		}
	}
}

//AI for situation where hand has four cards of same suit
//goal:  find and drop the card that is of a different suit
//returns 1 since 1 card is discarded
int dealerAIAlmostFlush(Card targetHand[]) {
	//make freq array, BUT OF SUITS, NOT FACES
	int frequencyArray[4] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardSuit]++;
	}
	//look through frequency array of suits
	for (int i = 0; i < 4; i++) {
		//find the one that is the singleton
		if (frequencyArray[i] == 1) {
			//search through hand
			for (int j = 0; j < 5; j++) {
				//find the card that matches the singleton suit
				if (targetHand[j].cardSuit == i) {
					//mark that card for discard
					targetHand[j].cardKeep = 0;
					return 1;
				}
			}
		}
	}





}

//AI for situation where hand has nothing really going for it
//not even an almost straight or flush, so really only a high card
//goal:  find and drop the lowest 3 cards and then hope for better
//returns 3 since 3 cards are discarded
int dealerAIHighCard(Card targetHand[]) {
	//make freq array
	int frequencyArray[13] = { 0 };
	for (int i = 0; i < 5; i++) {
		frequencyArray[targetHand[i].cardFace]++;
	}
	//check array low to high and grab the first three
	//entries with multiplicity one
	int i = 0;
	int count = 0;
	do {
		if (frequencyArray[i] == 1) {
			//if a match, find where in hand that match is
			//and toggle that card to discard
			for (int j = 0; j < 5; j++) {
				//both conditions are necessary, else code will just
				//see the first discarded card again and never hit
				//the second one that it needs to discard.
				if (targetHand[j].cardFace == i &&
					targetHand[j].cardKeep == 1) {

					targetHand[j].cardKeep = 0;
					count++;
				}
			}
		}
		i++;
	} while (count < 3);
	//so now we've picked all three cards we want to discard
	return 3;
}

//function to handle dealer(AI) discards
//returns number of cards AI discarded
int dealerDiscard(Card targetHand[]) {
	//figure out how good the hand is first
	int handValue = evaluateHand(targetHand);

	switch (handValue) {
		//hold onto cards if anything higher than a straight
	case 8:
	case 7:
	case 6:
	case 5:
	case 4:
		return 0;
		break;
	case 3:
		//case for three of a kind
		return dealerAIThreeOfKind(targetHand);
		break;
	case 2:
		//case for two pair
		return dealerAITwoPair(targetHand);
		break;
	case 1:
		//case for single pair
		return dealerAIOnePair(targetHand);
		break;
	case 0:
		//case for high card.  so we have to ask...
		//is it an almost straight?
		if (highestContiguousSequence(targetHand) == 4) {
			return dealerAIAlmostStraight(targetHand);
		}
		//is it an almost flush?
		else if (highestSuitMultiplicity(targetHand) == 4) {
			return dealerAIAlmostFlush(targetHand);
		}
		//k, so the hand is basically just a high card.
		else {
			return dealerAIHighCard(targetHand);
		}
		break;
	default:
		printf("Seeing this code means you fuc'd up.  Check your code.\n\n");
		break;
	}
}

//wrapper function for the first part of a round of poker
void shuffleAndDeal(Card playerHand[], Card dealerHand[],
	int wDeck[][13], const char *wFace[], const char *wSuit[],
	int * cardPosition) {

	//make sure that both hands are marked for discard
	discardAll(playerHand);
	discardAll(dealerHand);

	//on-screen text starts here
	printf("Let's play!\n\n");
	Sleep(1500);
	//shuffle sequence
	printf("Shuffling deck...  ");
	shuffle(wDeck);
	Sleep(1500);
	printf("done.\n\n");
	Sleep(1500);
	//deal sequence to dealer
	printf("\nDealing cards to me...  ");
	Sleep(1500);
	deal(wDeck, wFace, wSuit, dealerHand, 5, cardPosition);
	Sleep(1500);
	printHand(dealerHand, wFace, wSuit, 1, 2);
	printf("\n");
	Sleep(2000);
	//deal sequence to player
	printf("\nDealing cards to you...  ");
	Sleep(1500);
	deal(wDeck, wFace, wSuit, playerHand, 5, cardPosition);
	Sleep(1500);
	printHand(playerHand, wFace, wSuit, 0, 1);
	printf("\n");
	Sleep(2000);
	system("pause");
}

//wrapper function handling dealer discard AI, discarding said cards,
//then drawing replacements from the deck.
void dealerDiscardSequence(Card dealerHand[], int wDeck[][13], 
	const char *wFace[], const char *wSuit[], 	int * cardPosition) {

	system("cls");
	printHand(dealerHand, wFace, wSuit, 1, 2);
	Sleep(500);
	printf("\n\nThinking...  ");
	Sleep(3000);
	int dealerNumDiscards = dealerDiscard(dealerHand);

	system("cls");
	printHand(dealerHand, wFace, wSuit, 1, 2);
	Sleep(1500);
	if (dealerNumDiscards > 0) {
		printf("\nI choose to discard %d cards, as marked.\n\n",
			dealerNumDiscards);
		Sleep(2000);
		printf("Drawing cards to replace discards...  ");
		deal(wDeck, wFace, wSuit, dealerHand, dealerNumDiscards, cardPosition);
		Sleep(2000);
		printf("done.\n\n\n");
	}
	else {
		printf("\nI choose not to discard any cards.\n\n");
	}

	Sleep(1500);
	system("pause");
}

//wrapper function handling player discards, and drawing replacements
void playerDiscardSequence(Card playerHand[], int wDeck[][13],
	const char *wFace[], const char *wSuit[], int * cardPosition) {
	
	system("cls");
	printHand(playerHand, wFace, wSuit, 0, 1);
	int numPlayerDiscards = playerDiscard(playerHand, wDeck, wFace, wSuit);
	if (numPlayerDiscards > 0) {
		printf("\nYou chose to discard the %d marked cards.\n\n",
			numPlayerDiscards);
		Sleep(2000);
		printf("Drawing %d cards to replace discards...  ", numPlayerDiscards);
		Sleep(2000);
		printf("done.");
		deal(wDeck, wFace, wSuit, playerHand, numPlayerDiscards, cardPosition);
	}
	else {
		printf("\nYou chose not to discard any cards.\n\n");
	}
	Sleep(2000);
	system("cls");
	printHand(playerHand, wFace, wSuit, 0, 1);
	printf("\n");
	system("pause");
}

//wrapper for the sequence to compare the two hands and issue judgment
void compareHandsSequence(Card playerHand[], Card dealerHand[],
	int wDeck[][13], const char *wFace[], const char *wSuit[],
	const char *handRanks[], int * cardPosition) {

	system("cls");
	printf("Time to reveal hands.\n\n");
	Sleep(1500);
	printHand(dealerHand, wFace, wSuit, 0, 2);
	Sleep(1500);
	printHand(playerHand, wFace, wSuit, 0, 1);
	
	Sleep(1500);
	printf("The ranking of my hand is:  %s\n\n",
		handRanks[evaluateHand(dealerHand)]);
		
	Sleep(1500);
	printf("The ranking of your hand is:  %s\n\n", 
		handRanks[evaluateHand(playerHand)]);
	Sleep(2000);
	int handRelativeValue = compareHands(playerHand, dealerHand);
	if (handRelativeValue == 1) {
		printf("Sigh, your hand beats mine.  :/\n\n");
	}
	else if (handRelativeValue == -1) {
		printf("Yussss.... my hand beats yours!  :D\n\n");
	}
	else if (handRelativeValue == 0) {
		printf("Our hands are tied.  Split pot.\n\n");
	}
	else {
		printf("Uhm... yeah idk, I need to check my code better, sorry.\n\n");
	}
	Sleep(1500);
	system("pause");
}

//plays a round of poker with player and dealer, with discarding,
//and then final evaluation of hands
void pokerSequence(Card playerHand[], Card dealerHand[],
	const char *wFace[], const char *wSuit[], const char *handRanks[]) {
	//initialize Deck array, set card position for new round of poker
	int deck[4][13] = { 0 };
	int cardPosition = 1;

	shuffleAndDeal(playerHand, dealerHand, deck, wFace, wSuit, &cardPosition);
	dealerDiscardSequence(dealerHand, deck, wFace, wSuit, &cardPosition);
	playerDiscardSequence(playerHand, deck, wFace, wSuit, &cardPosition);
	compareHandsSequence(playerHand, dealerHand, deck, wFace, wSuit, 
		handRanks, &cardPosition);
}

//wrapper for the poker game in full
void playPoker(void) {
	
	/* initialize suit array */
	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char *face[13] = { "Deuce", "Three", "Four", "Five", "Six",
		"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	/* initialize hand kitten array */
	/* note this is also in the same order as the return values
	in the "evaluateHand" function, by design.*/
	const char *handRanks[9] = { "High Card", "One Pair", "Two Pair",
		"Three of a Kind", "Straight", "Flush", "Full House",
		"Four of a Kind", "Straight Flush" };

	/* initalize deck array */
	int deck[4][13] = { 0 };
	int cardPosition = 1;

	//initialize player and dealer hands
	Card playerHand[5] = {
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	};
	Card dealerHand[5] = {
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	{ -1, -1, -1, 0 },
	};

	/* seed random-number generator */
	srand((unsigned)time(NULL));

	int numberOfRounds = 0;
	system("cls");
	printf("Okay, poker it is.\n");
	printf("How many rounds would you like to play?  ");
	scanf("%d", &numberOfRounds);
	for (int i = 0; i < numberOfRounds; i++) {
		system("cls");
		printf("****Round %d****\n\n", i + 1);
		pokerSequence(playerHand, dealerHand, face, suit, handRanks);
	}
}

//prints the main menu
void printMenu(void) {
	printf("Please choose from the following:\n\n");
	printf(" 1.  Tic-Tac-Toe\n");
	printf(" 2.  Checkers\n");
	printf(" 3.  Monopoly\n");
	printf(" 4.  Poker\n");
	printf(" 5.  Thermonuclear War\n");
	printf(" 6.  Exit\n\n");
}

//just ignore this, it don't matter
void playThermonuclearWar(void) {
	system("cls");
	printf("\nVery well.  Preparing for THERMONUCLEAR WAR . . .  \n\n\n");
	Sleep(2000);
	printf("Preparing launch silos      ");
	statusBar(1);
	printf("Loading missiles            ");
	statusBar(1);
	printf("Designating targets         ");
	statusBar(1);
	printf("Fueling missiles            ");
	statusBar(1);
	printf("Powering guidance computers ");
	statusBar(1);
	printf("Uploading trajectories      ");
	statusBar(1);
	printf("Arming warheads             ");
	statusBar(1);
	printf("Running final diagnostics   ");
	statusBar(1);
	printf("Opening launch silos        ");
	statusBar(1);
	Sleep(1500);
	printf("\nStanding by for final confirmation . . .\n\n");
	Sleep(2500);
	printf("Obtaining launch codes               ");
	statusBar(0);
	printf("Re-attempting to obtain launch codes ");
	statusBar(0);
	printf("Re-attempting to obtain launch codes ");
	statusBar(0);
	Sleep(1000);
	printf("\nABORTING.  LAUNCH CODES UNAVAILABLE.\n\n");
	Sleep(1000);
	printf("Try asking the angry orange man, maybe?  Bye for now.\n\n");
	Sleep(1000);
	system("pause");
}

//don't worry about this either
void statusBar(int status) {
	for (int i = 0; i < 10; i++) {
		printf(". ");
		Sleep(250);
	}
	Sleep(400);
	if (status) {
		printf("COMPLETE.\n");
	}
	else {
		printf("FAILED.\n");
	}
	Sleep(700);
}