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
 * author: bjr
 * date: 7 oct 2021
 * pledge: this is my own work, unless otherwise noted
 *
 * this is a template. change "author" and continue work
 *
 * update: 
 *		6 oct 2021 -bjr: created
 *		7 oct 2021 -bjr: added condition variables
 *		7 oct 2021 -bjr: moved monitor code to own file
 */


extern int g_debug ;
extern int g_is_verbose ;

struct ThreadArg * ta_create(int id, struct RingBuf *rb, struct ReaderWriterPlan * rwp ) {
	struct ThreadArg * ta ;
	ta = (struct ThreadArg *) malloc(sizeof(struct ThreadArg)) ;
	assert(ta) ;
	ta->id = id ;
	ta->rwp = rwp ;
	ta->rb = rb ;
	return ta ;
}

void * th_producer(void * arg) {
	struct ThreadArg *ta = (struct ThreadArg *) arg ;
	int i ;
	int num = 0 ;
	char * p ;
	sleep(ta->rwp->delay) ;
	printf("%02d producer starting\n",ta->id ) ;

	for  (i=0; i<ta->rwp->repeat; i++)
		for (p=ta->rwp->cmd; *p; p++) {		
			monitor_enqueue(ta->rb,*p) ;
			num++ ;
			printf("%02d: %d\tenqueue %c\n", ta->id, num, *p) ;	
		}
	monitor_enqueue(ta->rb,'\0') ;
	
	printf("%02d: produced %d items.\n",ta->id, num) ;
	// pthread_exit(NULL);   
	return NULL ; 
}

void * th_consumer(void * arg) {
	struct ThreadArg *ta = (struct ThreadArg *) arg ;
	char ele ;
	int num = 0 ;
	sleep(ta->rwp->delay) ;
	printf("%02d consumer starting\n",ta->id ) ;

	while (1) {
		ele = monitor_dequeue(ta->rb) ;
		if (ele=='\0') {
			ta->rwp->repeat--;
			if (!ta->rwp->repeat) break ;
		}
		else {
			num++ ;
			printf("%02d: %d\tdequeue %c\n", ta->id, num, ele) ;
		}		
	} 

	printf("%02d: consumed %d items.\n", ta->id, num) ;
	// pthread_exit(NULL);   
	return NULL ;
}

/***
 *** ring buffer
 **/
 
struct RingBuf *rb_create(void) {
	struct RingBuf *  rb ;
	rb = (struct RingBuf *) malloc(sizeof(struct RingBuf)) ;
	assert(rb) ;
	memset(rb, 0, sizeof(struct RingBuf)) ;
	pthread_mutex_init(&rb->ring_buf_lock, NULL);
	pthread_cond_init (&rb->ring_buf_cond, NULL);
	return rb ;
}

int rb_ioctl(struct RingBuf *rb, int op) {
	switch (op) {
	case RB_Q_SIZE:
		return RINGBUF_SIZE ;
	case RB_IS_EMPTY:
		return !rb->is_full && (rb->head==rb->tail) ;
	case RB_IS_FULL:
		return rb->is_full ;
	case RB_Q_COUNT:
		if (rb->is_full) return RINGBUF_SIZE ;
		return (rb->head-rb->tail+RINGBUF_SIZE)%RINGBUF_SIZE ;
	default:
		;
	}
	return 0 ;
}

int rb_enqueue(struct RingBuf *rb, int ele) {
	if (rb_ioctl(rb, RB_IS_FULL)) return -1 ;
	rb->ringbuf[rb->head] = ele ;
	rb->head = (rb->head+1) % rb_ioctl(rb, RB_Q_SIZE) ;
	if (rb->head==rb->tail) rb->is_full = (1==1) ;	
 	return ele ;
}

int rb_dequeue(struct RingBuf *rb) {
	if (rb_ioctl(rb, RB_IS_EMPTY)) return -1 ;
	int res = rb->ringbuf[rb->tail] ;
	rb->tail = (rb->tail+1) % rb_ioctl(rb, RB_Q_SIZE) ;
	rb->is_full = (0==1) ;
	return res ;
}

