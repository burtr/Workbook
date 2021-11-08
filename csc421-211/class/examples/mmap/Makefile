#
# makefile for mmap example
# author: bjr
# last update: 
#	8 nov 2021
#


MF= -f Makefile
MMFILE= l0.dat
MMFILE_SIZE= 1024

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m
DOT=  | head -2 | tail -n +2
NODOT= | tail -n +2


all:
	make ${MF} test
	
mmap: mmap.c
	cc -o $@ $<  
	
${MMFILE}:
	dd if=/dev/zero of=$@ bs=1 count=${MMFILE_SIZE}

test: mmap ${MMFILE}
	./mmap -v ${MMFILE}
	hexdump -C ${MMFILE}

clean:
	-rm ${MMFILE} mmap

