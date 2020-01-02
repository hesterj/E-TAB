import os
import shutil
import sys
import subprocess
import fnmatch
from subprocess import call
from multiprocessing.pool import ThreadPool as Pool


def proof_search(name):
	print("Next attempt: "+ name)
	output_file = 'output/' + name
	job = "FEQCASC27/" + name
	
	command = ["./etab122119",
				  "--tableau=1",
				  "--tableau-depth=6",
				  "--output-file=" + output_file,
				  "--memory-limit=56000",
				  "--cpu-limit=600", 
				  job]

	"""
	command = ["./vanilla",
				  "--auto",
				  "--output-file=" + output_file,
				  "--cpu-limit=30",
				  job]
	"""
	temp = ' '.join(command)
		
	print(temp)
	#call(temp)
	subprocess.run(temp, shell=True)
	elif 'CPU time limit exceeded' in open(output_file).read():
		print('Timeout')
		resourceout.append(name)
	elif 'ResourceOut' in open(output_file).read():
		print('Resourceout')
		resourceout.append(name)
	elif 'Failure:' in open(output_file).read():
		print('Failure')
		failures.append(name)
	elif 'Unsatisfiable' in open(output_file).read():
		successes.append(name)
	elif 'Theorem' in open(output_file).read():
		successes.append(name)
	elif 'CNFRefutation' in open(output_file).read():
		print('CNFRefutation')
		successes.append(name)
	elif 'CounterSatisfiable' in open(output_file).read():
		#cts.append(name)
		successes.append(name)
	elif 'Satisfiable' in open(output_file).read():
		print('Tableau branch is satisfiable, proof failure')
		errors.append(name)
	else:
		print('Error: Unknown output from E')
		errors.append(name)

def run_output(runname):
	call(["touch", "runs/" + runname])
	os.remove("runs/" + runname)
	run = open("runs/" + runname, "w+")

	# Run finished, output in to file
	#a = " ".join(command)
	run.write("\nNumber of problems: ") 
	run.write(str(len(temp_filenames))) 
	run.write("\nTerm ordering: tAuto\n") 
	run.write("Memory limit: 56000\n")
	run.write("# of Successes: " + str(len(successes)) + "\n") 
	run.write("CPU limit: " + str(cpulimit) + "\n")  
	run.write("# of Failures: " + str(len(failures)) + "\n")
	run.write("# of Errors: " + str(len(errors)) + "\n") 
	
	run.write("Successes: " + str(len(successes)) + "\n")  
	for item in successes:
		run.write(item + "\n")

	run.write("Failures: " + str(len(failures)) + "\n")  
	for item in failures:
		run.write(item + "\n")
		
	run.write("Errors: " + str(len(errors)) + "\n") 
	for item in errors:
		run.write(item + "\n")
		
	run.write("END\n") 
	
		
# Start the proof search

folders = []
successes = []
errors = []
failures = []
resourceout = []
runname = 'etabcasc27_122119'
cpulimit = 600
temp_filenames = []

for f in os.listdir("FEQCASC27"):
	temp_filenames.append(f)


filenames = temp_filenames

for filename in filenames:
	if '.p' not in filename:
		temp_filenames.remove(filename)
	elif '.py' in filename:
		temp_filenames.remove(filename)
	elif '^' in filename:
		temp_filenames.remove(filename)
	elif '.ax' in filename:
		temp_filenames.remove(filename)
	elif 'definitions' in filename:
		temp_filenames.remove(filename)
		
print(temp_filenames)
print(len(temp_filenames))

for prob in temp_filenames:
	proof_search(prob)
	
run_output(runname)
shutil.rmtree('output')
os.mkdir('output')
