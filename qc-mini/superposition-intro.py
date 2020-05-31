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
		print(f'Status @ {time.time() - start_time:0.0f} s: {job_status.name},'
			  f' est. queue position: {job.queue_position()}')
		time.sleep(wait_interval)
		job_status = job.status()

def parse_args(back_ends):
	parser = argparse.ArgumentParser(description="Quantum circuit to demonstrate superposition")
	parser.add_argument('backend', choices=back_ends, help='ibmq backend')
	parser.add_argument("-o", "--output_drawing", action="store_true", help="output drawing of the circuit")
	return parser.parse_args()

def main(argv):
	global args_g

	provider = load_or_save_IBMQ_account()
	back_ends = [be.name() for be in provider.backends()]
	args_g = parse_args(back_ends)

	q = QuantumRegister(1)
	c = ClassicalRegister(1)
	superposition_state = QuantumCircuit(q, c)
	superposition_state.h(q)
	superposition_state.measure(q, c)

	if args_g.output_drawing:
		superposition_state.draw(output='mpl').savefig("circuit.png", dpi=150)

	backend = provider.get_backend(args_g.backend)
	qobj = assemble(transpile(superposition_state, backend=backend), backend=backend)
	job = backend.run(qobj)
	retrieved_job = backend.retrieve_job(job.job_id())

	wait_for_job(backend, job)
	result = job.result()
	print(result.get_counts())

main(sys.argv)

# ran on 28 april 2020
# program prints:
# Status @ 1 s: RUNNING, est. queue position: None
# Status @ 6 s: RUNNING, est. queue position: None
# Status @ 11 s: RUNNING, est. queue position: None
# {'1': 568, '0': 456}
