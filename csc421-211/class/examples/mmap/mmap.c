#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<assert.h>
#include<errno.h>

/*
 * example program to demonstrate memory mapping 
 *
 * author: bjr
 * last-update:
 *     8 nov 2021
 */


#define USAGE_MESSAGE "Usage: %s _filename_\n"
#define PROG_NAME "mmap"

#define KEY_SIZE 16
#define VALUE_SIZE 48
#define KV_PAIR_SIZE (KEY_SIZE+VALUE_SIZE)
#define N_PAIRS 16
#define MMFILE_SIZE (N_PAIRS*KV_PAIR_SIZE)

char * the_keys [] = { "one", "two", "three", "four" } ;
char * the_values [] = { "for the money", "for the show", "to get ready", "to go!" } ;

struct KV_PAIR {
	char key[KEY_SIZE] ;
	char value[VALUE_SIZE] ;
} ;


int print_usage(void) {
	printf(USAGE_MESSAGE,PROG_NAME) ;
	return 0 ;
}

int put_kvpair(struct KV_PAIR * kvp, int index, char * key, char * value ) {
	assert( strlen(key)<KEY_SIZE ) ;
	assert( strlen(value)<VALUE_SIZE ) ;
	memset(kvp+index,0,KV_PAIR_SIZE);
	strcpy(kvp[index].key, key) ;
	strcpy(kvp[index].value, value) ;
	return 0 ;
}

int get_kvpair(struct KV_PAIR * kvp, int index, char * kv_buf, int buf_len) {
	assert (buf_len==KV_PAIR_SIZE) ;
	memcpy( kv_buf, kvp+index, sizeof(struct KV_PAIR)) ;
	return 0 ;
}


int main(int argc, char * argv[]) {
	int ch ;
	int is_verbose = 0 ;
	char * mmap_name ;
	struct stat stat_struct ;
	int mmap_id ;
	void * mmap_mm ;
	struct KV_PAIR * kvp_a ;
	char kvp_buf[KV_PAIR_SIZE] ;
	struct KV_PAIR * kvp ;
	int i ;
	
	while ((ch = getopt(argc, argv, "v")) != -1) {
		switch(ch) {
		case 'v':
			is_verbose ++ ;
			break ;
		case '?':
		default:
			return( print_usage()) ;
		}
	}
	argc -= optind;
	argv += optind;
	if ( argc!=1 ) {
		return( print_usage()) ;
	}

	// open and memory map the file
	mmap_name = strdup(argv[0]) ;
	mmap_id = open(mmap_name, O_RDWR ) ;
	assert (mmap_id>1) ;
	assert( fstat(mmap_id,&stat_struct)!=-1 ) ;
	assert( stat_struct.st_size==MMFILE_SIZE) ;
	mmap_mm = mmap(NULL, stat_struct.st_size , PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED,  mmap_id, 0 ) ;
	assert ( mmap_mm != MAP_FAILED ) ;

	kvp_a = (struct KV_PAIR *) mmap_mm ; 
	kvp = (struct KV_PAIR *) kvp_buf ;

	for (i=0; i<sizeof(the_keys)/sizeof(the_keys[0]); i++) {
		put_kvpair(kvp_a, i, the_keys[i], the_values[i]) ;
	}
	for (i=0; i<sizeof(the_keys)/sizeof(the_keys[0]); i++) {
		get_kvpair(kvp_a, i, kvp_buf, sizeof(kvp_buf) ) ;
		printf("kv pair number %d\n\tkey: %s\n\tvalue: %s\n", i, kvp->key, kvp->value ) ;
	}
	return 0 ;
	
}

