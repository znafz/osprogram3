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
	int value;
	char *name;
	char trash[100];

	/* If target == 1, looking for MemFree
	   If target == 0, looking for MemTotal */

	//fgets(c, 40, ifp);		// Gets whole line
	//temp = strdup(c);		// Temporary file to work with
	//name = strsep(&temp, ':');

	rewind(ifp);

	fscanf(ifp, "%s %d", name, &value);		// Get number & "Kb"
	fgets(trash, 50, ifp);

	if (!target) printf("MemTotal = %d\n", value);

	if (target) {
		fscanf(ifp, "%s %d", name, &value);		// Get number & "Kb"
		fgets(trash, 50, ifp);
		printf("MemFree = %d\n", value);
	}

	rewind(ifp);

	return value;
}

int main(int argc, char** argv) {

	FILE *ifp = fopen("/proc/meminfo", "r");
	//char c[1000];
	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	//char * temp;
	//char * token;
	//printf("Testing...\nBefore:\n");
	//fgets(c, 100, ifp);//total memory
	//temp = strdup(c);
	//int i;
	//for (i = 0; i < 9; i++)
	//	token = strsep(&temp, " "); // had to repeat strsep for some reason
	//total_mem = atoi(token);
	//printf("\tTotal Memory: %d\n", total_mem);


	////now get free memory
	//fgets(c, 100, ifp);
	//temp = strdup(c);
	//for (i = 0; i < 11; i++)
	//	token = strsep(&temp, " "); // had to repeat strsep for some reason
	//free_mem = atoi(token);
	//printf("\tFree Memory: %d\n", free_mem);
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
			printf("\tUsed Memory: %d\n", used_mem);
			printf("\tMemory Used By Process: %d\n", used_mem - old_used_mem);
		}
		fclose(ifp);
		exit(1);
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
		exit(1);
	}

	printf("\n\nugh\n\n");

	return 0;
}