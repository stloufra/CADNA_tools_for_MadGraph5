import os
import sys
import numpy as np
import srcpy.momnetumParser as mpr
import srcpy.momentumPloting as mpl

if len(sys.argv) > 4 and (sys.argv[4] != "plotly" and sys.argv[4] != "both"):
    exit("Usage: python histogram.py <filename of ./check.exe -p -v output> <precision> <optimization> <plotly or both or nothing(for matplotlib)>")

# open file gdb.out or one provided in argument
if len(sys.argv) > 1:
    f = open(sys.argv[1], 'r')
else:
    exit("Usage: python histogram.py <filename of ./check.exe -p -v output>")

precision = "unknown"
if len(sys.argv) > 2:
    if "float" in sys.argv[2]:
        precision = "float"
    elif "double" in sys.argv[2]:
        precision = "double"

optimisation = "unknown"
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
process = process.split("_")[-2] + "_" + process.split("_")[-1]
print(process)

#get the random number seed from the file name
seed = sys.argv[1].split("_")[-1].split(".")[0]
process += "_seed_" + seed

# foward declaration
# "Matrix element = "
matrix_element = []
matrixElementPrecision = []
matrixElementPrecisionZeros = 0
# "Momentum: "
momentum = []
momentaPrecision = []
colinearities = []
momentaPrecisionZeros = 0  # just a counter

# parse the file
matrixElementPrecisionZeros = mpr.parse_file(f, momentum, momentaPrecision, matrix_element, matrixElementPrecision, matrixElementPrecisionZeros)

# cast to np arrays
matrix_element = np.array(matrix_element)
matrixElementPrecision = np.array(matrixElementPrecision)
momentum = np.array(momentum)
momentaPrecision = np.array(momentaPrecision)

nb_events = len(momentum)
nb_par = len(momentum[0])
if (len(matrixElementPrecision) != len(matrix_element)):
    exit("Number of matrix elements and number of matrix element precisions is not the same. file causing trouble: " +
         sys.argv[1])
if (len(momentaPrecision) != len(momentum)):
    exit("Number of momenta and number of momenta precisions is not the same. file causing trouble: " + sys.argv[1])

print("Number of matrix elements:                   " + str(len(matrixElementPrecision)))
print("Number of momenta groups:                    " + str(len(momentaPrecision)))
if len(momentum) > 0:
    print("Number of in/out particles:                  " + str(nb_par))
    print("Number of prec. for particles momenta:       " + str(len(momentaPrecision[0])))
    print("Number of zero matrix elements:              " + str(matrixElementPrecisionZeros))
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
matrixElementPrecision_fl = matrixElementPrecision.flatten()
momentum_fl = momentum.flatten()
momentaPrecision_fl = momentaPrecision.flatten()

if ((len(matrixElementPrecision_fl) != len(matrixElementPrecision)) or (len(matrix_element) != len(matrix_element_fl))):
    exit(
        "Number of matrix elements and number of matrix element precisions is not the same after flating. file causing "
        + "trouble: " + sys.argv[1])
if((len(momentum[0])*4*len(matrixElementPrecision)) != len(momentum_fl)):
    exit("There is not right amount of momenta given number of matrix elements. file causing trouble: " + sys.argv[1])

print("Number of all momenta:                       " + str(len(momentaPrecision_fl)))
print("Number of all momenta prec:                  " + str(len(momentum_fl)))

# matplotlib -> default (no argument) or both
if len(sys.argv) < 3 or (len(sys.argv) > 2 and sys.argv[2] == "both"):

    if len(colinearities) > 0:
        mpl.plotScat_COLvsMEandMEP(process, precision, optimisation, colinearities, matrix_element_fl,
                              matrixElementPrecision_fl)
    if len(energys) > 0:
        mpl.plotScat_EratiossMEP(process, precision, optimisation, energys, colinearities, matrixElementPrecision_fl,
                                 nb_par)

        mpl.plot_combined(process, precision, optimisation, energys, colinearities, matrixElementPrecision_fl)

        mpl.plotScat_EvsMEP(process, precision, optimisation, energys, colinearities, matrixElementPrecision_fl, nb_par)

        mpl.plotScat_EvsME(process, precision, optimisation, energys, matrix_element_fl, nb_par)

    if len(matrixElementPrecision_fl) > 0:
        mpl.plotHis_MEP(process, precision, optimisation, matrixElementPrecision_fl, matrixElementPrecisionZeros)

    if len(momentaPrecision_fl) > 0:
        mpl.plotHis_MOP(process, precision, optimisation, momentaPrecision_fl, momentaPrecisionZeros)
        mpl.plotScat_MomentumMagnitudeVsMEP(process, precision, optimisation, momentum, matrixElementPrecision_fl,
                                           nb_par)
        mpl.plotScat_MomentumComponentsVsMEP(process, precision, optimisation, momentum, matrixElementPrecision_fl,nb_par)

    if len(matrixElementPrecision_fl) > 0:
        mpl.plotScat_MEvsMEP(process, precision, optimisation, matrixElementPrecision_fl, matrixElementPrecisionZeros,
                             matrix_element_fl)

    if len(momentaPrecision_fl) > 0:
        mpl.plotScat_MOPvsMO(process, precision, optimisation, momentaPrecision_fl, momentaPrecisionZeros, momentum_fl)

        print(20*"-")
        print("Finished plotting")

# Plotly only plots the last two plots and histograms:
#  - histogram of matrix element precision
#  - scatter plot of matrix element precision vs matrix element
#  - histogram of momenta precision
#  - scatter plot of momenta precision vs momentum_fl
# plotly -> plotly or both
if len(sys.argv) > 2 and (sys.argv[2] == "plotly" or sys.argv[2] == "both"):
    # do the same using plotly
    import plotly.express as px

    # histogram of matrix element precision
    fig = px.histogram(x=matrixElementPrecision_fl,
                       title="Matrix element precision for: " + process + " " + precision + " " + optimisation)
    fig.show()

    # scatter plot of matrix element precision vs matrix element
    fig = px.scatter(x=np.log10(matrix_element_fl), y=matrixElementPrecision_fl,
                     title="Matrix element precision vs matrix element for: " + process + " " + precision + " " + optimisation,
                     labels={"x": "log10(Matrix element)", "y": "Digits of precision"})
    fig.show()
