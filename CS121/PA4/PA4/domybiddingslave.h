//Header file for PA4

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//sexually transmitted diseases library
#include <stdlib.h>
//making math in my parents' basement
#include <math.h>
//time keeps on slipping, slipping, slipping... into the future...
#include <time.h>

//explains what people are getting themselves into
void print_game_rules(void);

//gets the amount of money the user has foolishly brought to the casino and returns as double
double get_bank_balance(void);

//prompts user for wager and returns as double
double get_wager_amount(void);

//checks to see if the wager is within the limits of the player's available balance
//if wager exceeds the player's allowable balance (or < 0), then 0 is returned; else 1 is returned
int check_wager_amount(double wager, double balance);

//prompts user for wager, and makes sure it's valid input
//else, yell at user and make them do it again
//returns a valid wager if successful
//dependencies:  get wager amount, check wager amount
double wager_wrapper(double balance);

// rolls 2D6 and returns their sum as an int, and also informs the user of
// the individual die rolls as well as the sum
int roll_dice(void);

//returns 1 if sum of dice is 7 or 11 (player wins)
//returns 0 if sum of dice is 2, 3, or 12 (house wins)
//returns -1 for all other values (becomes point)
int is_win_loss_or_point(int sum_dice);

//If sum_dice is point_value then return 1 (player wins)
//If sum_dice = 7 then return 0 (player loses)
//else, return -1 (roll more)
//prec:  point_value should NOT be 2, 3, 7, 11, 12
int is_point_loss_or_neither(int sum_dice, int point_value);

//using is_win_loss_or_point and is_point_loss_or_neither
//figures out the entire result of a single round of craps
//returns 1 if win, 0 if lose
int determine_results_wrapper(int sum_dice, double curr_balance, double init_balance);

//adjusts bank_balance by wager_amount based on the var add_or_subtract
//if add_or_subtract is 1, then wager is added
//if add_or_subtract is 0, then wager is subtracted
//returns the new bank_balance
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);

//asks if user wants to play again and stores their answer
char play_again_prompt(void);

//handles the "play" part of the game - roll, roll more if necessary, figure out win or lose
//then update money, then check if player's still in game, then see if player wants to keep going
double play_craps(double currBalance, double initBalance);

//more messages to fuck with user during execution of program
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);

//prints a warning message at random from a pool to keep the user in their place
//if they enter a negative wager or bank balance
void warning_message(void);

//tells user how they ended up, based on ratio of final money to initial money
void epilogue_message(double current_balance, double initial_balance);