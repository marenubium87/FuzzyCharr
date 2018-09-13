//source file for prime project
#include "howtocodeplzhalp.h"


//for a three line triplet in input.txt...
//ignores line 1 (i.e. ignores the array ID)
//uses line 2 to determine number of elements
//uses line 3 to populate target array
//also returns the target size
int populate_array(int target[])
{
	int target_size = 0;
	//ignores the array id
	scanf("%*d");
	//grabs the size of array
	scanf("%d", &target_size);
	for (int i = 0; i < target_size; i++)
	{
		scanf("%d", &target[i]);
	}
	return target_size;
}

//determines if target number is prime or not
//returns 1 if prime, 0 if not
int determine_prime(int target)
{
	if (target <= 1)
	{
		return 0;
	}
	else if (target == 2)
	{
		return 1;
	}
	else if (target == 3)
	{
		return 1;
	}
	
	//the maximum divisor that needs to be checked 
	//before it's concluded that target is prime
	int max_divisor = floor(sqrt((double) target));
	for (int i = 2; i <= max_divisor; i++)
	{
		if (target % i == 0)
		{
			//if at any point a divisor divides target evenly, it can't be prime
			return 0;
		}
	}
	//if the code makes it to here no divisor divides target evenly
	//thus it must be prime;
	return 1;
}

//goes through source, and for any primes writes them to 
//successive elements of dest; returns destination array size
int write_primes(int source[], int dest[], int source_size)
{
	//required so that we know which element in dest array to write to
	int dest_index = 0;

	for (int i = 0; i < source_size; i++)
	{
		if (determine_prime(source[i]) == 1)
		{
			dest[dest_index] = source[i];
			dest_index++;
		}
	}
	//dest_index will end up at the first element that does not contain a prime
	//which is also equal to the destination size since the array starts at 0
	return dest_index;
}

//prints the first target_size elements of array target
void print_array(int target[], int target_size)
{
	for (int i = 0; i < target_size; i++)
	{
		printf("%d ", target[i]);
	}
}