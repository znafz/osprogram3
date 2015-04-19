/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   
  Compile with:  gcc -o task1 task1.c
  Run with:  ./task1

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
	printf("testing ping\nBefore:\n\t");
   fgets(c,100,ifp);
   fgets(c,100,ifp);
   printf("%s",c);

   //start some process
   
   if(fork() == 0){
	   
	   execv("ping", "ping google.com");
	   
   } else{

	   sleep(1);//sleep a little so it doesn't check memory until after the process has been running a bit
	   //rewind to the beginning of meminfo and read again
	   printf("After:\n\t");
	   rewind(ifp);
	   fgets(c,100,ifp);
	   fgets(c,100,ifp);
	   printf("%s",c);


	   fclose(ifp);
   }

    return 0;
}
