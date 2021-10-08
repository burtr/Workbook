#
# makefile for semaphore project, csc421-221
# last-update:
#    6 oct 2021 -bjr: 
# 

COPTS=
# these were for my code, not important for yours -bjr
#S= COND_SYNC
#S= ONLY_SYNC
#S= NO_SYNC

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m

build:
	make prod-cons

prod-cons: prod-cons.c prod-cons-sub.o monitor.o prod-cons.h
	cc ${COPTS} -o $@ prod-cons-sub.o monitor.o $<

prod-cons-sub.o: prod-cons-sub.c prod-cons.h
	cc ${COPTS}  -D $S -c -o $@ $<

monitor.o: monitor.c prod-cons.h
	cc ${COPTS}  -D $S -c -o $@ $<

test1: prod-cons
	./prod-cons  -v -w 2 1 1 abcdefghijklmnopqrstuvwxyz 1 1 ABCDEFGHIJKLMNOPQRSTUVWXYZ  2 
	@echo "*** ${GREEN}RUN complete ${NC}***"

test2: prod-cons
	./prod-cons  -v -w 2 5 1 Z 1 1 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY 2 2
	@echo "*** ${GREEN}RUN complete ${NC}***"
	
test3: prod-cons
	./prod-cons  -v -w 2 1 2 abcdefghijklmnopqrstuvwxyz 1 1 ABCDEFGHIJKLMNOPQRSTUVWXYZ  3 3
	@echo "*** ${GREEN}RUN complete ${NC}***"

count:
	make test1 | python3 count_items.py
	make test2 | python3 count_items.py
	make test3 | python3 count_items.py
	@echo "*** ${RED}CHECK that produced equals consumed.${NC}***"

clean:
	-rm prod-cons prod-cons-sub.o monitor.o


