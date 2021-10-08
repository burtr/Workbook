#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
// Compile and link with -pthread.
#include <pthread.h>

#include "prod-cons.h"


/*
 * author: bjr
 * date: 5 sep 2016
 * pledge: this is my own work, unless otherwise noted
 *
 * update: 
 *		7 oct 2021 -bjr: initial release 
 */


int g_debug ;
int g_is_verbose ;

#define USAGE_MESSAGE "usage: prod-cons [-v] -w n_writers writer-delay writer-repeat writer-cmd ... reader-delay ..."


int num_threads(int n_args, int n_writers) {
	// given the number of command line arguments, and the number
	// of writers, calculates the number of threads
	// also performs checks related to allowable reader and writer numbers
	
	int n_readers = n_args - 3 * n_writers ;
	if (n_writers<1) return -1 ;
	if (n_readers<1) return -1 ;
	if (n_readers>n_writers) return -1 ;
	return n_writers + n_readers ;
}

struct ReaderWriterPlan * rwp_parse(char ** cl, int n, int w) {
	struct ReaderWriterPlan * rwp ;
	int i, j ;
	rwp = (struct ReaderWriterPlan *) 
		malloc(n*sizeof(struct ReaderWriterPlan)) ;
	assert(rwp) ;
	
	j = 0 ; 
	for (i=0;i<w;i++) {
		// parse writers
		rwp[i].delay = atoi(cl[j++]) ;
		rwp[i].repeat = atoi(cl[j++]) ;
		rwp[i].cmd = cl[j++] ;
	}
	for (i=w;i<n;i++) {
		// parse readers
		rwp[i].cmd = NULL ;
		rwp[i].delay = atoi(cl[j++]) ;
		rwp[i].repeat = 1 ;
	}
	// last reader waits for any excess write stop signals
	rwp[n-1].repeat = 2*w-n+1;

	return rwp ;
}

void print_rwp(struct ReaderWriterPlan * rwp, int n) {
	int i ;
	for (i=0;i<n;i++) {
		if (rwp[i].cmd)
			printf("%2d: delay: %2d, repeat: %2d, writer: %s\n",
				i, rwp[i].delay, rwp[i].repeat, rwp[i].cmd) ;
		else
			printf("%2d: delay: %2d, repeat: %2d, reader\n",
				i, rwp[i].delay, rwp[i].repeat) ;
	}
}

int main(int argc, char * argv[]) {

	int ch, res, i, rc ;
	char * ops ;
	pthread_t p_th ;
	struct RingBuf *rb ;
	struct ThreadArg *ta ;
	struct ReaderWriterPlan * rwp ;
	int n_threads ;
	int n_writers = 0 ;
 
	while ((ch = getopt(argc, argv, "vw:")) != -1) {
		switch(ch) {
			case 'v':
				g_is_verbose = 1 ;
				break ;
			case 'w':
				n_writers = atoi(optarg) ;
				break ;
			default:
				printf("%s\n", USAGE_MESSAGE) ;
				return 0 ;
		}
	}
	argc -= optind;
	argv += optind;
	
	n_threads = num_threads(argc,n_writers) ;
	if ( n_threads==-1) {
		printf("%s\n", USAGE_MESSAGE) ;
		return 0 ;
	}

	rwp = rwp_parse(argv,n_threads,n_writers) ;
	if (g_is_verbose) print_rwp(rwp,n_threads) ;
	rb = rb_create() ;
		
	for (i=0;i<n_threads;i++) {
		ta = ta_create(i, rb, rwp+i) ;
		if (rwp[i].cmd==NULL)
			rc = pthread_create(&p_th, NULL, th_consumer, (void *) ta ) ;
		else
			rc = pthread_create(&p_th, NULL, th_producer, (void *) ta ) ;
	}

	if (g_is_verbose) printf("waiting for threads to exit ...\n") ;
	pthread_exit(NULL);  // block until all threads but this have exited
	return 0 ;
}

