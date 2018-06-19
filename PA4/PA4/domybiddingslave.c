//Source file for PA4

#include "domybiddingslave.h"

//it does what it sounds like.
void print_game_rules(void)
{
	printf("  *** Welcome to Kitty's Palace Casino! ***\n"
			"  We probably won't break both your kneecaps if we don't like you.\n\n");
	printf("\n***\n\n  Welcome to craps.  Get ready to lose all of your mone--\n"
		"  er, I mean, have a good time.  Yes, that.\n\n"
		"  Okay.  Rules.  First you roll a pair of dice, and the--\n"
		"  Actually, y'know what?  Just Google the fucking rules.  Seriously.\n\n***\n\n");
}

//gets the amount of money the user has foolishly brought to the casino and returns as double
//will not accept negative or zero balance and will loop/reprompt user until a correct
//(positive) value has been entered
double get_bank_balance(void)
{
	double moneyz = 0.0;
	do {
		//prompts user
		printf("So how much money did you foolishly bring to me, hooman?\n"
			"(Enter a valid amount in dollars and cents, if applicable)\n\n  $");
		scanf("%lf", &moneyz);

		//breaks out if an appropriate amount of cash is input, then returns that amount
		if (moneyz > 0.0)
		{
			printf("\nYes, shinies.  Excellent.  -does finger tent thing-\n\n");
			return moneyz;
		}

		//otherwise, threaten user and try this over again
		warning_message();
	} while (moneyz <= 0.0);
}

//prompts user for wager and returns as double
double get_wager_amount(void)
{
	double wager = 0.0;

	printf("So... how much money are you wagering this time?\n\n  $");
	scanf("%lf", &wager);
	return wager;
}

//checks to see if the wager is within the limits of the player's available balance
//if wager exceeds the player's allowable balance or <= 0, then 0 is returned; else 1 is returned
int check_wager_amount(double wager, double balance)
{
	if (wager <= balance && wager > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//first tells user how much money they currently have
//prompts user for wager, and makes sure it's valid input
//else, yell at user and make them do it again
//returns a valid wager if successful
//dependencies:  get wager amount, check wager amount
double wager_wrapper(double balance)
{
	double potentialWager = 0.0;
	do
	{
		//inform user of their current balance
		printf("Your current balance is: $%.2f\n\n", balance);

		//get the wager amount from user
		potentialWager = get_wager_amount();
		
		//if wager amount is okay return it
		if (check_wager_amount(potentialWager, balance) == 1)
		{
			return potentialWager;
		}

		//otherwise, warn user
		warning_message();

	} while (check_wager_amount(potentialWager, balance) == 0);
}

// rolls 2D6 and returns their sum as an int
// also prints out result of roll for user
int roll_dice(void)
{
	//just because
	char tempCharr = '\0';
	int dieRoll1 = -1, dieRoll2 = -1, dieRollSum = -2;
	printf("        Press enter to roll dice...\n");
	scanf("%c", &tempCharr);
	//roll for die1 and die2
	//+1 because rand() % 6 will return a value between 0 and 5
	dieRoll1 = (rand() % 6) + 1;
	dieRoll2 = (rand() % 6) + 1;

	dieRollSum = dieRoll1 + dieRoll2;
	printf("You rolled a %d and a %d, totalling %d.\n", dieRoll1, dieRoll2, dieRollSum);

	return dieRollSum;
}

//returns 1 if sum of dice is 7 or 11 (player wins)
//returns 0 if sum of dice is 2, 3, or 12 (house wins)
//returns -1 for all other values (becomes point)
int is_win_loss_or_point(int sum_dice)
{
	switch (sum_dice)
	{
	case 7:
	case 11: return 1;
		break;
	case 2:
	case 3:
	case 12: return 0;
		break;
	default: return -1;
		break;
	}
}

//If sum_dice is point_value then return 1 (player wins)
//If sum_dice = 7 then return 0 (player loses)
//else, return -1 (roll more)
//prec:  point_value should NOT be 2, 3, 7, 11, 12
int is_point_loss_or_neither(int sum_dice, int point_value)
{
	//the is_point_loss_or_neither function should never be called unless result is not 2, 3, 7, 11, 12
	//so this just provides an extra layer of security for me when testing
	if (point_value == 2 ||
		point_value == 3 ||
		point_value == 7 ||
		point_value == 11 ||
		point_value == 12)
	{
		printf("Error 420; contact your weed cat for help (or to get high).\n\n");
	}

	//the actual part as described in the comment above function
	if (sum_dice == point_value)
	{
		return 1;
	}
	else if (sum_dice == 7)
	{
		return 0;
	}
	return -1;
}

//dependencies: is_win_loss_or_point and is_point_loss_or_neither and roll_dice
//figures out the entire result of a single round of craps
//returns 1 if win, 0 if lose
//curr_balance and init_balance used for chatter messages
int determine_results_wrapper(int sum_dice, double curr_balance, double init_balance)
{
	if (is_win_loss_or_point(sum_dice) == 1)
	{
		printf("\nHmm... you won... somehow.\n");
		//win chatter messages
		chatter_messages(1, 1, curr_balance, init_balance);
		return 1;
	}
	else if (is_win_loss_or_point(sum_dice) == 0)
	{
		printf("\nYou lose.  Maow maow.\n");
		//loss chatter messages
		chatter_messages(1, 0, curr_balance, init_balance);
		return 0;
	}
	//this is the point situation
	else if (is_win_loss_or_point(sum_dice) == -1)
	{
		//set current point to sum of dice
		int currPoint = 0, newRoll = -1;
		currPoint = sum_dice;
		//informs the user of thus
		printf("\nYour current point is %d.\n\n", currPoint);

		//an internal var for this next part used to proc chatter_messages fcn
		int number_rolls = 0;
		//keep rolling until a win or loss state is determined
		do
		{
			newRoll = roll_dice();
			number_rolls += 1;
			//check to see if a win or loss state has been reached, and print messages/break accordingly...
			if (is_point_loss_or_neither(newRoll, currPoint) == 1)
			{
				printf("\nHmm... you matched your point.  you won... somehow.\n");
				//win chatter messages
				chatter_messages(1, 1, curr_balance, init_balance);
				return 1;
			}
			else if (is_point_loss_or_neither(newRoll, currPoint) == 0)
			{
				printf("\nHa, you lose.  Maow maow.\n");
				//loss chatter messages
				chatter_messages(1, 0, curr_balance, init_balance);
				return 0;
			}
			//chatter for continuing to roll here
			chatter_messages(number_rolls, -1, curr_balance, init_balance);
		} while (is_point_loss_or_neither(newRoll, currPoint) == -1);
	}
}

//adjusts bank_balance by wager_amount based on the var add_or_subtract
//if add_or_subtract is 1, then wager is added
//if add_or_subtract is 0, then wager is subtracted
//returns the new bank_balance
//also prints messages to inform user
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	if (add_or_subtract == 1)
	{
		printf("  -grumbles-  Fine, here's your money...\n");
		printf("  Your previous balance was %.2f and your wager was %.2f.\n", bank_balance, wager_amount);
		bank_balance += wager_amount;
		printf("  Your new balance is %.2f.\n\n", bank_balance);
		
	}
	else if (add_or_subtract == 0)
	{
		printf("  Heheh.  I take ur moneyz yuhs.\n");
		printf("  Your previous balance was $%.2f and your wager was $%.2f.\n", bank_balance, wager_amount);
		bank_balance -= wager_amount;
		printf("  Your new balance is $%.2f.\n\n", bank_balance);
	}
	return bank_balance;
}

//asks if user wants to play again and stores their answer
char play_again_prompt(void)
{
	char tempCharr = '\0';
	printf("  Welp.  Play again? (y/n)  ");
	scanf("%c", &tempCharr);
	printf("\n");
	return tempCharr;
}

//handles the "play" part of the game - roll, roll more if necessary, figure out win or lose
//then update money, then check if player's still in game, then see if player wants to keep going
//eventually returns the updated balance after playing, or -1 if user has been warned too many times
//init balance really only used for "chatter" messages
//dependencies: a lot, by definition.  look at the function.
double play_craps(double currBalance, double initBalance)
{
	char playAgain = '\0';
	do
	{
		//first, wager
		double wager = 0.0;
		wager = wager_wrapper(currBalance);

		//eats up any whitespace (Enters) before rolls
		char tempCharr = '\0';
		scanf("%c", &tempCharr);

		int sumDice = 0;
		//then roll dice
		sumDice = roll_dice();

		//determine results
		int stateWL = 0;
		stateWL = determine_results_wrapper(sumDice, currBalance, initBalance);

		//adjust bank balance
		//since stateWL is now 1 on win, 0 on loss, works out with 1 for adding money, 0 for losing money
		currBalance = adjust_bank_balance(currBalance, wager, stateWL);

		//see if user wants to play again
		playAgain = play_again_prompt();

	}
	//while the user wants to play again and still has money...
	while (currBalance > 0.5 && (playAgain == 'y' || playAgain == 'Y'));

	//warning message when can't play again
	if (currBalance <= 0.5)
	{
		printf("\nNo!  You are broke; you cannot play again.");
	}

	return currBalance;
}

//berates user based on game state
//win_loss_neither is as follows:  win = 1, loss = 0, neither = -1
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{
	//let's not harass the user every single time...
	//only runs a message ~40% of the time
	int someRand = 0;
	someRand = rand() % 5;

	if (someRand < 2)
	{
		//branch for if user is overall winning
		if (current_bank_balance > initial_bank_balance)
		{
			//did user win last roll?
			if (win_loss_neither == 1)
			{
				printf("Dammit!  I'll get you next time.\n");
			}
			else if (win_loss_neither == 0)
			{
				printf("Ha!  Get ready to gib my moneyz back.\n");
			}
			else if (win_loss_neither == -1)
			{
				//let's see how many rolls we've done at this point...
				if (number_rolls < 3)
				{
					printf("Welp, guess you're rolling again.\n");
				}
				else if (number_rolls < 6)
				{
					printf("All right, next roll - next roll you're getting screwed.\n");
				}
				else
				{
					printf("Christ, this is getting boring...\n");
				}
			}
		}

		//branch for if user is overall losing
		else
		{
			//did user win last roll?
			if (win_loss_neither == 1)
			{
				printf("Shit.  You were doing so wonderfully at giving me your money, too.\n");
			}
			else if (win_loss_neither == 0)
			{
				printf("Yus, moneyz.  Gib all your moneyz.\n");
			}
			else if (win_loss_neither == -1)
			{
				//let's see how many rolls we've done at this point...
				if (number_rolls < 3)
				{
					printf("Welp, guess you're rolling again.\n");
				}
				else if (number_rolls < 6)
				{
					printf("All right, next roll - next roll you're getting screwed.\n");
				}
				else
				{
					printf("Christ, this is getting boring...\n");
				}
			}
		}
	}
	
	printf("\n");
}

//berates the user for stupidity, whether intentionally or otherwise
void warning_message(void)
{
	int i = 0;
	i = rand() % 15;
	printf("\n");
	switch (i)
	{
	case 0: printf("  Keep up that funny business and you'll be staring at your spleen.\n\n");
		break;
	case 1: printf("  I swear I will get a jackal to break your kneecaps.\n\n");
		break;
	case 2: printf("  Every time you fuck this up a fluffy kitten dies.\n\n");
		break;
	case 3: printf("  I will call security if you try that again.\n\n");
		break;
	case 4: printf("  You know people \"disappear\" all the time in this town... \n  especially troublemakers.\n\n");
		break;
	case 5: printf("  There's three dead hookers in the dumpster out back - you want to join them?\n\n");
		break;
	case 6: printf("  You don't want to be fucking with me tonight, pal.  Believe me.\n\n");
		break;
	case 7: printf("  That security guard behind you could snap you like a toothpick, y'know.\n\n");
		break;
	case 8: printf("  Numbers.  Do you understand how numbers work, asshole?\n\n");
		break;
	case 9: printf("  Y'know, the last person that fucked with me like this \n  got fed to a tiger.  Just sayin'.\n\n");
		break;
	case 10: printf("  I'm actually surprised you've gotten this far in life\n  with your level of incompetence.\n\n");
		break;
	case 11: printf("  Ffs check your input before pressing enter, man.\n\n");
		break;
	case 12: printf("  Yeah, there are some casinos that can deal with your bullshit while\n"
					"  you siphon free drinks off of them.  Not this one.\n\n");
		break;
	case 13: printf("  I'm pretty sure if someone looked up 'asshole' in the dictionary\n"
					"  there would be your ugly face by the definition.\n\n");
		break;
	case 14: printf("  Try that again and I will [censored] your [censored]\n"
					"  and then I will take my [censored] and [censored] your [censored].\n\n");
		break;
	default: printf("Shit, did I fuck up my code again?  Uh... idk, report this to someone.\n\n");
		break;
	}
	printf("So let's try that again, shall we?\n");
}

//gives a sense of closure to the user based on their winnings, or lack thereof
void epilogue_message(double current_balance, double initial_balance)
{
	printf("\n\n***\n");
	printf("You came to Kitty's Palace with $%.2f\n", initial_balance);
	printf("and you are leaving with $%.2f\n\n", current_balance);
	if (current_balance/initial_balance < 0.2)
	{
		printf("You leave Kitty's Palace destitute.  You are forced to perform\n"
			"unspeakable sexual acts just so you can get enough money for a\n"
			"bus ticket home.\n\n");
	}
	else if (current_balance / initial_balance < 0.5)
	{
		printf("You leave Kitty's Palace having lost a shitton of money.  When you\n"
			"get home your significant other leaves you, and then you burn\n"
			"to death in a fire.\n\n");
	}
	else if (current_balance / initial_balance < 0.9)
	{
		printf("You leave Kitty's Palace not having done very well at all.  In your\n"
			"depressed state you don't look both ways and get run over by a bus.\n\n");
	}
	else if (current_balance / initial_balance < 1.2)
	{
		printf("You leave Kitty's Palace having roughly broken even.  But deep down\n"
			"you know the kitty is watching you, waiting for you to fuck up next time so\n"
			"so that he can take all of your money.\n\n");
	}
	else
	{
		printf("You leave Kitty's Palace having won some money.  You are giddy until\n"
			"you are cornered in a nondescript back alley and get the shit beat out\n"
			"of you.  You learn the hard way: don't fuck with kitty.\n\n");
	}
	printf("  THE END\n\n");
}