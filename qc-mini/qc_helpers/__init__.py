#!/usr/bin/env python3

from qiskit import QuantumCircuit, execute, Aer, IBMQ
from qiskit.compiler import transpile, assemble
from qiskit.tools.jupyter import *
from qiskit.visualization import *
from qiskit.providers.jobstatus import JOB_FINAL_STATES, JobStatus
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, execute, Aer
import time, math, argparse

#
# qc_helpers.py
# 
# author: burt rosenberg
# date: 17 june 2020
# last update:
#

args_g = 0 

def load_or_save_IBMQ_account(api_token=None):
	global args_g
	if api_token:
		# only needs to be done once
		IBMQ.save_account(api_token)
	provider = IBMQ.load_account()
	return provider

def wait_for_job(backend, job, wait_interval=5):
	global args_g
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
	global args_g
	print('backends available:')
	for be in backends:
		st = be.status()
		if st.operational:
			print(f'\t{be.name()}, pending jobs:{st.pending_jobs}')

def match_backend_name(be, be_s,min_len=3):
	global args_g
	if len(be)<3:
		return ""
	for be_t in be_s:
		if be in be_t:
			return be_t
	return ""

def parse_args():
	global args_g
	parser = argparse.ArgumentParser(description="Quantum circuit to demonstrate superposition")
	parser.add_argument('backend', nargs='?', help='ibmq backend name or partial name')
	parser.add_argument("-L", "--list_backends", action="store_true", help="list the available backends")
	parser.add_argument('-v', '--verbose', action='store_true', help='verbose output')
	parser.add_argument('-V', '--unverbose', action='store_true', help='silent output')
	args_g = parser.parse_args()
	return args_g


