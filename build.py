import os

duck_prefix = os.environ.get("DUCK_PREFIX", "~/duck/")
duck_cxx = os.environ.get("DUCK_CXX", os.path.join(duck_prefix, "duck-utils/duck64-glibc-cxx"))

programs = list(filter(lambda x: x != "", open("program_list.txt", "r").read().split("\n")))

os.system("mkdir -p bin/")

for program in programs:
	print("Building %s" % program)
	os.system("%s src/%s.cpp -O2 -o bin/%s.exe" % (duck_cxx, program, program))

print("Done")

