/*
 * name: bjr
 * date: 6 oct 2021
 *
 * header file for the producer consumer project
 */
 
#include <pthread.h>

extern int g_debug ;
extern int g_is_verbose ;

struct ReaderWriterPlan {
	char * cmd ;		// the letters to enqueue, NULL for reader.
	int repeat ;		// the number of repetitions of cmd, number endmarkers for reader.
	int delay ;			// seconds delay to thread start
} ;

struct ThreadArg {
	int id ;
	struct ReaderWriterPlan * rwp ;
	struct RingBuf * rb ;
} ;

#define RINGBUF_SIZE 16
#define RB_Q_SIZE 0
#define RB_IS_EMPTY 1
#define RB_IS_FULL 2
#define RB_Q_COUNT 3

struct RingBuf {
	pthread_mutex_t ring_buf_lock ;
	pthread_cond_t ring_buf_cond ;
	int head ;
	int tail ;
	int is_full ;
	char ringbuf[RINGBUF_SIZE] ;
} ;


int monitor_enqueue(struct RingBuf *, int ele) ;
int monitor_dequeue(struct RingBuf *) ;


struct ThreadArg * ta_create(int id, struct RingBuf * , struct ReaderWriterPlan * ) ;
void * th_producer(void * arg) ;
void * th_consumer(void * arg) ;

struct RingBuf *rb_create(void) ;
int rb_ioctl(struct RingBuf *rb, int op) ; 
int rb_enqueue(struct RingBuf *rb, int ele) ;
int rb_dequeue(struct RingBuf *rb) ;

