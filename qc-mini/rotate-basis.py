#!/usr/bin/env python3

from qiskit import QuantumCircuit, execute, Aer, IBMQ
from qiskit.compiler import transpile, assemble
from qiskit.tools.jupyter import *
from qiskit.visualization import *
from qiskit.providers.jobstatus import JOB_FINAL_STATES, JobStatus
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, execute, Aer
import time, math, argparse
from qc_helpers import *


#
# rotate-basis.py
# 
# author: burt rosenberg
# date: 17 june 2020
# last update:
#

# args_g = 0  # args are global



def main(argv):
	global args_g
	args_g = parse_args()

	if not args_g.unverbose: print('Opening account ... ')
	provider = load_or_save_IBMQ_account()
	backends = provider.backends()

	if args_g.list_backends or args_g.backend is  None:
		print('Backend required: possible backends are:')
		list_backends(backends)
		exit(0)
	
	backend = match_backend_name(args_g.backend, [be.name() for be in backends], min_len=4)
	if len(backend)==0:
		print(f'Backend |{args_g.backend}| not found.')
		list_backends(backends)
		exit(0)
	backend = provider.get_backend(backend)

	
	
	for a in [i * math.pi/3.0 for i in range(7)]:
		qc = QuantumCircuit(1,1)
		qc.ry(a,0)
		qc.measure(0, 0)
		
		if args_g.verbose:
			print('\n-------- CIRCUIT ---------')
			print(qc.draw(output='text'))
			print('-------------------------\n')

		qobj = assemble(transpile(qc, backend=backend), backend=backend)
		
		if not args_g.unverbose: 
			print(f'Running job on backend: |{backend}|')
	
	
		job = backend.run(qobj)
		retrieved_job = backend.retrieve_job(job.job_id())

		wait_for_job(backend, job)
		result = job.result()
		r = result.get_counts()
		for k in r:
			r[k] = [r[k]/1024.0]
		if not args_g.unverbose: 
			print(f'results: {r}')
		else:
			print(result.get_counts())

main(sys.argv)
