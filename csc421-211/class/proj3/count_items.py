import re, os, sys

#
# small program to help sum up the results of the
# semaphore program output
#
# author: bjr
# last-update: 7 oct 2021
#

def main():
	
	prod = 0 
	cons = 0
	print(f'threads: ',end='')
	for line in sys.stdin:
		m = re.search('.*produced (\d+) items',line)
		if m:
			print(f'+{m[1]}',end='')
			prod += int(m[1])
		m = re.search('.*consumed (\d+) items',line)
		if m:
			print(f'-{m[1]}',end='')
			cons += int(m[1])
	print(f'\nsummary: {prod} items produced and {cons} items consumed')

main()

		