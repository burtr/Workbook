#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<ctype.h>
// Compile and link with -pthread.
#include <pthread.h>
#include "prod-cons.h"


/*
 * author: 
 * date: 
 * pledge: this is my own work, unless otherwise noted
 *
 * this is a template. 
 *
 * update: 
 *		7 oct 2021 -bjr: code that is not thread safe
 */

// https://hpc-tutorials.llnl.gov/posix/creating_and_terminating/


// this code is not thread safe. use 
// 1) use pthread_mutex_lock and pthread_mutex_unlock 
//    to make it safe and live.
// 2) use pthread_cond_wait and either pthread_cond_signal or pthread_cond_broadcast
//    to make it safe, live with efficient waits for both producer and consumer.


extern int g_debug ;
extern int g_is_verbose ;

int monitor_enqueue(struct RingBuf *rb, int ele) {

	while (rb_ioctl(rb,RB_IS_FULL)) ;
	rb_enqueue(rb,ele) ;		
	return ele ;

}

int monitor_dequeue(struct RingBuf *rb) {

	int ele ;
	while (rb_ioctl(rb,RB_IS_EMPTY)) ;
	ele = rb_dequeue(rb) ;
	return ele ;

}


