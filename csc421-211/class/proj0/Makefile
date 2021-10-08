#
# makefile for hello world project
# author: bjr
# date: 21 aug 2017
# last-update: 
#    21 aug 2020
#    22 aug 2020 bjr; universal for old and new
#


RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m
M= Makefile

H= hello

$H: $H.c
	cc -o $H $H.c

test: $H
	./$H > $H.out
	diff -i $H.out $H.ref
	@echo "*** ${GREEN}PASSED the test ${NC}***"

clean:
	-rm $H $H.out

commit:
	svn commit -m "commit for grade"

