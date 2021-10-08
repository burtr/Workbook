#!/bin/bash

#
# Makefile for Project 2
# csc421-201
# author: bjr
# last revision: 16 oct 2019
#

KHR=/usr/src/linux-source-4.4.0
LS=./linux-source-4.4.0

M= -f Makefile

all:
	@echo "All action roll-up"
	make $M dist-clean
	make $M mysyslog
	make $M test-mysyslog
	make $M evidence
	make $M clean

uname-out:
	uname -a > uname.out

mysyslog: mysyslog.c mysyscalls.h
	cc -o $@ $<

test-mysyslog: mysyslog
	./mysyslog "hello kernel!"
	echo $$? > mysyslog.out
	tail /var/log/syslog | grep "my_syslog:" | tail -n 1 >> mysyslog.out

evidence:
	make $M test-mysyslog
	cp mysyslog.out evidence.out
	uname -a >> evidence.out
	tar cvf evidence.tar evidence.out -C ${KHR} \
		${LS}/kernel/Makefile \
		${LS}/include/linux/syscalls.h \
		${LS}/arch/x86/entry/syscalls/syscall_32.tbl \
		${LS}/kernel/mysyscalls.c ${LS}/kernel/mysyscalls.h

untar:
	tar xvf evidence.tar

clean:
	-rm mysyslog mysyslog.out
	-rm evidence.out
	-rm -r ./${LS}

dist-clean:
	make $M clean
	-rm evidence.tar

