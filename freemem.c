/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:
  Compile with:  gcc -o freemem freemem.c
  Run with:  ./freemem

  */

#define LIMIT 0.85

#include <stdio.h>
#include <stdlib.h> /* For exit() function*/
#include <time.h>

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

	clock_t start = clock();

	//first open meminfo
	FILE *ifp = fopen("/proc/meminfo", "r");

	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	double total_mem, free_mem, used_mem, percentage;
	
	while (1) {
		total_mem = get_file_value(ifp, 0);	// /proc/meminfo:MemTotal
		free_mem = get_file_value(ifp, 1);	// /proc/meminfo:MemFree
		used_mem = total_mem - free_mem;	//calculate memory in use
		
		//printf("\033[7A"); // Move up 7 lines
		//printf("\033[10D"); // Move left 10 columns
		system("clear");
		printf("\n\tTotal:\t%.0f\tFree:\t%.0f\tUsed:\t%.0f", total_mem, free_mem, used_mem);
		printf("\tTime: %d", clock() / CLOCKS_PER_SEC);

		percentage = (used_mem / total_mem) * 100;

		printf("\n\t----- Used: %.0f%% -----\n", percentage);
		if (used_mem / total_mem > LIMIT) {
			// Memory limit exceeded
			printf("Memory limit of %.0f%% reached.\n", LIMIT * 100);
		}
		
		if (clock() / CLOCKS_PER_SEC >= 15) exit(0);

		sleep(1);

	}

	fclose(ifp);
	return 0;
}
