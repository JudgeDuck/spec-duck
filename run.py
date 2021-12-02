import os
import sys
import subprocess

duck_prefix = os.environ.get("DUCK_PREFIX", "~/duck/")
duck_run = os.environ.get("DUCK_RUN", os.path.join(duck_prefix, "duck-utils/duck-run"))
duck_ip = os.environ["DUCK_IP"]

n_run_times = int(os.environ.get("N_RUN_TIMES", 10))

programs = list(filter(lambda x: x != "", open("program_list.txt", "r").read().split("\n")))

run_results = []

for program in programs:
	sys.stdout.write("Running %s " % program)
	sys.stdout.flush()
	
	sum_time = 0
	sum_time_2 = 0
	
	for i in range(n_run_times):
		result = subprocess.run([
			os.path.realpath(os.path.expanduser(duck_run)),
			duck_ip,
			"bin/%s.exe" % program,
			"-t", "5000000000",
			"-m", "1048576",
			"-O", "16777216",
			"-E", "16777216",
			"-r", "/dev/stdout",
			"-o", "/dev/null",
			"-e", "/dev/null"
		], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=60)
		time_ns = int(list(filter(lambda x: x[:8] == "time-ns ", str(result.stdout, "utf-8").split("\n")))[0].split(" ")[1])
		time_ms = time_ns / 1e6
		sum_time += time_ms
		sum_time_2 += time_ms * time_ms
		
		sys.stdout.write(".")
		sys.stdout.flush()
	
	average_time = sum_time / n_run_times
	stddev = (sum_time_2 * n_run_times - sum_time * sum_time) ** 0.5 / n_run_times
	
	run_results.append([program, average_time, stddev])
	sys.stdout.write("\n")
	sys.stdout.flush()

print("")
print("Results:")
print("")

print("Time(ms)\tstddev(ms)\tProgram")

for res in run_results:
	print("%.2f\t%.2f\t%s" % (res[1], res[2], res[0]))

print("")

print(",".join(programs))
print(",".join(map(lambda x: "%.2f(%.2f)" % (x[1], x[2]), run_results)))

