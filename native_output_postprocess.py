import os
import sys
from math import floor

import numpy as np
import srcpy.momnetumParser as mpr
import srcpy.momentumPloting as mpl

if len(sys.argv) < 3:
    exit("Usage: python3 native_output_postprocess.py <filename of native float> <filename of native double>")

if "float" not in sys.argv[1] :
    print("First file does not contain keyword float. Are you sure it is right?")

if "double" not in sys.argv[2]:
    print("First file does not contain keyword double. Are you sure it is right?")

#----------- FLOAT -------------
# "Matrix element = "
matrix_element_f = []
matrix_element_d = []
matrixElementPrecision = []
# "Momentum: "
momentum_f = []
momentum_d = []

with open(sys.argv[1], 'r') as f:
    mpr.parse_file_native(f,momentum_f,matrix_element_f)

with open(sys.argv[2], 'r') as f:
    mpr.parse_file_native(f,momentum_d,matrix_element_d)

    for i in range(len(matrix_element_f)):
        fl = float(matrix_element_f[i])
        dbl = float(matrix_element_d[i])
        sig_dig = floor(-np.log10( abs(dbl-fl)/(dbl+fl)*2))
        matrixElementPrecision.append(sig_dig)

    print(20*"-")
    print("First element in f = " + str(matrix_element_f[0]) + "")
    print("First element in d = " + str(matrix_element_d[0]) + "")
    print("Precision of first matrix element in f = " + str(matrixElementPrecision[0]) )
    mpl.plotHis_MEP("comparison_natives", "", "", matrixElementPrecision, 0)

    print(20*"-")
    print("Plot saved as comparison_natives.png")
    print(20*"-")

'''
with open(sys.argv[2], 'r') as f:
    newlines = []
    i = 0
    for l in f:
        newline = l
        if "Matrix element =" in l:
            newlines.append(l)
            newlines.append(l.split("M")[0] + "Matrix element number of sig dig = " + str(matrixElementPrecision[i]) + "\n")
            i += 1
        else :
            newlines.append(l)

    with open("gdb_output_postprocessed.txt", "w") as f:
        f.writelines(newlines)
'''
thresh = 4
saved_precisions = []
with open(sys.argv[2], 'r') as f:

    newlines = []
    i = 0
    block = []
    errase_block = False
    in_momenta = False

    for l in f:
        if not in_momenta and "Momenta:" in l:
            in_momenta = True

        if in_momenta:
            newline = l
            if "Matrix element =" in l:
                block.append(l)
                block.append(l.split("M")[0] + "Matrix element number of sig dig = " + str(matrixElementPrecision[i]) + "\n")
                errase_block = True
                i += 1
            else :
                block.append(l)

            if errase_block:
                if matrixElementPrecision[i-1] < thresh:
                    newlines.extend(block)
                    saved_precisions.append(matrixElementPrecision[i-1])
                block = []
                errase_block = False


    with open("boiler_plate/backup/ggttxgg/gdb_ggttxgg_native_test_31.txt", "w") as f:
        f.writelines(newlines)
print("We saved " + str(len(saved_precisions)) + " matrix elements with precision lower than " + str(thresh))
mpl.plotHis_MEP("comparison_natives_thresh"+str(thresh), "", "", saved_precisions, 0)