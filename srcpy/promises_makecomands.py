import subprocess
import os

if not "make_output.txt" in os.listdir("."):
    subprocess.run('make -j12 OPTFLAGS=" -O2 -g" CUDA_HOME="" AVX=none HASCURAND=hasNoCurand GTESTLIBS= > make_output.txt', shell=True)

#read lines
if not "bashlines.sh" in os.listdir("."):
    f = open("make_output.txt", "r")
    lines = f.readlines()
    f.close()

    bashlines = ["#!/bin/bash\n"]

    for l in lines:
        if "c++" in l:
            bashlines.append(l)
        if "gfortran -o" in l:
            bashlines.append(l)

    f = open("bashlines.sh", "w")
    f.writelines(bashlines)
    f.close()
    subprocess.run("chmod +x bashlines.sh", shell=True)

with open("error_run.txt", "w") as f:
    print("Running bashlines.sh")
    subprocess.run(["bash", "bashlines.sh"], stdout=f, stderr=f)

with open("error_run.txt", "r") as f:
    lines = f.readlines()
f.close()

errorInLines = False
for l in lines:
    if "error" in l:
        errorInLines = True
        print(l)

if errorInLines:
    exit("Fix the error in the bashlines.sh file and run again")
else:
    print("No errors found in bashlines.sh")

changes = 0

i=0
for l in lines:
    if l.strip() == "":
        lines[i] = "\n"

    elif not "#! /bin/bash" in l:
        lines[i] = l.strip() + " -lcadnaC -L$CADNA_PATH/lib -I$CADNA_PATH/include\n"
        changes += 1

    i=i+1

fileName = "bashlines.sh"
print(f"Changes in: {fileName:<30}\t{changes}")

f = open(fileName, "w")
f.writelines(lines)
f.close()
