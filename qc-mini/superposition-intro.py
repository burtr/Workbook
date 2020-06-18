#!/usr/bin/env python3

from qiskit import QuantumCircuit, execute, Aer, IBMQ
from qiskit.compiler import transpile, assemble
from qiskit.tools.jupyter import *
from qiskit.visualization import *
from qiskit.providers.jobstatus import JOB_FINAL_STATES, JobStatus
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, execute, Aer
import time
import argparse
from qc_helpers import *

#
# superposition-intro.py
# Quantum circuit to demonstrate superposition
#
# author: burt rosenberg
# date: 12 june 2020
# last update:
#


def main(argv):
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


	# make the circuit
	q = QuantumRegister(1)
	c = ClassicalRegister(1)
	superposition_state = QuantumCircuit(q, c)
	superposition_state.h(q)
	superposition_state.measure(q, c)

	if args_g.verbose:
		print('\n-------- CIRCUIT ---------')
		print(superposition_state.draw(output='text'))
		print('-------------------------\n')

#	removed for security reasons
#	if args_g.output_drawing:
#		superposition_state.draw(output='mpl').savefig(args_g.output_drawing, dpi=150)

	if not args_g.unverbose: 
		print(f'Running job on backend: |{backend}|')
	backend = provider.get_backend(backend)
	qobj = assemble(transpile(superposition_state, backend=backend), backend=backend)
	job = backend.run(qobj)
	retrieved_job = backend.retrieve_job(job.job_id())

	wait_for_job(backend, job)
	result = job.result()
	if not args_g.unverbose: 
		print(f'results: {result.get_counts()}')
	else:
		print(result.get_counts())

main(sys.argv)

# ran on 28 april 2020
# program prints:
# Status @ 1 s: RUNNING, est. queue position: None
# Status @ 6 s: RUNNING, est. queue position: None
# Status @ 11 s: RUNNING, est. queue position: None
# {'1': 568, '0': 456}
