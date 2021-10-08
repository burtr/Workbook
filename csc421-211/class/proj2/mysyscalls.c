#include<linux/kernel.h>
#include<linux/syscalls.h>

/*
 * kernel/mysyscalls.c
 *
 * this is a template of the file that goes into the kernel
 *
 * it implements the system calls that will be required
 * to complete the csc421 projects.
 *
 * author:
 * date:
 *
 */

#include "mysyscalls.h"

asmlinkage long sys_my_syslog(const char * msg) {
	printk(KERN_ALERT "my_syslog: %s\n", msg) ;
	return 0 ;
}

