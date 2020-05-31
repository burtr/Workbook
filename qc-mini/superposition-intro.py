

# Quantum circuit to demonstrate superposition
# burton rosenberg
# may 2020



# Importing standard Qiskit libraries and configuring account
from qiskit import QuantumCircuit, execute, Aer, IBMQ
from qiskit.compiler import transpile, assemble
from qiskit.tools.jupyter import *
from qiskit.visualization import *
from qiskit.providers.jobstatus import JOB_FINAL_STATES, JobStatus
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, execute, Aer
import time


# Saving or Loading IBM Q account(s)
#IBMQ.save_account('MY_API_TOKEN') # only needs to be done once
provider = IBMQ.load_account()


# a helper function

def wait_for_job(backend, job, wait_interval=5):
	retrieved_job = backend.retrieve_job(job.job_id())
	start_time = time.time()
	job_status = job.status()
	while job_status not in JOB_FINAL_STATES:
		print(f'Status @ {time.time() - start_time:0.0f} s: {job_status.name},'
			  f' est. queue position: {job.queue_position()}')
		time.sleep(wait_interval)
		job_status = job.status()


# Define the Quantum and Classical Registers
q = QuantumRegister(1)
c = ClassicalRegister(1)

# Build the circuit
superposition_state = QuantumCircuit(q, c)
superposition_state.h(q)
superposition_state.measure(q, c)

# draw the circuit
#draw_circuit = False
draw_circuit = True
if draw_circuit:
	superposition_state.draw(output='mpl').savefig("myfile.png", dpi=150)

# Execute the circuit
backend = provider.backends.ibmq_london
qobj = assemble(transpile(superposition_state, backend=backend), backend=backend)
job = backend.run(qobj)
retrieved_job = backend.retrieve_job(job.job_id())

# Wait for completetion
wait_for_job(backend, job)

result = job.result()
print(result.get_counts())

# ran on 28 april 2020
# program prints:
# Status @ 1 s: RUNNING, est. queue position: None
# Status @ 6 s: RUNNING, est. queue position: None
# Status @ 11 s: RUNNING, est. queue position: None
# {'1': 568, '0': 456}
