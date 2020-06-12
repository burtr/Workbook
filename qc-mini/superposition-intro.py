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
# date: may 2020
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
		if args_g.verbose:
			print(f'Status @ {time.time() - start_time:0.0f} s: {job_status.name},'
			  f' est. queue position: {job.queue_position()}')
		time.sleep(wait_interval)
		job_status = job.status()

def parse_args():
	parser = argparse.ArgumentParser(description="Quantum circuit to demonstrate superposition")
	parser.add_argument('-b','--backend', help='ibmq backend')
	parser.add_argument("-L", "--list_backends", action="store_true", help="list the available backends")
	parser.add_argument("-o", "--output_drawing", help="output drawing of the circuit")
	parser.add_argument('-v', '--verbose', action='store_true', help='verbose output')
	return parser.parse_args()

def main(argv):
	global args_g
	args_g = parse_args()

	if args_g.verbose: print('Opening account ... ')
	provider = load_or_save_IBMQ_account()
	if args_g.verbose: print('Getting backends ...')
	backends = provider.backends()
	if args_g.list_backends:
		print('backends available:')
		for be in backends:
			st = be.status()
			if st.operational:
				print(f'\t{be.name()}, pending jobs:{st.pending_jobs}')
		exit(0)
	if args_g.backend == None:
		backend =  backends[0].name()
	elif args_g.backend not in [be.name() for be in backends]:
		print('unknown backend')
		exit(0)
	else:
		backend = args_g.backend
	if args_g.verbose: print(f'Using backend: {backend}')

	q = QuantumRegister(1)
	c = ClassicalRegister(1)
	superposition_state = QuantumCircuit(q, c)
	superposition_state.h(q)
	superposition_state.measure(q, c)

	if args_g.verbose:
		print(superposition_state.draw(output='text'))

	if args_g.output_drawing:
		superposition_state.draw(output='mpl').savefig('qc_circuit.png', dpi=150)

	
	backend = provider.get_backend(backend)
	qobj = assemble(transpile(superposition_state, backend=backend), backend=backend)
	if args_g.verbose: print('Submitting job ...')
	job = backend.run(qobj)
	retrieved_job = backend.retrieve_job(job.job_id())

	wait_for_job(backend, job)
	result = job.result()
	if args_g.verbose: 
		print(f'results: {result.get_counts()}')
	else:
		print(result.get_counts())
	if args_g.verbose: print('Done!')

main(sys.argv)

# ran on 28 april 2020
# program prints:
# Status @ 1 s: RUNNING, est. queue position: None
# Status @ 6 s: RUNNING, est. queue position: None
# Status @ 11 s: RUNNING, est. queue position: None
# {'1': 568, '0': 456}
