/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   
  Compile with:  gcc -o memhog memhog.c -lm
  Run with:  ./memhog

*/


#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* For exit() function*/

void expensiveFunction(){
	int i;
	float sum = 0;
	for(i = 0; i < 9000; i++)
	{
		int j;
		for(j = 0; j < 9000; j++)
		{
			sum += cos((float)(i))/sin((float)(j));//do some expensive calculations
			malloc(i*j*1000);//allocate to memory
		}
		sum /= cos(sum);
		
	}

	printf("finished expensive function.\n");
}

int main(int argc, char** argv) {

	int pid;
	int numChildren = 2; //change this to change number of forked children
	int procNum;

	for(procNum = 0; procNum < numChildren; procNum++) {
		pid = fork();
		if (pid == 0) {
			break;
		}
	}

	if (pid == 0) {
		expensiveFunction();
	}
	else {
		exit(1);
	}
	/*expensiveFunction();*/
    return 0;
}
