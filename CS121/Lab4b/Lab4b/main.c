/*
* Aerie, CS 121
* Instructor: Reynx
* Lab 4 Part 2
* 10 Jun '18
*/

//grabs header file
#include "mrow.h"

int main()
{
	printf(" Lab 4 Part 2\n\n");

	//variable declaration
	int bonus = 0;

	//adds bonuses
	bonus = bonus + wasAllStar();
	bonus = bonus + wasRegularMVP();
	bonus = bonus + wasWorldMVP();
	bonus = bonus + wasGoldGlove();
	bonus = bonus + wasSilverSlug();
	bonus = bonus + wasHomeRunChamp();
	bonus = bonus + wasBattingChamp();

	//outputs bonus
	printf("The bonus for this player is $%d." "\n", bonus);
	//mocks player if they are shit.
	if (bonus == 0)
	{
		printf("God, what a loser.\n");
	}
	printf("\n");
	printf("End of program; press Enter to continue");
	//kitty says no to insta-termination
	char tempCharr = '\0';
	scanf("%c", &tempCharr);
	scanf("%c", &tempCharr);

	return 0;
}