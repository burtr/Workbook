#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>

#include "ringbuf.h"

/*
 * author: 
 * date: 
 * pledge: this is my own work, unless otherwise noted
 *
 * update: 
 */


/* static variables (zeroed) */

int g_debug = 0 ;
int is_verbose = 0 ;
struct RingBuf rb ;

int rb_ioctl(int op) {
	switch (op) {
	case RB_Q_SIZE:
		return RINGBUF_SIZE ;
	case RB_IS_EMPTY:
		return 1 ;
	case RB_IS_FULL:
	case RB_Q_COUNT:
	default:
		;
	}
	return 0 ;
}

int rb_enqueue(int ele) {
	/* given element ele of type char, enqueues on the ring buffer.
	   if successful return ele, else return -1.
	*/
	return 0 ;
}

int rb_dequeue(void) {
	/* dequeue on the ring buffer.
	   if successful return ele, else return -1.
	*/
	return -1 ;
}

