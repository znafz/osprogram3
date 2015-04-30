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
   
  
    fclose(ifp);
    return 0;
}
