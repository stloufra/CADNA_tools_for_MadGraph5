import os
import sys
import numpy as np
import srcpy.momnetumParser as mpr
import srcpy.momentumPloting as mpl

if len(sys.argv) > 4 and (sys.argv[4] != "plotly" and sys.argv[4] != "both"):
    exit("Usage: python histogram.py <filename of ./check.exe -p -v output> <accuracy> <optimization> <plotly or both or nothing(for matplotlib)>")

# open file gdb.out or one provided in argument
if len(sys.argv) > 1:
    f = open(sys.argv[1], 'r')
else:
    exit("Usage: python histogram.py <filename of ./check.exe -p -v output>")

accuracy = "FP32"
if len(sys.argv) > 2:
    if "float" in sys.argv[2]:
        accuracy = "FP32"
    elif "double" in sys.argv[2]:
        accuracy = "FP64"

optimisation = ""
if len(sys.argv) > 3:
    if "O0" in sys.argv[3]:
        optimisation = "-O0"
    elif "O3" in sys.argv[3]:
        optimisation = "-O3"
    elif "fgdb" in sys.argv[3]:
        optimisation += "_fortran"
    elif "load" in sys.argv[3]:
        optimisation += "_load_momenta"

# get current directory:
cwd = os.getcwd()
process = cwd.split("/")[-1]
if "_" in process:
    process = process.split("_")[-2] + "_" + process.split("_")[-1]
else:
    process = "test"
print(process)

#get the random number seed from the file name
#seed = sys.argv[1].split("_")[-1].split(".")[0]
#process += "_seed_" + seed

# foward declaration
# "Matrix element = "
matrix_element = []
matrixElementAccuracy = []
matrixElementAccuracyZeros = 0
# "Momentum: "
momentum = []
momentaAccuracy = []
colinearities = []
momentaAccuracyZeros = 0  # just a counter

# parse the file
matrixElementAccuracyZeros = mpr.parse_file(f, momentum, momentaAccuracy, matrix_element, matrixElementAccuracy, matrixElementAccuracyZeros)

# cast to np arrays
matrix_element = np.array(matrix_element)
matrixElementAccuracy = np.array(matrixElementAccuracy)
momentum = np.array(momentum)
momentaAccuracy = np.array(momentaAccuracy)

nb_events = len(momentum)
nb_par = len(momentum[0])
if (len(matrixElementAccuracy) != len(matrix_element)):
    exit("Number of matrix elements and number of matrix element accuracys is not the same. file causing trouble: " +
         sys.argv[1])
if (len(momentaAccuracy) != len(momentum)):
    exit("Number of momenta and number of momenta accuracys is not the same. file causing trouble: " + sys.argv[1])

print("Number of matrix elements:                   " + str(len(matrixElementAccuracy)))
print("Number of momenta groups:                    " + str(len(momentaAccuracy)))
if len(momentum) > 0:
    print("Number of in/out particles:                  " + str(nb_par))
    print("Number of prec. for particles momenta:       " + str(len(momentaAccuracy[0])))
    print("Number of zero matrix elements:              " + str(matrixElementAccuracyZeros))
else:
    exit("No momenta found")

for ev in range(nb_events):
    col=[]
    for i in range(nb_par):
        for j in range(i + 1, nb_par):
            if i == 0 and j == 1:
                continue  # skip (0, 1) - always colinear
            col.append(mpr.colinearity(momentum[ev][i], momentum[ev][j]))
    colinearities.append(col)

colinearities = np.array(colinearities)

energys = momentum[:, :, 0]

# flatten the arrays
matrix_element_fl = matrix_element.flatten()
matrixElementAccuracy_fl = matrixElementAccuracy.flatten()
momentum_fl = momentum.flatten()
momentaAccuracy_fl = momentaAccuracy.flatten()

if ((len(matrixElementAccuracy_fl) != len(matrixElementAccuracy)) or (len(matrix_element) != len(matrix_element_fl))):
    exit(
        "Number of matrix elements and number of matrix element accuracys is not the same after flating. file causing "
        + "trouble: " + sys.argv[1])
if((len(momentum[0])*4*len(matrixElementAccuracy)) != len(momentum_fl)):
    exit("There is not right amount of momenta given number of matrix elements. file causing trouble: " + sys.argv[1])

print("Number of all momenta:                       " + str(len(momentaAccuracy_fl)))
print("Number of all momenta prec:                  " + str(len(momentum_fl)))

# matplotlib -> default (no argument) or both
print("Lenght of system arguments" + str(len(sys.argv)))
if len(sys.argv) < 5 or (len(sys.argv) > 4 and sys.argv[4] == "both"):

    if len(colinearities) > 0:
        mpl.plotScat_COLvsMEandMEP(process, accuracy, optimisation, colinearities, matrix_element_fl,
                              matrixElementAccuracy_fl)
    if len(energys) > 0:
        mpl.plotScat_EratiossMEP(process, accuracy, optimisation, energys, colinearities, matrixElementAccuracy_fl,
                                 nb_par)

        mpl.plot_combined(process, accuracy, optimisation, energys, colinearities, matrixElementAccuracy_fl)

        mpl.plotScat_EvsMEP(process, accuracy, optimisation, energys, colinearities, matrixElementAccuracy_fl, nb_par)

        mpl.plotScat_EvsME(process, accuracy, optimisation, energys, matrix_element_fl, nb_par)

    if len(matrixElementAccuracy_fl) > 0:
        mpl.plotHis_MEP(process, accuracy, optimisation, matrixElementAccuracy_fl, matrixElementAccuracyZeros)

    if len(momentaAccuracy_fl) > 0:
        mpl.plotHis_MOP(process, accuracy, optimisation, momentaAccuracy_fl, momentaAccuracyZeros)
        mpl.plotScat_MomentumMagnitudeVsMEP(process, accuracy, optimisation, momentum, matrixElementAccuracy_fl,
                                           nb_par)
        mpl.plotScat_MomentumComponentsVsMEP(process, accuracy, optimisation, momentum, matrixElementAccuracy_fl,nb_par)

    if len(matrixElementAccuracy_fl) > 0:
        mpl.plotScat_MEvsMEP(process, accuracy, optimisation, matrixElementAccuracy_fl, matrixElementAccuracyZeros,
                             matrix_element_fl)

    if len(momentaAccuracy_fl) > 0:
        mpl.plotScat_MOPvsMO(process, accuracy, optimisation, momentaAccuracy_fl, momentaAccuracyZeros, momentum_fl)

        print(20*"-")
        print("Finished plotting")

# Plotly only plots the last two plots and histograms:
#  - histogram of matrix element accuracy
#  - scatter plot of matrix element accuracy vs matrix element
#  - histogram of momenta accuracy
#  - scatter plot of momenta accuracy vs momentum_fl
# plotly -> plotly or both
if len(sys.argv) > 4 and (sys.argv[4] == "plotly" or sys.argv[4] == "both"):
    # do the same using plotly
    import plotly.express as px

    # histogram of matrix element accuracy
    fig = px.histogram(x=matrixElementAccuracy_fl,
                       title="Matrix element accuracy for: " + process + " " + accuracy + " " + optimisation)
    fig.show()

    # scatter plot of matrix element accuracy vs matrix element
    fig = px.scatter(x=np.log10(matrix_element_fl), y=matrixElementAccuracy_fl,
                     title="Matrix element accuracy vs matrix element for: " + process + " " + accuracy + " " + optimisation,
                     labels={"x": "log10(Matrix element)", "y": "Sig. digits"})
    fig.show()
