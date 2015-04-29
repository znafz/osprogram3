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

int main(int argc, char** argv) {
	/* Timing stuff */
	clock_t start = clock(), diff;
	int msec;
	//How to get time:
	//msec = diff * 1000 / CLOCKS_PER_SEC;

	FILE *ifp = fopen("/proc/meminfo", "r");
	char c[1000];
	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	int total_mem, free_mem, used_mem;
	char * temp;
	char * token;
	printf("Testing...\nBefore:\n");
	fgets(c, 100, ifp);//total memory
	temp = strdup(c);
	int i;
	for (i = 0; i < 9; i++)
		token = strsep(&temp, "  "); // had to repeat strsep for some reason
	total_mem = atoi(token);
	printf("\tTotal Memory: %d\n", total_mem);


	//now get free memory
	fgets(c, 100, ifp);
	temp = strdup(c);
	for (i = 0; i < 11; i++)
		token = strsep(&temp, "  "); // had to repeat strsep for some reason
	free_mem = atoi(token);
	printf("\tFree Memory: %d\n", free_mem);

	//calculate memory in use
	used_mem = total_mem - free_mem;
	printf("\tUsed Memory: %d\n", used_mem);

	int flag = 500;
	
	if (fork() == 0) {
		while (flag--) {
			//sleep(1);	// Reduce memory usage of memory watcher...
			// "Lap" the clock in diff; every 5 seconds, 
			if (((diff = clock() - start) * 1000 / CLOCKS_PER_SEC) % 5 == 0) {

				/* Do memory watching stuff */
				//printf("\nCHECK %d\n", flag);
				rewind(ifp);
				fgets(c, 100, ifp);
				fgets(c, 100, ifp);
				temp = strdup(c);
				for (i = 0; i < 11; i++)
					token = strsep(&temp, "  "); // had to repeat strsep for some reason
				free_mem = atoi(token);
				//printf("\tFree Memory: %d\n", free_mem);

				//calculate memory in use
				int old_used_mem = used_mem;
				used_mem = total_mem - free_mem;
				//printf("\tUsed Memory: %d\n", used_mem);
				if (used_mem - old_used_mem)
					printf("\tMemory Used By Process: %d\n", used_mem - old_used_mem);

			}

		}
		
		exit(1);
	} else {
		printf("\nPARENT\n\n");
		//sleep(1);
		flag = 50;
		int i, j, k, ugh;
		ugh = 1;
		while (flag--) {
			for (i = 0; i < 10; i++) {
				//printf("ugh... \n");
				for (k = 1; k <= 50; k++) {
					//if (k % 20 == 0) printf("\n");
					//printf("%d ", ugh++);
					for (j = 0; j < 1000; j++) {
						ugh *= 1;
					}
				}
				//printf("\n");
			}
		}
		printf("ugh = %d\n", ugh);
		exit(1);
	}

	printf("\n\n\n\n\nugh\n\n");

	return 0;
}