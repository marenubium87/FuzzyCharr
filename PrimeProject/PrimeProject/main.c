/*
* Aerie, CS121
* Instructor: Reynx
* Prime Project I have no idea how to fucking do
* 12 September 2018
*/

#include "howtocodeplzhalp.h"

int main(int argc, char * argv[])
{
	int num_array_1[10] = { 0 };
	int num_array_2[10] = { 0 };

	int prime_array_1[10] = { 0 };
	int prime_array_2[10] = { 0 };
	
	//populates arrays and determines size of each array
	int num_array_1_size = populate_array(num_array_1);
	int num_array_2_size = populate_array(num_array_2);

	//populates prime arrays and figures out size of each prime array
	int prime_array_1_size = write_primes(num_array_1, prime_array_1, num_array_1_size);
	int prime_array_2_size = write_primes(num_array_2, prime_array_2, num_array_2_size);

	if (prime_array_1_size > prime_array_2_size)
	{
		printf("1: ");
		print_array(prime_array_1, prime_array_1_size);
	}
	else if (prime_array_1_size < prime_array_2_size)
	{
		printf("2: ");
		print_array(prime_array_2, prime_array_2_size);
	}

	return 0;
}
