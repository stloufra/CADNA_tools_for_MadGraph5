# Post process mutliple Subprocesses into common graphs instead of individual graphs
# Script is ment to be run from within -Suprocesses- dir
import os
import srcpy.momnetumParser as mpr
import matplotlib.pyplot as plt
import numpy as np

from dataclasses import dataclass, field
from typing import List, Any

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

@dataclass
class Data:
    # "Matrix element = "
    matrix_element: List[Any] = field(default_factory=list)
    matrixElementPrecision: List[Any] = field(default_factory=list)
    maxCol: List[Any] = field(default_factory=list)
    maxSoft: List[Any] = field(default_factory=list)
    deviants: int = 0
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
print("Working on process: " + process)

base_dir =  cwd

subdirs = [
    sub for sub in os.listdir(base_dir)
    if os.path.isdir(os.path.join(base_dir, sub))
    and sub.startswith("P1_")
    and "_float" not in sub
]

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
        print(f"{bcolors.WARNING}No gdb_run_output file found in {subdir}{bcolors.ENDC}")
        os.chdir("..")
        continue

    if os.path.getsize(f) == 0:
        print(f"{bcolors.WARNING}gdb_run_output file is empty in {subdir}{bcolors.ENDC}")
        os.chdir("..")
        continue
    ff = open(f, "r")

    # parse the file
    d.matrixElementPrecisionZeros = mpr.parse_file_woMomP(ff, d.momentum, d.matrix_element,
                                                   d.matrixElementPrecision, d.matrixElementPrecisionZeros)

    if (len(d.matrixElementPrecision) != len(d.matrix_element)):
        exit(
            "Number of matrix elements and number of matrix element precisions is not the same. file causing trouble: " + subdir + "/" + f)

    for mp in d.matrixElementPrecision:
        if mp == 0:
            d.matrixElementPrecisionZeros += 1
        elif mp == 1:
            d.matrixElementPrecisionOnes += 1
        elif mp == 2:
            d.matrixElementPrecisionTwos += 1

    nb_events = len(d.momentum)
    nb_par = len(d.momentum[0])
    for ev in range(nb_events):
        col = []
        soft = []
        for i in range(nb_par):
            for j in range(i + 1, nb_par):
                if i == 0 and j == 1:
                    continue  # skip (0, 1) - always colinear
                col.append(mpr.colinearity(d.momentum[ev][i], d.momentum[ev][j]))
                soft.append(mpr.softness(d.momentum[ev][i], d.momentum[ev][j]))
        d.maxCol.append(max(col))
        d.maxSoft.append(max(soft))

    for ev in range(nb_events):
        if d.matrixElementPrecision[ev] < 3:
            if d.maxCol[ev] < 0.995 and d.maxSoft[ev] < 50:
                d.deviants += 1
        else:
            continue

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

    fig, ax = plt.subplots(figsize=(12, 7))
    rects1 = ax.bar(x - width, zeros, width, label='Precision 0', color='blue')
    rects2 = ax.bar(x, ones, width, label='Precision 1', color='green')
    rects3 = ax.bar(x + width, twos, width, label='Precision 2', color='orange')

    # Add labels above bars
    ax.bar_label(rects1, padding=0)
    ax.bar_label(rects2, padding=6)
    ax.bar_label(rects3, padding=12)

    ax.set_xlabel('Subdirectories')
    ax.set_ylabel('Number of elements')
    ax.set_title(f'Matrix Element Precision Comparison for {process}')
    ax.set_xticks(x)
    ax.set_xticklabels(names, rotation=45, ha='right')
    ax.legend()

    fig.tight_layout()
    plt.savefig(f"combined_precision.png")
    print(f"Combined plot saved as combined_precision.png")
    plt.close()

    # Plotting deviants
    deviants_list = [d.deviants for d in data]

    fig, ax = plt.subplots(figsize=(12, 7))
    rects = ax.bar(names, deviants_list, color='red')

    # Add labels above bars
    ax.bar_label(rects, padding=3)

    ax.set_xlabel('Subdirectories')
    ax.set_ylabel('Number of Deviants')
    ax.set_title(f'Number of Deviants per Subprocess for {process}')
    plt.xticks(rotation=45, ha='right')

    fig.tight_layout()
    plt.savefig(f"deviants.png")
    print(f"Deviants plot saved as deviants.png")
    plt.close()

    # Scatter plot: log10(Matrix element) vs precision (< 3)
    fig, ax = plt.subplots(figsize=(10, 7))
    
    for subdir, d in zip(valid_subdirs, data):
        label = subdir.replace("P1_", "")
    
        me = np.array(d.matrix_element)
        prec = np.array(d.matrixElementPrecision)
    
        mask = prec < 3
        if not np.any(mask):
            continue
    
        # Safe log10: ignore non-positive values
        me_sel = me[mask]
        prec_sel = prec[mask]
    
        positive_mask = np.abs(me_sel) > 0
        me_sel = me_sel[positive_mask]
        prec_sel = prec_sel[positive_mask]
        prec_pert = np.random.uniform(-0.4,0.4, len(prec_sel))
    
        ax.scatter(
            np.log10(np.abs(me_sel)),
            prec_sel + prec_pert,
            s=15,
            alpha=0.7,
            label=label
        )
    
    ax.set_xlabel(r'$\log_{10}(|\mathrm{Matrix\ Element}|)$')
    ax.set_ylabel('Matrix Element Precision')
    ax.set_title(f'Precision vs Matrix Element for {process}')
    ax.legend(title='Subprocess', fontsize=9)
    ax.grid(True, linestyle='--', alpha=0.4)
    
    fig.tight_layout()
    plt.savefig("precision_vs_matrix_element.png")
    print("Scatter plot saved as precision_vs_matrix_element.png")
    plt.close()

