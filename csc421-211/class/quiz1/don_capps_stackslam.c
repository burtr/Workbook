#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
/*
 * Don.Capps@netapp.com
 *
 */
 
void sub1(int);
void sub2(void);
char save_space[4] ;
char * save  = save_space ;

#define OFFSET 3

int main(int argc, char **argv) {
	sub1(1);
	printf("Hello world\n");
	exit(0);
}


void sub2(void) {
	long y[1];
	y[OFFSET]= (long)save;
	printf("How did I get here ?\n");
}

void sub1(int one) {
	long x[1];
	save = (char *)x[OFFSET];
	x[OFFSET]=(long)sub2;
	return;
}
