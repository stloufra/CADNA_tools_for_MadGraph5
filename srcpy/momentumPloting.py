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
    y_perturbation = np.random.uniform(-0.4, 0.4, matrixElementPrecision_fl.size)
    max_col = []
    for i in colinearities:
        max_col.append(np.max(np.abs(i)))

    plt.scatter(max_col, matrixElementPrecision_fl+y_perturbation,s=0.1)
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
    plt.scatter(max_col, np.log10(matrix_element_fl), s=0.1)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_colinearities_ME_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()

def plotScat_EvsMEP(process, precision, optimisation, energys, colinearities, matrixElementPrecision_fl, nb_par, withoutFirstTwo = True):
    #Energys vs matrix element precision
    fig, ax = plt.subplots(figsize=(10, 6))
    if withoutFirstTwo:
       flag = " without first two"
       start = 2
    else:
        flag=""
        start = 0

    plt.title("Energys vs matrix element precision for: "+process+" "+precision+" "+optimisation+flag)
    plt.xlabel("Energy")
    plt.ylabel("Digits of precision")

    # Define colors for each particle
    colors = plt.cm.tab10(np.linspace(0, 1, nb_par))  # Use colormap for distinct colors

    # Plot each particle with different color
    for particle_idx in range(start,nb_par):
        # Get energies for this particle across all matrix elements
        particle_energies = energys[:, particle_idx]

        # Add small perturbation to avoid overlapping points
        y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementPrecision_fl))

        plt.scatter(particle_energies,
                   matrixElementPrecision_fl + y_perturbation,
                   s=1,
                   color=colors[particle_idx],
                   label=f'Particle {particle_idx + 1}',
                   alpha=0.6)

    plt.legend(markerscale=5)  # Make legend markers larger
    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_energys_MEP_"+process+"_"+precision+"_"+optimisation[1:]+".png", dpi=150)
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


def plotScat_EvsME(process, precision, optimisation, energys, matrix_element_fl, nb_par):
    #Energys vs matrix element
    fig, ax = plt.subplots(figsize=(10, 6))
    plt.title("Energys vs matrix element for: "+process+" "+precision+" "+optimisation)
    plt.xlabel("Energy")
    plt.ylabel("Log10 of matrix element")

    # Define colors for each particle
    colors = plt.cm.tab10(np.linspace(0, 1, nb_par))  # Use colormap for distinct colors

    # Plot each particle with different color
    for particle_idx in range(nb_par):
        # Get energies for this particle across all matrix elements
        particle_energies = energys[:, particle_idx]
        plt.scatter(particle_energies,
                  np.log10(matrix_element_fl),
                   s=1,
                   color=colors[particle_idx],
                   label=f'Particle {particle_idx + 1}',
                   alpha=0.6)

    plt.legend(markerscale=5)  # Make legend markers larger

    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_energys_ME_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
    plt.close()

def plotScat_MomentumMagnitudeVsMEP(process, precision, optimisation, momentum, matrixElementPrecision_fl, nb_par, withoutFirstTwo = True):
    """
    Plot 3-momentum magnitude and angles vs precision
    momentum shape: [nb_me, nb_par, 4] where [E, px, py, pz]
    """
    if withoutFirstTwo:
       flag = " without first two"
       start = 2
    else:
        flag=""
        start = 0
    fig, axes = plt.subplots(1, 3, figsize=(18, 5))

    # Extract 3-momentum components only
    px = momentum[:, :, 1]
    py = momentum[:, :, 2]
    pz = momentum[:, :, 3]

    # Calculate 3-momentum magnitude and angles
    p_mag = np.sqrt(px**2 + py**2 + pz**2)
    theta = np.arctan2(np.sqrt(px**2 + py**2), pz)  # polar angle [0, π]
    phi = np.arctan2(py, px)  # azimuthal angle [-π, π]

    plots_data = [
        (p_mag, '|p| [GeV]', '3-Momentum Magnitude'),
        (theta, 'θ [rad]', 'Polar Angle θ'),
        (phi, 'φ [rad]', 'Azimuthal Angle φ')
    ]

    colors = plt.cm.tab10(np.linspace(0, 1, nb_par))

    for ax, (data, xlabel, title) in zip(axes, plots_data):
        for particle_idx in range(start,nb_par):
            particle_data = data[:, particle_idx]
            y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementPrecision_fl))

            ax.scatter(particle_data,
                      matrixElementPrecision_fl + y_perturbation,
                      s=1,
                      color=colors[particle_idx],
                      label=f'Particle {particle_idx + 1}',
                      alpha=0.6)

        ax.set_xlabel(xlabel)
        ax.set_ylabel('Digits of precision')
        ax.set_title(f'{title} vs Precision')
        ax.legend(markerscale=5, loc='best')
        ax.grid(True, alpha=0.3)

    plt.suptitle(f"3-Momentum Magnitude/Angles vs Precision: {process} {precision} {optimisation} {flag}")
    plt.tight_layout()

    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_3momentum_magnitudeAngle_MEP_"+process+"_"+precision+"_"+optimisation[1:]+".png", dpi=150)
    plt.close()
def plotScat_MomentumComponentsVsMEP(process, precision, optimisation, momentum, matrixElementPrecision_fl, nb_par, withoutFirstTwo = True):
    """
    Three separate 2D plots for px, py, pz vs matrix element precision
    momentum shape: [nb_me, nb_par, 4] where [E, px, py, pz]
    """
    fig, axes = plt.subplots(1, 3, figsize=(18, 5))
    if withoutFirstTwo:
        flag = " without first two"
        start = 2
    else:
        flag=""
        start = 0

    # Extract only 3-momentum components (indices 1, 2, 3)
    px = momentum[:, :, 1]  # shape: [nb_me, nb_par]
    py = momentum[:, :, 2]
    pz = momentum[:, :, 3]

    components = [px, py, pz]
    component_names = ['px', 'py', 'pz']
    colors = plt.cm.tab10(np.linspace(0, 1, nb_par))

    for comp_idx, (component, name, ax) in enumerate(zip(components, component_names, axes)):
        for particle_idx in range(start, nb_par):
            # Get component for this particle
            component_particle = component[:, particle_idx]

            # Add small perturbation to avoid overlapping points
            y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementPrecision_fl))

            ax.scatter(component_particle,
                      matrixElementPrecision_fl + y_perturbation,
                      s=1,
                      color=colors[particle_idx],
                      label=f'Particle {particle_idx + 1}',
                      alpha=0.6)

        ax.set_xlabel(f'{name} [GeV]')
        ax.set_ylabel('Digits of precision')
        ax.set_title(f'{name} vs Precision')
        ax.legend(markerscale=5, loc='best')
        ax.grid(True, alpha=0.3)

    plt.suptitle(f"Momentum Components vs Precision: {process} {precision} {optimisation} {flag}")
    plt.tight_layout()

    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_momentum_components_MEP_"+process+"_"+precision+"_"+optimisation[1:]+".png", dpi=150)
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