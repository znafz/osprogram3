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

int main(int argc, char** argv) {
	pid_t pid, sid;

	pid = fork();

	if (pid < 0) {
		printf("Error!\n");
		exit(1);
	} else if (pid > 0) {
		/* Parent */
		exit(0);
	}
	printf("\nAttempting to daemonize process...\n");

	sid = setsid();		// Sets a new session ID; isolates daemon from terminal
	if (sid < 0) exit(1);

	// Change working directory to root
	if (chdir("/") < 0) exit(1);

	// Close out the standard file descriptors
	//close(STDIN_FILENO);
	//close(STDOUT_FILENO);
	close(STDERR_FILENO);

	printf("Successfully daemonized process.\n\n");

	/* Declarations for memory monitoring */
	int total_mem, free_mem, used_mem;
	int i;
	char * temp;
	char * token;

	FILE *ifp = fopen("/proc/meminfo", "r");
	char c[1000];
	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}
	


	while (1) {
		/* Do stuff to monitor memory */

		/* Before */

		fgets(c, 100, ifp);		// Total memory
		temp = strdup(c);

		for (i = 0; i < 9; i++) token = strsep(&temp, "  ");

		total_mem = atoi(token);
		printf("\tTotal Memory: %d\n", total_mem);

		// Now get free memory
		fgets(c, 100, ifp);
		temp = strdup(c);

		for (i = 0; i < 11; i++) token = strsep(&temp, "  ");

		free_mem = atoi(token);
		printf("\tFree Memory: %d\n", free_mem);

		// Calculate memory in use
		used_mem = total_mem - free_mem;
		printf("\tUsed Memory: %d\n", used_mem);

		sleep(30);	// Wait 30 seconds
	}

	return 0;
}