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

   //read out the free memory
	printf("\nFree Memory Before:\n\t");
   fgets(c,100,ifp);
   fgets(c,100,ifp);
   printf("%s",c);

   //start some processes
   
   if(fork() == 0){
	   
	   execv("ping", "ping google.com");
	   
   } else{

	   if(fork() == 0){
		   sleep(1.9);
		   execv("ping", "ping youtube.com");
	   
	   } else{

			   if(fork() == 0){
			   sleep(2.9);
			   execv("ping", "ping facebook.com");
	   
		   } else{

			   //check the first process
			   sleep(1);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 1 starts:\n\t");
			   rewind(ifp);
			   fgets(c,100,ifp);
			   fgets(c,100,ifp);
			   printf("%s",c);

			   //check the second process
			    sleep(1);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 2 starts:\n\t");
			   rewind(ifp);
			   fgets(c,100,ifp);
			   fgets(c,100,ifp);
			   printf("%s",c);

			   //check the third process
			   sleep(1);//sleep a little so it doesn't check memory until after the process has been running a bit
			   //rewind to the beginning of meminfo and read again
			   printf("After Process 3 starts:\n\t");
			   rewind(ifp);
			   fgets(c,100,ifp);
			   fgets(c,100,ifp);
			   printf("%s",c);

		  }
	   }
   }

    fclose(ifp);
    return 0;
}
