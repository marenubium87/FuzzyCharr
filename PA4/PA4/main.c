/*
* Aerie, CS 121
* Instructor: Reynx
* PA 4
* 16 Jun '18
*/

#include "domybiddingslave.h"

int main()
{
	printf(" PA5 - Craps\n\n");
	//seeds the RNG with YOUR DOOM!!  er, I mean...
	srand((unsigned int)time(NULL));

	//like what it says.
	print_game_rules();

	//var declaration
	double initBankBalance = 0.0, currBalance = 0.0;

	//gets how much money idiot, i mean user, starts with
	initBankBalance = get_bank_balance();

	//sets current balance to that amount
	currBalance = initBankBalance;

	//play craps
	currBalance = play_craps(currBalance, initBankBalance);

	//seeing how you did, in general, then judges you accordingly
	epilogue_message(currBalance, initBankBalance);

	//end program
	printf("End of program; press Enter to continue");
	char endCharr = '\0';
	scanf("%c", &endCharr);
	scanf("%c", &endCharr);
	return 0;
}