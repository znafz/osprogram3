/*
Author:  Zach Nafziger and Aaron Rosenberger
Course:  COMP 340, Operating Systems
Date:    10 March 2015
Description: Task 3
Compile with:  gcc -o task3 task3.c
Run with:  ./task3

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <math.h>

int get_file_value(FILE * ifp, int target) {
	int value = 0;
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

	return value;
}

int main(int argc, char** argv) {

	FILE *ifp = fopen("/proc/meminfo", "r");

	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	int i;
	int total_mem, free_mem, used_mem;

	total_mem = get_file_value(ifp, 0);		// Total Memory
	free_mem = get_file_value(ifp, 1);		// Free Memory

	//calculate memory in use
	used_mem = total_mem - free_mem;
	printf("\tUsed Memory: %d\n", used_mem);

	int flag = 5;
	int old_used_mem = used_mem;
	
	if (fork() == 0) {
		while (flag--) {
			free_mem = get_file_value(ifp, 1);

			used_mem = total_mem - free_mem;
			printf("\t\tUsed Memory: %d\n", used_mem);
			printf("\t\tMemory Used By Process: %d\n", used_mem - old_used_mem);
		}
		fclose(ifp);
		sleep(5);
	} else {
		printf("\nPARENT\n\n");
		flag = 50;
		int j, k, ugh;
		ugh = 1;
		while (flag--) {
			for (i = 0; i < 100; i++) {
				for (k = 1; k <= 100; k++) {
					for (j = 0; j < 100; j++) {
						ugh += 1;
					}
				}
			}
		}
		fclose(ifp);
	}

	printf("\n\nugh\n\n");

	return 0;
}