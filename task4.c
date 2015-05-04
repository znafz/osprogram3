/*
Author:  Zach Nafziger and Aaron Rosenberger
Course:  COMP 340, Operating Systems
Date:    10 March 2015
Description:
Compile with:  gcc -o task4 task4.c
Run with:  ./task4

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
	int current_time;

	//first open meminfo
	FILE *ifp = fopen("/proc/meminfo", "r");

	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	double total_mem = 0.0, free_mem = 0.0, used_mem = 0.0, percentage = 0.0;
	double total_temp, free_temp, used_temp;

	system("clear");

	while (1) {
		total_temp = total_mem;
		free_temp = free_mem;
		used_temp = used_mem;
		total_mem = get_file_value(ifp, 0);	// /proc/meminfo:MemTotal
		free_mem = get_file_value(ifp, 1);	// /proc/meminfo:MemFree
		used_mem = total_mem - free_mem;	//calculate memory in use

		if (total_mem - total_temp > 0 ||
			free_mem - free_temp > 0 ||
			used_mem - used_temp > 0) {
			printf("\033[7A"); // Move up 7 lines
			printf("\033[10D"); // Move left 10 columns
			printf("\n\tTotal:\t%.0f\n\tFree:\t%.0f\n\tUsed:\t%.0f\n", total_mem, free_mem, used_mem);
			percentage = (used_mem / total_mem) * 100;
			printf("\t----- Used: %.0f%% -----\n\n", percentage);
		}
		
		printf("\033[10D"); // Move left 10 columns
		printf("\tTime: %d", clock() / CLOCKS_PER_SEC);

		if (used_mem / total_mem > LIMIT) {
			// Memory limit exceeded
			printf("\nMemory limit of %.0f%% reached.\n", LIMIT * 100);
			if (fork() == 0) {
				if (execv("pkill", "pkill memhog") == -1) {
					printf("Error with pkill\n");
					exit(1);
				}
				printf("Killed stuff\n");
				break;
			}
			else sleep(1);
		}

		if (clock() / CLOCKS_PER_SEC >= 15) break;

	}

	system("clear");
	fclose(ifp);
	return 0;
}




