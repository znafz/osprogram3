/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   
  Compile with:  gcc -o task1 task1.c
  Run with:  ./task1

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* For exit() function*/

void expensiveFunction(int x){
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

int main(int argc, char** argv) {

	//first open meminfo
    FILE *ifp = fopen("/proc/meminfo", "r");
	char c[1000];
    if (ifp==NULL){
       printf("Error opening file");
       exit(1);         /* Program exits if file pointer returns NULL. */
   }

   //read out the free memory
	int total_mem, free_mem, used_mem;
	char * temp;
	char * token;
	printf("testing ping\nBefore:\n");
   fgets(c,100,ifp);//total memory
   temp = strdup(c);
   int i;
   for(i=0; i < 9; i++)
		token = strsep(&temp, "  "); // had to repeat strsep for some reason
   total_mem = atoi(token);
   printf("\tTotal Memory: %d\n", total_mem);


   //now get free memory
   fgets(c,100,ifp);
   temp = strdup(c); 
   for(i=0; i < 11; i++)
		token = strsep(&temp, "  "); // had to repeat strsep for some reason
   free_mem = atoi(token);
   printf("\tFree Memory: %d\n", free_mem);

   //calculate memory in use
   used_mem = total_mem - free_mem;
   printf("\tUsed Memory: %d\n", used_mem);

   //start some process
   
   if(fork() == 0){
	   
	   expensiveFunction(1);
	   
   } else{

	   usleep(10000);//sleep a little so it doesn't check memory until after the process has been running a bit
	   //rewind to the beginning of meminfo and read again
	   printf("After:\n");
	   rewind(ifp);
	   fgets(c,100,ifp);
	   fgets(c,100,ifp);
	   temp = strdup(c); 
	   for(i=0; i < 11; i++)
			token = strsep(&temp, "  "); // had to repeat strsep for some reason
	   free_mem = atoi(token);
	   printf("\tFree Memory: %d\n", free_mem);

	   //calculate memory in use
	   int old_used_mem = used_mem;
	   used_mem = total_mem - free_mem;
	   printf("\tUsed Memory: %d\n", used_mem);
	   printf("\tMemory Used By Process: %d\n", used_mem-old_used_mem);

	   


	  
   }

    fclose(ifp);
    return 0;
}
