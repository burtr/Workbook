#
# Makefile for stack-trac
# last-update:
#	9 sep 2021 -bjr: created
#
#

P= simple-stack-trace
Q= stack-hopping

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m


all:
	@echo "\t1. ${GREEN}make stack-trace${NC}"
	@echo "\t2. examine the ${GREEN}run.out${NC} file"
	@echo "\t3. complete the ${GREEN}stack-hopping.c${NC} program"
	@echo "\t4. ${RED}make stack-hop${NC} to hop the stack"
	make clean

stack-trace: $P
	./$P > run.out

stack-hop: $Q
	./$Q

$P: $P.c
	cc -o $@ $<

$Q: $Q.c
	cc -o $@   -fno-stack-protector $<

clean:
	-rm $P $Q  run.out

