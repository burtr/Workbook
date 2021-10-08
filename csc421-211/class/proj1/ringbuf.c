#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>

#include "ringbuf.h"

/*
 * author: bjr
 * date: 5 sep 2016
 * pledge: this is my own work, unless otherwise noted
 *
 * this is a template. change "author" and continue work
 *
 * update: 
 */


/* globals go here */
extern int g_debug ;
extern int is_verbose ;

/* defines go here, in SHOUTY_CASE */
#define USAGE_MESSAGE "usage: ringbuf [-v] _commands_"

int main(int argc, char * argv[]) {

	int is_verbose = 0 ;
	int ch ;
	char * ops ;
	int res ;

	while ((ch = getopt(argc, argv, "v")) != -1) {
		switch(ch) {
			case 'v':
				is_verbose = 1 ;
				break ;
			default:
				printf("%s\n", USAGE_MESSAGE) ;
				return 0 ;
		}
	}
	argc -= optind;
	argv += optind;

	/* example of an assertion */
	assert(is_verbose==0 || is_verbose==1) ;

	if ( is_verbose ) {
		printf("%s:%d argc=%d\n", __FILE__, __LINE__, argc) ;
		if (argc!=0) {
			printf("%s:%d argument = |%s|\n", 
				__FILE__, __LINE__, argv[0] ) ;
		}
		printf("%s:%d ringbuffer size = %d\n",
				__FILE__, __LINE__, rb_ioctl(RB_Q_SIZE) ) ;
	}

	if (!argc) {
		printf("%s\n", USAGE_MESSAGE) ;
		return 0 ;
	}

	ops = argv[0] ;
	while (*ops) {
		switch (*ops) {
		case '-':
			// ** HINT: res should be the result of a call to rb_dequeue
			res = -1 ;
			// **
			if ( res==-1 ) {
				printf("deq: empty\n") ;
			} 
			else {
				printf("deq: %c\n", res) ;
			}
			break ;
		case '+':
			printf("ioc: %d %d %d %d\n", 
				// ** HINT: the first -1 is replaced by rb_iotcl(RB_Q_SIZE)
				-1, -1, -1, -1 ) ;
				// **
			break ;
		default:
			// ** HINT: the next line is replaced by a call to rb_enqueue. the character
			//    to enqueue is pointed to by ops.
			res = -1 ;
			// **
			if ( res==-1 ) {
				printf("enq: full\n") ;
			}
			else {
				printf("enq: %c\n", *ops) ;
			}
		}
		// ** HINT: the next line should increment the character pointer ops
		ops ;
		// **
	}

	return 0 ;
}

