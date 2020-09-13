//source file for Lab 4 Part 2

//grabs header file
#include "mrow.h"

//each of these functions prompts for the specific type of bonus, and if the user enters 'y'
//it will return the appropriate amount as defined in the header file.
//also newlines at end to prepare for next question.
int wasAllStar(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player an all-star?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = ALLSTAR;
	}
	printf("\n");
	return bonus;
}

int wasRegularMVP(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player a regular season MVP?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = REGULARMVP;
	}
	printf("\n");
	return bonus;
}

int wasWorldMVP(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player a world series MVP?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = WORLDMVP;
	}
	printf("\n");
	return bonus;
}

int wasGoldGlove(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player a gold glove award winner?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = GOLDGLOVE;
	}
	printf("\n");
	return bonus;
}

int wasSilverSlug(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player a silver slugger award winner?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = SILVERSLUG;
	}
	printf("\n");
	return bonus;
}

int wasHomeRunChamp(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player a home run champ?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = HOMERUNCHAMP;
	}
	printf("\n");
	return bonus;
}

int wasBattingChamp(void)
{
	char response = '\0';
	int bonus = 0;
	printf("Was this player a batting average champ?  (y/n) ");
	scanf(" %c", &response);

	if (response == 'y' || response == 'Y')
	{
		bonus = BATTINGCHAMP;
	}
	printf("\n");
	return bonus;
}