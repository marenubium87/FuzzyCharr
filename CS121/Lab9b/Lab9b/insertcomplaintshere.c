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

//binary search which does not rely on left index and right index as parameters
//prec: target array is a sorted int array of size at least 1, my_value is a valid int
//post: gives message regarding whether target value was found and
//		returns array index location of target value
//		or -1 if target value was not found
int bin_search_redux(int target[], int my_value, int target_size)
{
	//at some point the target size will in fact become 1
	if (target_size <= 2)
	{
		if (target[0] == my_value)
		{
			printf("Target value of %d was found in array\n", my_value);
			return my_value;
		}
		else if (target[1] == my_value)
		{
			printf("Target value of %d was found in array\n", my_value);
			return my_value;
		}
		else
		{
			printf("Target value of %d was not found in array\n", my_value);
			return -1;
		}
	}


	//this integer division is fine
	int mid_index = (target_size) / 2;
	if (target[mid_index] > my_value)
	{
		//searches inside the front half of the array up to mid_index - 1 
		//if mid_index value is greater than the target value
		return bin_search_redux(target, my_value, mid_index - 1);
	}
	else if (target[mid_index] < my_value)
	{
		//searches the back half of the array starting from mid_index + 1
		//the length of the back half of the array is now target_size - mid_index - 1
		return bin_search_redux(target + mid_index + 1, my_value, target_size - mid_index - 1);
	}
	else
	{
		printf("Target value of %d was found in location %d of array\n", my_value, mid_index);
		return mid_index;
	}
}










int fooBar(void)
{
	char myTestArr[64] = "soft kitty, warm kitty, little ball of fur";
	char * maowPointer = NULL;

	int i = 0;
	for (i = 0; myTestArr[i] != '\0'; i++)
	{
		if (myTestArr[i] == ',')
		{
			if (myTestArr[i + 1] == ' ')
			{
				maowPointer = &myTestArr[i + 2];
			}
		}
	}
}