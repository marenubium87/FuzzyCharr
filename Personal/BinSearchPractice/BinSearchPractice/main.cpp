#include <iostream>


using std::cout;

int binSearch(int arr[], int arrSize, int target) {
	int left = 0;
	int right = arrSize - 1;
	int mid;

	while (left <= right) {
		mid = left + (right - left) / 2;
		//did we find the value?
		if (target == arr[mid]) {
			return mid;
		}
		else if (target < arr[mid]) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	return -1;
}

int main() {

	int sortedArr[20] = { 2, 3, 5, 7, 11, 13 };
	for (int i = 1; i < 17; i++) {
		cout << i << "  " << binSearch(sortedArr, 1, i) << std::endl;
	}

	return 0;
}