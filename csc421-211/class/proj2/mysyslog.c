/*
 * mysyslog.c
 *
 * implements the mysyslog command, taking the command line argument and sending it
 * to the syslog using our new my_syslog system call.
 *
 * author: burt
 * created: sep 2015
 * updated: 13 sep 2016
 *
 * returns the error value of syscall and command result
 *
 */
 
#include<unistd.h>
#include<stdio.h>
#include "mysyscalls.h"

#define USAGE "mysyslog _message_"

int main(int argc, char * argv[]) {
	if (argc!=2) {
		printf("%s\n", USAGE) ;
		return 0 ;
	}
	return syscall(MY_SYSLOG, argv[1]) ;
}

