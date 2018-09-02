//source file for lab 9b

#include "insertcomplaintshere.h"

//debugger function
//prints out the contents of target int array of size target_size
void print_int_array(int target[], int target_size)
{
	printf("Target array composition is:\n");
	for (int i = 0; i < target_size; i++)
	{
		printf("%d ", target[i]);
	}
	printf("\n\n");
}

//binary search - searches target array for my_value
//between left_index and right_index
//start with left_index at 0 and right_index at array_size - 1
//prec: target array is a sorted int array, myValue is a valid int
//post: gives message regarding whether target value was found
//returns array index location of target value
//or -1 if target value was not found
int bin_search(int target[], int my_value, int left_index, int right_index)
{
	//if the indices are right next to each other or on top of each other, 
	//then check each of the two and output accordingly
	if (left_index + 1 >= right_index)
	{
		if (target[left_index] == my_value)
		{
			printf("Target value of %d was found in location %d of array\n", my_value, left_index);
			return left_index;
		}
		else if (target[right_index] == my_value)
		{
			printf("Target value of %d was found in location %d of array\n", my_value, right_index);
			return right_index;
		}
		else
		{
			printf("Target value of %d was not found in the array\n", my_value);
			return -1;
		}
	}

	//this integer division is fine
	int mid_index = (left_index + right_index) / 2;
	//check whether mid_index value is higher or lower than my_value and then
	//call bin_search again with indices adjusted accordingly
	if (target[mid_index] < my_value)
	{
		return bin_search(target, my_value, mid_index, right_index);
	}
	else if (target[mid_index] > my_value)
	{
		return bin_search(target, my_value, left_index, mid_index);
	}
	//only way it can get here is if the mid_index value is the correct value
	else
	{
		printf("Target value of %d was found in location %d of array\n", my_value, mid_index);
		return mid_index;
	}
}