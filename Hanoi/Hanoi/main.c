#include "hanoi.h"

int main() {

	int diskArray[NUM_DISKS + 1] = { 0 };
	for (int i = 0; i <= NUM_DISKS; i++) {
		diskArray[i] = 1;
	}
	
	//FILE * outfile = NULL;
	//outfile = fopen("hanoi_output.txt", "w");

	printf("Running Hanoi for %d disks...\n\n", NUM_DISKS);
	//fprintf(outfile, "Running Hanoi for %d disks...\n\n", NUM_DISKS);
	
	hanoi(diskArray, NUM_DISKS);
	
	printf("Done.\n\n");
	//fprintf(outfile, "Done.\n\n");


	system("pause");
	return 0;
}