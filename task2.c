/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   
  Compile with:  gcc -o task2 task1.c -lm
  Run with:  ./task2

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

void expensiveFunction(int x){ //same expensive function as task 1
	int i;
	float sum = 0;
	for(i = 0; i < 5000; i++)
	{
		int j;
		for(j = 0; j < 5000; j++)
		{
			sum += cos((float)(i))/sin((float)(j));
		}
		sum /= cos(sum);
	}
	printf("finished expensive function %d.\n", x);
}

void expensiveFunction2(int x){ //so we can make unidentical children
	int i;
	float sum = 0;
	for(i = 0; i < 5000; i++)
	{
		int j;
		for(j = 0; j < 5000; j++)
		{
			sum += sin((float)(i))/cos((float)(j));
		}
		sum /= cos(sum);
	}
	printf("finished expensive function %d.\n", x);
}

int main(int argc, char** argv) {

	//first open meminfo
    FILE *ifp = fopen("/proc/meminfo", "r");
	char c[1000];
    if (ifp==NULL){
       printf("Error opening file");
       exit(1);         /* Program exits if file pointer returns NULL. */
   }

   int total_mem, free_mem, used_mem;
	char * temp;
	char * token;
	printf("Memory Before:\n");
   total_mem = get_file_value(ifp, 0);		// Total Memory
	free_mem = get_file_value(ifp, 1);		// Free Memory
   printf("\tTotal Memory: %d\n", total_mem);
   printf("\tFree Memory: %d\n", free_mem);

   //calculate memory in use
   used_mem = total_mem - free_mem;
   printf("\tUsed Memory: %d\n", used_mem);


   //start some processes
   
   if(fork() == 0){ //all 3 forks 
	   printf("executing process 1..\n");
	   expensiveFunction(1);
	   
   } else{
	   
	   if(fork() == 0){
		   usleep(1000000);//1 million microseconds =  1 second
		   printf("executing process 2..\n");
		   expensiveFunction2(2);
	   
	   } else{
		   
			   if(fork() == 0){
					usleep(2000000);
					printf("executing process 3..\n");
					expensiveFunction(3);
	   
		   } else{

			   //check the first process
			   usleep(500000);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 1 starts:\n");

				free_mem = get_file_value(ifp, 1);		// Free Memory
			   printf("\tTotal Memory: %d\n", total_mem);
			   printf("\tFree Memory: %d\n", free_mem);
			   used_mem = total_mem - free_mem;
			   printf("\tUsed Memory: %d\n", used_mem);


			   //check the second process
			    usleep(1000000);//sleep a little so it doesn't check memory until after the process has been running a bit
				
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 2 starts:\n");
			   free_mem = get_file_value(ifp, 1);		// Free Memory
			   printf("\tTotal Memory: %d\n", total_mem);
			   printf("\tFree Memory: %d\n", free_mem);
			   used_mem = total_mem - free_mem;
			   printf("\tUsed Memory: %d\n", used_mem);

			   //check the third process
			   usleep(1000000);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   free_mem = get_file_value(ifp, 1);		// Free Memory
			   printf("\tTotal Memory: %d\n", total_mem);
			   printf("\tFree Memory: %d\n", free_mem);
			   used_mem = total_mem - free_mem;
			   printf("\tUsed Memory: %d\n", used_mem);

		  }
	   }
   }

    fclose(ifp);
    return 0;
}
