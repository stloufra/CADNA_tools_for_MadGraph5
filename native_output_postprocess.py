import os
import sys
from math import floor

import numpy as np
import srcpy.momnetumParser as mpr
import srcpy.momentumPloting as mpl

if len(sys.argv) < 4:
    exit(
        "Usage: python3 native_output_postprocess.py <filename of native float> <filename of native double> <savefile name> <thresh>")

if "float" not in sys.argv[1]:
    print("First file does not contain keyword float. Are you sure it is right?")

if "double" not in sys.argv[2]:
    print("First file does not contain keyword double. Are you sure it is right?")

if os.path.exists(sys.argv[3]):
    print("File with name " + sys.argv[3] + " already exists.")
    print("Do you want to overwrite it? (y/n).")
    ans = input()
    if ans != "y":
        exit("Exiting.")
    else:
        print("Overwriting file.")

else:
    print("File with name " + sys.argv[3] + " will be created.")

thresh = 3
if len(sys.argv) == 5:
    if sys.argv[4].isdigit():
        thresh = int(sys.argv[4])
        print("Threshold set to " + str(thresh))

file_name = sys.argv[3]

# ----------- FLOAT -------------
# "Matrix element = "
matrix_element_f = []
matrix_element_d = []
matrixElementPrecision = []
# "Momentum: "
momentum_f = []
momentum_d = []

with open(sys.argv[1], 'r') as f:
    mpr.parse_file_native(f, momentum_f, matrix_element_f)

with open(sys.argv[2], 'r') as f:
    mpr.parse_file_native(f, momentum_d, matrix_element_d)

    for i in range(len(matrix_element_f)):
        fl = float(matrix_element_f[i])
        dbl = float(matrix_element_d[i])
        sig_dig = floor(-np.log10(abs(dbl - fl) / (dbl + fl) * 2))
        matrixElementPrecision.append(sig_dig)

    print(20 * "-")
    print("First element in f = " + str(matrix_element_f[0]) + "")
    print("First element in d = " + str(matrix_element_d[0]) + "")
    print("Precision of first matrix element in f = " + str(matrixElementPrecision[0]))
    mpl.plotHis_MEP("comparison_natives", "", "", matrixElementPrecision, 0)

    print(20 * "-")
    print("Plot saved as comparison_natives.png")
    print(20 * "-")


if thresh != 3:
    print("The threshold is different from standart (3). Is that ok? (y/n).")
    ans = input()
    if ans != "y":
        thresh = 3

saved_precisions = []
with open(sys.argv[2], 'r') as f:
    newlines = []
    i = 0
    j = 0
    block = []
    errase_block = False
    in_momenta = False

    for l in f:
        newline = l
        if not in_momenta and "Momenta:" in l:
            in_momenta = True

        if in_momenta:
            if "Momenta:" in l:
                newline = newline.replace("Momenta:", f"Momenta: for event {j} ({i}) ")
            if "Matrix element =" in l:
                block.append(newline)
                block.append(newline.split("M")[0] + "Matrix element number of sig dig = " + str(
                    matrixElementPrecision[i]) + "\n")  # newline.split("M")[0] to get same indent
                errase_block = True
                i += 1
            else:
                block.append(newline)

            if errase_block:
                if matrixElementPrecision[i - 1] < thresh:
                    newlines.extend(block)
                    saved_precisions.append(matrixElementPrecision[i - 1])
                    j += 1
                block = []
                errase_block = False

    with open(file_name, "w") as f:
        f.writelines(newlines)
print("We saved " + str(len(saved_precisions)) + " matrix elements with precision lower than " + str(
    thresh) + "into file" + file_name)
mpl.plotHis_MEP("comparison_natives_thresh" + str(thresh), "", "", saved_precisions, 0)
