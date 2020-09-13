//header file for poker

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct card {
	int cardOrder;
	int cardSuit;
	int cardFace;
	int cardKeep;
} Card;

/* shuffle cards in deck */
void shuffle(int wDeck[][13]);

//prints out target player's hand to the console
//if hide = 0, hand will be printed; if 1, hand will be obfuscated
//playerID prints "your hand" for 1, "my hand" for 2
void printHand(Card targetHand[],
	const char *wFace[], const char *wSuit[], int hide, int playerID);

//function to mark all cards as to be discarded...
//helpful for between rounds of poker
void discardAll(Card targetHand[]);

//deals numCardsToDeal from deck to targetHand, keeping track
//of card position (as output param) so that future deals can
//start from the correct location.
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[],
	Card targetHand[], int numCardsToDeal, int * cardPosition);

//auxiliary function for deal
//places next card from deck into next available position (keep == 0)
//in targetHand array, by assigning the card position, the rowID (suit)
//and the columnID (face), and also flips cardKeep to 1
void placeNextCard(int * cardPosition, Card targetHand[], int row, int col);

//returns the number of the highest face multiplicity in targetHand
//e.g. will return 1 if hand contains no pairs
//will return 2 if a pair is found
//will return 3 if 3 of a kind is found, 4 if 4 of a kind is found
//if this function return 5, someone cheated or code is borked
//takes care of hands:  one pair, three of a kind, four of a kind
int highestFaceMultiplicity(Card targetHand[]);

//returns the number of the highest suit multiplicity in targetHand
//e.g. if hand is S S H C D then fcn will return 2
//takes care of flushes
int highestSuitMultiplicity(Card targetHand[]);

//returns the highest contiguous sequence in targetHand
//e.g. if hand is 3 4 7 8 9, will return 3 (for 7 8 9)
int highestContiguousSequence(Card targetHand[]);

//returns 1 if targetHand contains two pair, 0 else
//takes care of two pair, obviously
int containsTwoPair(Card targetHand[]);

//returns 1 if targetHand contains a full house, 0 else
//takes care of full house situation, obviously
int containsFullHouse(Card targetHand[]);

//evaluates targetHand and returns the following values
//0:  nothing (high card)	1:  one pair
//2:  two pair				3:  three of a kind
//4:  straight				5:  flush
//6:  full house			7:  four of a kind
//8:  straight flush
int evaluateHand(Card targetHand[]);

//aux function for compareHands
//finds the column (face) value of the highest card with multiplicity mult
//ex: if mult == 1, TT862 would return 6, b/c 8 is the highest single card
//		and is in position 6 in the face array
//ex2:  if mult == 2, AQTT8 will return 8, b/c T is the highest card face
//		with multiplicity 2 and is in position 8 in the face array.
int findHighestCard(Card targetHand[], int mult);

//aux function for compareHands
//compares two hands element by element running from high card to low
//at the first discrepency, returns 1 if handA has higher value,
//returns -1 if handB has the higher value, returns 0 if both hands
//have exact same face value (since suits don't matter in poker)
int rankSimilarHands(Card HandA[], Card HandB[]);

//compares handA and handB
//returns 1 if handA is better in value than handB
//returns -1 if handB is better in value than handA
//returns 0 if hands are equal in value
int compareHands(Card handA[], Card handB[]);

//aux function for player discards
//handles user selection of cards to discard and
//gives user feedback on which cards are currently marked for discard
//returns 1 when user is ready to continue, 0 else
int handleDiscards(Card targetHand[], const int wDeck[][13],
	const char *wFace[], const char *wSuit[]);

//function to handle player discards
//returns number of cards player discarded
int playerDiscard(Card targetHand[], const int wDeck[][13],
	const char *wFace[], const char *wSuit[]);

//AI for situation where hand contains three of a kind
//goal:  drop the lower of the two single cards and hope for FH
//will returns 1 since 1 card is discarded
int dealerAIThreeOfKind(Card targetHand[]);

//AI for situation where hand contains two pair
//goal:  drop the singleton and hope for a full house on the draw
//returns 1 since 1 card is discarded
int dealerAITwoPair(Card targetHand[]);

//AI for situation where hand contains one pair
//goal:  drop two lowest singletons and hope for a match with the
//highest singleton.
//returns 2 since 2 cards are discarded.
int dealerAIOnePair(Card targetHand[]);

//AI for situation where hand has four cards in a row
//goal:  find and drop the card not contiguous w/ the others
//returns 1 since 1 card is discarded
int dealerAIAlmostStraight(Card targetHand[]);

//AI for situation where hand has four cards of same suit
//goal:  find and drop the card that is of a different suit
//returns 1 since 1 card is discarded
int dealerAIAlmostFlush(Card targetHand[]);

//AI for situation where hand has nothing really going for it
//not even an almost straight or flush, so really only a high card
//goal:  find and drop the lowest 3 cards and then hope for better
//returns 3 since 3 cards are discarded
int dealerAIHighCard(Card targetHand[]);

//function to handle dealer(AI) discards
//returns number of cards AI discarded
int dealerDiscard(Card targetHand[]);

//wrapper function for the first part of a round of poker
void shuffleAndDeal(Card playerHand[], Card dealerHand[],
	int wDeck[][13], const char *wFace[], const char *wSuit[],
	int * cardPosition);

//wrapper function for the first part of a round of poker
void shuffleAndDeal(Card playerHand[], Card dealerHand[],
	int wDeck[][13], const char *wFace[], const char *wSuit[],
	int * cardPosition);

//wrapper function handling dealer discard AI, discarding said cards,
//then drawing replacements from the deck.
void dealerDiscardSequence(Card dealerHand[], int wDeck[][13],
	const char *wFace[], const char *wSuit[], int * cardPosition);

//wrapper function handling player discards, and drawing replacements
void playerDiscardSequence(Card playerHand[], int wDeck[][13],
	const char *wFace[], const char *wSuit[], int * cardPosition);

//wrapper for the sequence to compare the two hands and issue judgment
void compareHandsSequence(Card playerHand[], Card dealerHand[],
	int wDeck[][13], const char *wFace[], const char *wSuit[],
	const char *handRanks[], int * cardPosition);

//plays a round of poker with player and dealer, with discarding,
//and then final evaluation of hands
void pokerSequence(Card playerHand[], Card dealerHand[],
	const char *wFace[], const char *wSuit[], const char *handRanks[]);

//wrapper for the poker game in full
void playPoker(void);

//prints the main menu
void printMenu(void);

//just ignore this, it don't matter
void playThermonuclearWar(void);

//don't worry about this either
void statusBar(int status);