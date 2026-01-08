# Post process mutliple Subprocesses into common graphs instead of individual graphs
# Script is ment to be run from within -Suprocesses- dir
import os
import srcpy.momnetumParser as mpr
import matplotlib.pyplot as plt
import numpy as np

from dataclasses import dataclass, field
from typing import List, Any


@dataclass
class Data:
    # "Matrix element = "
    matrix_element: List[Any] = field(default_factory=list)
    matrixElementPrecision: List[Any] = field(default_factory=list)
    matrixElementPrecisionZeros: int = 0
    matrixElementPrecisionOnes: int = 0
    matrixElementPrecisionTwos: int = 0

    # "Momentum: "

    momentum: List[Any] = field(default_factory=list)
    momentaPrecision: List[Any] = field(default_factory=list)
    colinearities: List[Any] = field(default_factory=list)
    momentaPrecisionZeros: int = 0


# begining of the postprocess
# get current directory:
cwd = os.getcwd()

if cwd.split("/")[-1] != "SubProcesses":
    exit("Not in SubProcesses dir")

process = cwd.split("/")[-2]
process = process.replace("PROC_", "")
print("Working on process:" + process)

subdirs = os.listdir(cwd)
print("It contains the following subdirs:")
for subdir in subdirs:
    print(subdir.replace("P1_", ""))
print("-" * 20)
print("Total number of subprocesses: " + str(len(subdirs)))
print(" " * 20 + "Starting post processing")

data: List[Data] = []
valid_subdirs = []

for subdir in subdirs:
    print(f"Working on {subdir}")
    d = Data()

    if not os.path.isdir(subdir):
        continue

    os.chdir(subdir)
    f = None
    for file in os.listdir("."):
        if "gdb_run_output" in file:
            f = file
            break

    if f is None:
        print(f"No gdb_run_output file found in {subdir}")
        os.chdir("..")
        continue

    if os.path.getsize(f) == 0:
        print(f"gdb_run_output file is empty in {subdir}")
        os.chdir("..")
        continue
    ff = open(f, "r")

    # parse the file
    d.matrixElementPrecisionZeros = mpr.parse_file(ff, d.momentum, d.momentaPrecision, d.matrix_element,
                                                   d.matrixElementPrecision, d.matrixElementPrecisionZeros)

    if (len(d.matrixElementPrecision) != len(d.matrix_element)):
        exit(
            "Number of matrix elements and number of matrix element precisions is not the same. file causing trouble: " + subdir + "/" + f)
    if (len(d.momentaPrecision) != len(d.momentum)):
        exit(
            "Number of momenta and number of momenta precisions is not the same. file causing trouble: " + subdir + "/" + f)

    for mp in d.matrixElementPrecision:
        if mp == 0:
            d.matrixElementPrecisionZeros += 1
        elif mp == 1:
            d.matrixElementPrecisionOnes += 1
        elif mp == 2:
            d.matrixElementPrecisionTwos += 1

    data.append(d)
    valid_subdirs.append(subdir)
    os.chdir("..")

# Plotting combined results
if data:
    names = [s.replace("P1_", "") for s in valid_subdirs]
    zeros = [d.matrixElementPrecisionZeros for d in data]
    ones = [d.matrixElementPrecisionOnes for d in data]
    twos = [d.matrixElementPrecisionTwos for d in data]

    x = np.arange(len(names))
    width = 0.25

    plt.figure(figsize=(12, 7))
    plt.bar(x - width, zeros, width, label='Precision 0', color='blue')
    plt.bar(x, ones, width, label='Precision 1', color='green')
    plt.bar(x + width, twos, width, label='Precision 2', color='orange')

    plt.xlabel('Subdirectories')
    plt.ylabel('Number of elements')
    plt.title(f'Matrix Element Precision Comparison for {process}')
    plt.xticks(x, names, rotation=45, ha='right')
    plt.legend()

    plt.tight_layout()
    plt.savefig(f"combined_precision_{process}.png")
    print(f"Combined plot saved as combined_precision_{process}.png")
    plt.close()