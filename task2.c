/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   
  Compile with:  gcc -o task2 task1.c
  Run with:  ./task2

*/

#include <stdio.h>
#include <stdlib.h> /* For exit() function*/

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


   //start some processes
   
   if(fork() == 0){
	   printf("executing process 1..\n");
	   execv("ping", "ping google.com");
	   
   } else{
	   
	   if(fork() == 0){
		   usleep(1000000);//1 million microseconds =  1 second
		   printf("executing process 2..\n");
		   execv("ping", "ping youtube.com");
	   
	   } else{
		   
			   if(fork() == 0){
					usleep(2000000);
					printf("executing process 3..\n");
					execv("ping", "ping facebook.com");
	   
		   } else{

			   //check the first process
			   usleep(500000);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 1 starts:\n");
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

			   //check the second process
			    usleep(1000000);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 2 starts:\n");
			   rewind(ifp);
			   fgets(c,100,ifp);
			   fgets(c,100,ifp);
			   temp = strdup(c); 
			   for(i=0; i < 11; i++)
					token = strsep(&temp, "  "); // had to repeat strsep for some reason
			   free_mem = atoi(token);
			   printf("\tFree Memory: %d\n", free_mem);

			   //calculate memory in use
			   old_used_mem = used_mem;
			   used_mem = total_mem - free_mem;
			   printf("\tUsed Memory: %d\n", used_mem);
			   printf("\tMemory Used By Process: %d\n", used_mem-old_used_mem);

			   //check the third process
			   usleep(1000000);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 3 starts:\n");
			   rewind(ifp);
			   fgets(c,100,ifp);
			   fgets(c,100,ifp);
			   temp = strdup(c); 
			   for(i=0; i < 11; i++)
					token = strsep(&temp, "  "); // had to repeat strsep for some reason
			   free_mem = atoi(token);
			   printf("\tFree Memory: %d\n", free_mem);

			   //calculate memory in use
			   old_used_mem = used_mem;
			   used_mem = total_mem - free_mem;
			   printf("\tUsed Memory: %d\n", used_mem);
			   printf("\tMemory Used By Process: %d\n", used_mem-old_used_mem);

		  }
	   }
   }

    fclose(ifp);
    return 0;
}
