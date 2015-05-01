/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:
  Compile with:  gcc -o freemem freemem.c
  Run with:  ./freemem

  */


#include <stdio.h>
#include <stdlib.h> /* For exit() function*/

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

	//first open meminfo
	FILE *ifp = fopen("/proc/meminfo", "r");

	if (ifp == NULL) {
		printf("Error opening file");
		exit(1);         /* Program exits if file pointer returns NULL. */
	}

	int total_mem, free_mem, used_mem;

	//read out the free memory
	total_mem = get_file_value(ifp, 0);
	printf("\tTotal Memory: %d\n", total_mem);

	//now get free memory
	free_mem = get_file_value(ifp, 1);
	printf("\tFree Memory: %d\n", free_mem);

	//calculate memory in use
	used_mem = total_mem - free_mem;
	printf("\tUsed Memory: %d\n", used_mem);


	fclose(ifp);
	return 0;
}
