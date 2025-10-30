import os
import numpy as np
import matplotlib.pyplot as plt

def plotScat_COLvsMEP(process, precision, optimisation, colinearities, matrix_element_fl, matrixElementPrecision_fl):
    #plot scatter plot of colinearities vs matrix element precision
    fig, ax = plt.subplots()
    plt.title("Colinearities vs matrix element precision for: "+process+" "+precision+" "+optimisation)
    plt.xlabel("Colinearity")
    plt.ylabel("Digits of precision")
    #keep outliers
    y_perturbation = np.random.uniform(-0.4, 0.4, colinearities.size)
    plt.scatter(colinearities, matrixElementPrecision_fl+y_perturbation,s=0.01)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_colinearities_MEP_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()
    #Colinearities vs matrix element
    fig, ax = plt.subplots()
    plt.title("Colinearities vs matrix element precision for: "+process+" "+precision+" "+optimisation)
    plt.xlabel("Colinearity")
    plt.ylabel("Log10 of matrix element")
    #keep outliers
    plt.scatter(colinearities, np.log10(matrix_element_fl), s=0.01)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_colinearities_ME_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()

def plotScat_EvsMEP(process, precision, optimisation, energys, colinearities, matrixElementPrecision_fl):
    #Energys vs matrix element precision
    fig, ax = plt.subplots()
    plt.title("Energys vs matrix element precision for: "+process+" "+precision+" "+optimisation)
    plt.xlabel( "Energy")
    plt.ylabel( "Digits of precision")
    #keep outliers
    y_perturbation = np.random.uniform(-0.4, 0.4, colinearities.size)
    plt.scatter(    energys, matrixElementPrecision_fl + y_perturbation,s=0.01)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_energys_MEP_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()

def plotScat_MEvsMEP(process, precision, optimisation, matrixElementPrecision_fl, matrixElementPrecisionZeros, matrix_element_fl):
    # scatter plot of matrix element precision vs matrix element
    fig, ax = plt.subplots()
    zeros = matrixElementPrecisionZeros
    plt.title("Matrix element precision vs matrix element for: "+process+" "+precision+" "+optimisation+"\n Plus "+str(zeros)+" zero precision.")
    plt.xlabel("log10(Matrix element)")
    plt.ylabel("Digits of precision")
    #delete outliers. Outlier is a value that is more than 5 standard deviations away from the mean

    matrixElementPrecision_fl = np.array(matrixElementPrecision_fl,dtype=float)
    matrix_element_fl = np.array(matrix_element_fl)

    variation = np.random.uniform(-0.4, 0.4, matrixElementPrecision_fl.size)
    matrixElementPrecision_fl += variation

    dir = "histograms"
    plt.scatter(np.log10(matrix_element_fl), matrixElementPrecision_fl, s=0.1)
    plt.savefig(dir+"/scatter_"+process+"_"+precision+"_"+optimisation[1:]+".png" )

def plotScat_MOPvsMO(process, precision, optimisation, momentaPrecision_fl, momentaPrecisionZeros, momentum_fl):
    # scatter plot of momenta precision vs momentum
    fig, ax = plt.subplots()
    zeros = momentaPrecisionZeros
    plt.title(
        "Momenta precision vs momentum_fl for: " + process + " " + precision + " " + optimisation + "\n Plus " + str(
            zeros) + " zero precision.")
    plt.xlabel("momentum_fl")
    plt.ylabel("Digits of precision")
    # delete outliers. Outlier is a value that is more than 5 standard deviations away from the mean

    momentaPrecision_fl = np.array(momentaPrecision_fl, dtype=float)
    momentum_fl = np.array(momentum_fl)

    variation = np.random.uniform(-0.4, 0.4, momentaPrecision_fl.size)
    momentaPrecision_fl += variation

    dir = "histograms"
    plt.scatter(momentum_fl, momentaPrecision_fl, s=0.01, color='black')
    plt.savefig(dir + "/scatter_momentum_fl_" + process + "_" + precision + "_" + optimisation[1:] + ".png")


def plotScat_EvsME(process, precision, optimisation, energys, matrix_element_fl):
   #Energys vs matrix element
    fig, ax = plt.subplots()
    plt.title("Energys vs matrix element precision for: "+process+" "+precision+" "+optimisation)
    plt.xlabel( "Energy")
    plt.ylabel( "Log10 of matrix element")
    #keep outliers
    plt.scatter(energys, np.log10(matrix_element_fl), s=0.01)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_energys_ME_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()

def plotHis_MEP(process, precision, optimisation, matrixElementPrecision_fl, matrixElementPrecisionZeros):
    # plot histogram of matrix element precision
    fig, ax = plt.subplots()
    plt.title("Matrix element precision for: "+process+" "+precision+" "+optimisation)
    plt.xlabel("Digits of precision.        Sum = "+str(len(matrixElementPrecision_fl)+matrixElementPrecisionZeros))
    counts, edges, bars = ax.hist(matrixElementPrecision_fl, histtype='barstacked',bins=range(0, int(max(matrixElementPrecision_fl))+2))
    plt.bar_label(bars)
    #show the mean in neat way
    plt.axvline(x=sum(matrixElementPrecision_fl)/len(matrixElementPrecision_fl), color='c', linestyle='dashed', linewidth=1)
    min_ylim, max_ylim = plt.ylim()
    plt.text(sum(matrixElementPrecision_fl)/len(matrixElementPrecision_fl), +max_ylim*0.1, 'Mean: {:.2f}'.format(sum(matrixElementPrecision_fl)/len(matrixElementPrecision_fl)),color='black')
    #show the median in neat way

    #create a directory for the histograms if it doesn't exist
    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)

    #save histogram
    plt.savefig(dir+"/histogram_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()

def plotHis_MOP(process, precision, optimisation, momentaPrecision_fl, momentaPrecisionZeros):
    # plot histogram of momenta precision
    fig, ax = plt.subplots()
    plt.title("Momenta precision for: "+process+" "+precision+" "+optimisation)
    plt.xlabel("Digits of precision.        Sum = "+str(len(momentaPrecision_fl)+momentaPrecisionZeros))
    counts, edges, bars = ax.hist(momentaPrecision_fl, histtype='barstacked',color='orange',bins=range(0, int(max(momentaPrecision_fl))+2))
    plt.bar_label(bars)
    #show the mean in neat way
    plt.axvline(x=sum(momentaPrecision_fl)/len(momentaPrecision_fl), color='c', linestyle='dashed', linewidth=1)
    min_ylim, max_ylim = plt.ylim()
    plt.text(sum(momentaPrecision_fl)/len(momentaPrecision_fl), +max_ylim*0.1, 'Mean: {:.2f}'.format(sum(momentaPrecision_fl)/len(momentaPrecision_fl)),color='black')
    #show the median in neat way

    #create a directory for the histograms if it doesn't exist
    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)

    #save histogram
    plt.savefig(dir+"/histogram_momenta_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()