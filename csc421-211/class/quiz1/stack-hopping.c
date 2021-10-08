#include<stdio.h>
#include<stdlib.h>

/*
 * stack hopping template 
 * last-update:
 *	9 sept 2021 -bjr: modified from stack-trace
 *
 */

#define DEPTH 6
#define AT_HOP 2

int h() {
	printf("stack hopped!\n") ;
	exit(0 ;
}

int f(int n) {
	int i = n ;
	printf("downwards:  %d\n",n) ;
	if ( n ) f(n-1) ;
	printf("upwards:  %d\n",n) ;
	//
	// HACK THE STACK HERE
	//    hint: use "h" as a value, and "&i" as a pointer to 
	//          some place in the stack.
	//
	return 0 ;
}

int main(int argc, char * argv[]) {
	f(DEPTH) ;
	return 0 ;
}


