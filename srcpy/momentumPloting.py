import os
import numpy as np
import matplotlib.pyplot as plt

def plotScat_COLvsMEandMEP(process, accuracy, optimisation, colinearities, matrix_element_fl, matrixElementAccuracy_fl):
    #plot scatter plot of colinearities vs Sig. digits to observe the colinearity limit
    fig, ax = plt.subplots()
    plt.title("Colinearities vs Sig. digits for: "+process+" "+accuracy+" "+optimisation)
    plt.xlabel("Colinearity")
    plt.ylabel("Sig. digits")
    #keep outliers
    y_perturbation = np.random.uniform(-0.4, 0.4, matrixElementAccuracy_fl.size)
    max_col = []
    for i in colinearities:
        max_col.append(np.max(np.abs(i)))

    '''top3_indices = np.argsort(max_col)[:3]
    print(f"The least 3 colinearities are:")
    for idx in top3_indices:
        print(f"  Event {idx}: colinearity = {max_col[idx]}")'''

    plt.scatter(max_col, matrixElementAccuracy_fl+y_perturbation,s=0.1)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_colinearities_MEP_"+process+"_"+accuracy+"_"+optimisation[1:]+".png" )
    plt.close()
    #Colinearities vs matrix element
    fig, ax = plt.subplots()
    plt.title("Max colinearities vs Sig. digits for: "+process+" "+accuracy+" "+optimisation)
    plt.xlabel("Max. abs. colinearity")
    plt.ylabel("Log10 of matrix element")
    #keep outliers
    plt.scatter(max_col, np.log10(matrix_element_fl), s=0.1)
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_colinearities_ME_"+process+"_"+accuracy+"_"+optimisation[1:]+".png" )
    plt.close()


def plotScat_EratiossMEP(process, accuracy, optimisation, energys, colinearities, matrixElementAccuracy_fl, nb_par):

    plt.title("Max Energy ratio vs Sig. digits for: "+process+" "+accuracy+" "+optimisation)
    plt.xlabel("Energy ratio")
    plt.ylabel("Sig. digits")

    max = np.max(energys, axis=1)
    min = np.min(energys, axis=1)

    ratio = max/min

    '''top3_indices = np.argsort(ratio)[-3:][::-1]
    print(f"The top 3 energy ratios are:")
    for idx in top3_indices:
        print(f"  Event {idx}: ratio = {ratio[idx]}")'''

    # Plot each particle with different color
    y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementAccuracy_fl))

    plt.scatter(ratio,
                matrixElementAccuracy_fl + y_perturbation,
                s=1,
                alpha=0.6)

    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_energys_ratios_MEP_"+process+"_"+accuracy+"_"+optimisation[1:]+".png", dpi=150)
    plt.close()


def plotScat_EvsMEP(process, accuracy, optimisation, energys, colinearities, matrixElementAccuracy_fl, nb_par, withoutFirstTwo = True):
    #Energys vs Sig. digits
    fig, ax = plt.subplots(figsize=(10, 6))
    if withoutFirstTwo:
       flag = " without first two"
       start = 2
    else:
        flag=""
        start = 0

    plt.title("Energys vs Sig. digits for: "+process+" "+accuracy+" "+optimisation+flag)
    plt.xlabel("Energy")
    plt.ylabel("Sig. digits")

    # Define colors for each particle
    colors = plt.cm.tab10(np.linspace(0, 1, nb_par))  # Use colormap for distinct colors

    # Plot each particle with different color
    for particle_idx in range(start,nb_par):
        # Get energies for this particle across all matrix elements
        particle_energies = energys[:, particle_idx]

        # Add small perturbation to avoid overlapping points
        y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementAccuracy_fl))

        plt.scatter(particle_energies,
                   matrixElementAccuracy_fl + y_perturbation,
                   s=1,
                   color=colors[particle_idx],
                   label=f'Particle {particle_idx + 1}',
                   alpha=0.6)

    plt.legend(markerscale=5)  # Make legend markers larger
    dir = "histograms/colinearities_energys_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_energys_MEP_"+process+"_"+accuracy+"_"+optimisation[1:]+".png", dpi=150)
    plt.close()

import numpy as np
import matplotlib.pyplot as plt
import os

def plot_combined(process, accuracy, optimisation,
                  energys, colinearities, matrixElementAccuracy_fl):

    max_col = np.array([np.max(np.abs(c)) for c in colinearities])
    max_E = np.max(energys, axis=1)
    min_E = np.min(energys, axis=1)
    ratio = max_E / min_E

    accuracy_arr = np.array(matrixElementAccuracy_fl)

    # Categories
    cat1 = max_col > 0.995
    cat2 = ratio > 50
    cat3 = (~cat1 & ~cat2) & (accuracy_arr < 3)
    cat4 = ~(cat1 | cat2 | cat3)

    colors = np.empty(len(max_col), dtype=object)
    colors[cat1] = "red"
    colors[cat2] = "blue"
    colors[cat3] = "green"
    colors[cat4] = "grey"

    # --- Legend statistics ---
    N = len(max_col)

    def stat(mask):
        count = np.sum(mask)
        pct = 100 * count / N
        return f"{count} ({pct:.1f}%)"

    labels = [
        f"Max. abs. collinearity > 0.995  — {stat(cat1)}",
        f"Max. energy ratio > 50     — {stat(cat2)}",
        f"Significant digits < 3 (others) — {stat(cat3)}",
        f"Remaining points       — {stat(cat4)}"
    ]

    # --- Apply jitter in accuracy for readability ---
    y_perturbation = np.random.uniform(-0.4, 0.4, N)

    # --- Plotting ---
    plt.figure(figsize=(9, 6))
    plt.title(f"Significant digits vs Maximal absolute pairwise collinearity\n{process} {accuracy} {optimisation}")
    plt.xlabel("Max. abs. collinearity")
    plt.ylabel("Sig. digits")

    plt.scatter(max_col, accuracy_arr + y_perturbation,
                s=4, c=colors, alpha=0.7)

    plt.grid(True, alpha=0.3)

    # Legend handles
    from matplotlib.lines import Line2D
    handles = [
        Line2D([0], [0], marker='o', color='w', label=labels[0],
               markerfacecolor='red', markersize=6),
        Line2D([0], [0], marker='o', color='w', label=labels[1],
               markerfacecolor='blue', markersize=6),
        Line2D([0], [0], marker='o', color='w', label=labels[2],
               markerfacecolor='green', markersize=6),
        Line2D([0], [0], marker='o', color='w', label=labels[3],
               markerfacecolor='grey', markersize=6)
    ]
    plt.tight_layout(rect=[0, 0.07, 1, 1])

    plt.legend(handles=handles,
               fontsize=9,
               loc="upper center",
               bbox_to_anchor=(0.5, -0.1),
               ncol=2)

    # --- Save ---
    outdir = f"histograms/combined_{process}"
    if not os.path.exists(outdir):
        os.makedirs(outdir)

    plt.savefig(
        outdir + f"/scatter_combined_{process}_{accuracy}_{optimisation[1:]}.png",
        dpi=200
    )
    plt.close()

def plotScat_MEvsMEP(process, accuracy, optimisation, matrixElementAccuracy_fl, matrixElementAccuracyZeros, matrix_element_fl):
    # scatter plot of Sig. digits vs matrix element
    fig, ax = plt.subplots()
    zeros = matrixElementAccuracyZeros
    plt.title("Sig. digits vs matrix element for: "+process+" "+accuracy+" "+optimisation+"\n Plus "+str(zeros)+" zero accuracy.")
    plt.xlabel("log10(Matrix element)")
    plt.ylabel("Sig. digits")
    #delete outliers. Outlier is a value that is more than 5 standard deviations away from the mean

    matrixElementAccuracy_fl = np.array(matrixElementAccuracy_fl,dtype=float)
    matrix_element_fl = np.array(matrix_element_fl)

    variation = np.random.uniform(-0.4, 0.4, matrixElementAccuracy_fl.size)
    matrixElementAccuracy_fl += variation

    dir = "histograms"
    plt.scatter(np.log10(matrix_element_fl), matrixElementAccuracy_fl, s=0.1)
    plt.savefig(dir+"/scatter_"+process+"_"+accuracy+"_"+optimisation[1:]+".png" )



def plotScat_MOPvsMO(process, accuracy, optimisation, momentaAccuracy_fl, momentaAccuracyZeros, momentum_fl):
    # scatter plot of momenta accuracy vs momentum
    fig, ax = plt.subplots()
    zeros = momentaAccuracyZeros
    plt.title(
        "Momenta accuracy vs momentum_fl for: " + process + " " + accuracy + " " + optimisation + "\n Plus " + str(
            zeros) + " zero accuracy.")
    plt.xlabel("momentum_fl")
    plt.ylabel("Sig. digits")
    # delete outliers. Outlier is a value that is more than 5 standard deviations away from the mean

    momentaAccuracy_fl = np.array(momentaAccuracy_fl, dtype=float)
    momentum_fl = np.array(momentum_fl)

    variation = np.random.uniform(-0.4, 0.4, momentaAccuracy_fl.size)
    momentaAccuracy_fl += variation

    dir = "histograms"
    plt.scatter(momentum_fl, momentaAccuracy_fl, s=0.01, color='black')
    plt.savefig(dir + "/scatter_momentum_fl_" + process + "_" + accuracy + "_" + optimisation[1:] + ".png")


def plotScat_EvsME(process, accuracy, optimisation, energys, matrix_element_fl, nb_par):
    #Energys vs matrix element
    fig, ax = plt.subplots(figsize=(10, 6))
    plt.title("Energys vs matrix element for: "+process+" "+accuracy+" "+optimisation)
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
    plt.savefig(dir+"/scatter_energys_ME_"+process+"_"+accuracy+"_"+optimisation[1:]+".png" )
    plt.close()

def plotScat_MomentumMagnitudeVsMEP(process, accuracy, optimisation, momentum, matrixElementAccuracy_fl, nb_par, withoutFirstTwo = True):
    """
    Plot 3-momentum magnitude and angles vs accuracy
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
            y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementAccuracy_fl))

            ax.scatter(particle_data,
                      matrixElementAccuracy_fl + y_perturbation,
                      s=1,
                      color=colors[particle_idx],
                      label=f'Particle {particle_idx + 1}',
                      alpha=0.6)

        ax.set_xlabel(xlabel)
        ax.set_ylabel('Sig. digits')
        ax.set_title(f'{title} vs Significant digits')
        ax.legend(markerscale=5, loc='best')
        ax.grid(True, alpha=0.3)

    plt.suptitle(f"3-Momentum Magnitude/Angles vsSignificant digits: {process} {accuracy} {optimisation} {flag}")
    plt.tight_layout()

    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_3momentum_magnitudeAngle_MEP_"+process+"_"+accuracy+"_"+optimisation[1:]+".png", dpi=150)
    plt.close()
def plotScat_MomentumComponentsVsMEP(process, accuracy, optimisation, momentum, matrixElementAccuracy_fl, nb_par, withoutFirstTwo = True):
    """
    Three separate 2D plots for px, py, pz vs Sig. digits
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
            y_perturbation = np.random.uniform(-0.4, 0.4, len(matrixElementAccuracy_fl))

            ax.scatter(component_particle,
                      matrixElementAccuracy_fl + y_perturbation,
                      s=1,
                      color=colors[particle_idx],
                      label=f'Particle {particle_idx + 1}',
                      alpha=0.6)

        ax.set_xlabel(f'{name} [GeV]')
        ax.set_ylabel('Sig. digits')
        ax.set_title(f'{name} vs Significant digits')
        ax.legend(markerscale=5, loc='best')
        ax.grid(True, alpha=0.3)

    plt.suptitle(f"Momentum Components vs Significant digits: {process} {accuracy} {optimisation} {flag}")
    plt.tight_layout()

    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_momentum_components_MEP_"+process+"_"+accuracy+"_"+optimisation[1:]+".png", dpi=150)
    plt.close()
def plotHis_MEP(process, accuracy, optimisation, matrixElementAccuracy_fl, matrixElementAccuracyZeros):
    # plot histogram of Sig. digits
    fig, ax = plt.subplots()
    plt.title("Sig. digits for: "+process+" "+accuracy+" "+optimisation)
    plt.xlabel("Sig. digits. [1]     Sum = "+str(len(matrixElementAccuracy_fl)))#'''+matrixElementAccuracyZeros'''))
    plt.ylabel("ME count [1]")
    counts, edges, bars = ax.hist(matrixElementAccuracy_fl, histtype='barstacked',bins=range(0, int(max(matrixElementAccuracy_fl))+2))
    plt.bar_label(bars)
    #show the mean in neat way
    plt.axvline(x=sum(matrixElementAccuracy_fl)/len(matrixElementAccuracy_fl), color='c', linestyle='dashed', linewidth=1)
    min_ylim, max_ylim = plt.ylim()
    plt.text(sum(matrixElementAccuracy_fl)/len(matrixElementAccuracy_fl), +max_ylim*0.1, 'Mean: {:.2f}'.format(sum(matrixElementAccuracy_fl)/len(matrixElementAccuracy_fl)),color='black')
    #show the median in neat way

    #create a directory for the histograms if it doesn't exist
    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)

    #save histogram
    plt.savefig(dir+"/histogram_"+process+"_"+accuracy+"_"+optimisation[1:]+".png" )
    plt.close()

def plotHis_MOP(process, accuracy, optimisation, momentaAccuracy_fl, momentaAccuracyZeros):
    # plot histogram of momenta accuracy
    fig, ax = plt.subplots()
    plt.title("Momenta accuracy for: "+process+" "+accuracy+" "+optimisation)
    plt.xlabel("Sig. digits.        Sum = "+str(len(momentaAccuracy_fl)))#+momentaAccuracyZeros))
    counts, edges, bars = ax.hist(momentaAccuracy_fl, histtype='barstacked',color='orange',bins=range(0, int(max(momentaAccuracy_fl))+2))
    plt.bar_label(bars)
    #show the mean in neat way
    plt.axvline(x=sum(momentaAccuracy_fl)/len(momentaAccuracy_fl), color='c', linestyle='dashed', linewidth=1)
    min_ylim, max_ylim = plt.ylim()
    plt.text(sum(momentaAccuracy_fl)/len(momentaAccuracy_fl), +max_ylim*0.1, 'Mean: {:.2f}'.format(sum(momentaAccuracy_fl)/len(momentaAccuracy_fl)),color='black')
    #show the median in neat way

    #create a directory for the histograms if it doesn't exist
    dir = "histograms"
    if not os.path.exists(dir):
        os.makedirs(dir)

    #save histogram
    plt.savefig(dir+"/histogram_momenta_"+process+"_"+accuracy+"_"+optimisation[1:]+".png" )
    plt.close()
