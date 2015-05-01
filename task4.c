/*
Author:  Zach Nafziger and Aaron Rosenberger
Course:  COMP 340, Operating Systems
Date:    10 March 2015
Description: Ends user processes when memory allocation exceeds given limit.
Compile with:  gcc -o task4 task4.c
Run with:  ./task4

*/

#define LIMIT 0.85

#include <stdio.h>
#include <stdlib.h> /* For exit() function*/

double get_file_value(FILE * ifp, int target) {
	int value = 0.0;
	char name[15];
	char trash[100];

	/* If target == 1, looking for MemFree
	If target == 0, looking for MemTotal */

	fscanf(ifp, "%s %d", name, &value);		// Get number & "Kb"
	fgets(trash, 50, ifp);

	if (target) {
		fscanf(ifp, "%s %d", name, &value);		// Get number & "Kb"
		fgets(trash, 50, ifp);
	}

	rewind(ifp);

	return (double)value;
}

int main(int argc, char** argv) {

	//first open meminfo
	FILE *ifp = fopen("/proc/meminfo", "r");

	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	double total_mem, free_mem, used_mem, percentage;
	int flag = 10;

	while (flag) {
		total_mem = get_file_value(ifp, 0);	//total memory
		free_mem = get_file_value(ifp, 1);	//now get free memory
		used_mem = total_mem - free_mem;	//calculate memory in use

		printf("\n\tTotal:\t%.0f\n\tFree:\t%.0f\n\tUsed:\t%.0f\n", total_mem, free_mem, used_mem);

		percentage = (used_mem / total_mem) * 100;

		printf("\t----- Used: %.0f%% -----\n", percentage);
		if (used_mem / total_mem > LIMIT) {
			// Memory limit exceeded
			printf("Memory limit of %.0f%% reached.\n", LIMIT * 100);

			// Now kill user processes... TODO!
		}

		sleep(1);
		flag--;
	}

	fclose(ifp);
	return 0;
}
