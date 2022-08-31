#
# accelerate! GPU
# csc596 (231) fall 2022-2023
# proj2 makefile
#
# last-update:
#	30 aug 2022 -bjr: 
#
#

H= cryptanthus
H= lutheria
H= androlepis
H= orthophytum

L=/usr/local/cuda/bin
GIT_NAME= __YOUR_GITHUB_NAME__

P= vector-mult

VERBOSE= -DIS_VERBOSE
N_ELEM= -DN_ELEM=5

test: 
	make clean
	make $P
	make test-mult
	
$P: $P.cu
	$L/nvcc ${N_ELEM} ${VERBOSE} -lm -o $P $P.cu

test-mult: $P
	./$P

login:
	ssh $H

clean:
	-rm $P
