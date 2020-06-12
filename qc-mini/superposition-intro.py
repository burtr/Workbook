#!/usr/bin/env python3

from qiskit import QuantumCircuit, execute, Aer, IBMQ
from qiskit.compiler import transpile, assemble
from qiskit.tools.jupyter import *
from qiskit.visualization import *
from qiskit.providers.jobstatus import JOB_FINAL_STATES, JobStatus
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, execute, Aer
import time
import argparse


#
# superposition-intro.py
# Quantum circuit to demonstrate superposition
#
# author: burt rosenberg
# date: 12 june 2020
# last update:
#

args_g = 0  # args are global

def load_or_save_IBMQ_account(api_token=None):
	if api_token:
		# only needs to be done once
		IBMQ.save_account(api_token)
	provider = IBMQ.load_account()
	return provider

def wait_for_job(backend, job, wait_interval=5):
	retrieved_job = backend.retrieve_job(job.job_id())
	start_time = time.time()
	job_status = job.status()
	while job_status not in JOB_FINAL_STATES:
		if not args_g.unverbose:
			print(f'Status @ {time.time() - start_time:0.0f} s: {job_status.name},'
			  f' est. queue position: {job.queue_position()}')
		time.sleep(wait_interval)
		job_status = job.status()

def list_backends(backends):
	print('backends available:')
	for be in backends:
		st = be.status()
		if st.operational:
			print(f'\t{be.name()}, pending jobs:{st.pending_jobs}')

def match_backend_name(be, be_s,min_len=3):
	if len(be)<3:
		return ""
	for be_t in be_s:
		if be in be_t:
			return be_t
	return ""

def parse_args():
	parser = argparse.ArgumentParser(description="Quantum circuit to demonstrate superposition")
	parser.add_argument('backend', nargs='?', help='ibmq backend name or partial name')
	parser.add_argument("-L", "--list_backends", action="store_true", help="list the available backends")
#	parser.add_argument("-o", "--output_drawing", help="output drawing of the circuit")
	parser.add_argument('-v', '--verbose', action='store_true', help='verbose output')
	parser.add_argument('-V', '--unverbose', action='store_true', help='silent output')
	return parser.parse_args()

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
