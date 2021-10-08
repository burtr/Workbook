#include<stdio.h>
#include<stdlib.h>

/*
 * simple stack frame trace program
 * last-update:
*	9 sept 2021 -bjr: modified from stack-trace
 *
 */

#define DEPTH 6
#define TRACE_DEPTH 100

int g(int d) {
	int i = d ;
	int * ip = &i ;
	ip += d ;
	for ( ; i>=0; i-- )  {
		printf("%p  0x%08x\n", ip, *ip) ;
		ip -= 1 ;
	}
	printf("done\n") ;
	return 0 ;
}

int f(int n) {
	int i = n ; // force non-register parameter passing
	printf("downwards:  %d\n",n) ;
	if ( n ) f(n-1) ;
	else g(TRACE_DEPTH) ;
	printf("upwards:  %d\n",n) ;
	return 0 ;
}

int main(int argc, char * argv[]) {
	f(DEPTH) ;
	return 0 ;
}


