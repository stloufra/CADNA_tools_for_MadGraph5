#%%
import sys
import numpy as np
#open file gdb.out or one provided in argument
if len(sys.argv) > 1:
    f = open(sys.argv[1], 'r')
else:
    exit("Usage: python histogram.py <filename of ./check.exe -p -v output>")

precision = "unknown"
if "float" in sys.argv[1]:
    precision = "float"
elif "double" in sys.argv[1]:
    precision = "double"

optimisation = "unknown"
if "O0" in sys.argv[1]:
    optimisation = "-O0"
elif "O3" in sys.argv[1]:
    optimisation = "-O3"
    
    
#get current directory:
import os
cwd = os.getcwd()
process = cwd.split("/")[-1]
#split with respect to "_":
process = process.split("_")[-2]+"_"+process.split("_")[-1]

#check if there are pickle files in cwd
usingPickledData = False
'''import glob
import pickle
cwd = os.getcwd()
files = glob.glob(cwd+"/*.pickle")
if len(files) > 0:
    print("Using pickled data from cwd: "+cwd)
    usingPickledData = True
    for file in files:
        #find list_amp_sv_mag file
        if "gdb_list_amp_sv_mag" in file:
            f = open(file, "rb")
            list_amp_sv_mag = pickle.load(f)
            f.close()
            # print("Found list_amp_sv_mag in pickle file: "+file)
        #find matrixElementPrecision file
        if "gdb_matrixElementPrecision" in file:
            f = open(file, "rb")
            matrixElementPrecision = pickle.load(f)
            f.close()
            # print("Found matrixElementPrecision in pickle file: "+file)
        #find momentaPrecision file
        if "gdb_momentaPrecision" in file:
            f = open(file, "rb")
            momentaPrecision = pickle.load(f)
            f.close()
            # print("Found momentaPrecision in pickle file: "+file)
        #find matrixElement file
        if "gdb_matrixElement" in file:
            f = open(file, "rb")
            matrixElement = pickle.load(f)
            f.close()
            # print("Found matrixElement in pickle file: "+file)
        #find momentum file
        if "gdb_momentum" in file:
            f = open(file, "rb")
            momentum = pickle.load(f)
            f.close()
            # print("Found momentum in pickle file: "+file)
    
    #read info file
    filename = cwd+"/[A]_info_"+process+"_"+precision+"_"+optimisation[1:]+".txt"
    #read number of zero matrix elements and momenta
    matrixElementPrecisionZeros = 0
    momentaPrecisionZeros = 0
    for line in open(filename, "r"):
        if "Number of zero matrix elements:" in line:
            matrixElementPrecisionZeros = int(line.split(":")[1])
        if "Number of zero         momenta:" in line:
            momentaPrecisionZeros = int(line.split(":")[1])
    
    
    if usingPickledData == False:
    # find all files in directory that start with "gdb_run" has <precision> and <optimisation> in name and end with ".out"
    # and process them
    cwd = os.getcwd()
    files = os.listdir(cwd)
    files_to_process = []
    for file in files:
        if file.startswith("gdb_run") and precision in file and optimisation in file and file.endswith(".out"):
            files_to_process.append(file)
    print("Will Process:")
    for f in files_to_process:
        print(f, "Size (GB):",os.path.getsize(f)/1_000_000_000)'''


if True:
    event_number = 0
    events_processed = 0
    #get all the numbers after "Matrix element = "
    exponent = []
    matrixElement = []
    matrixElementPrecision = []
    matrixElementPrecisionZeros = 0

    momentum = []
    momentaPrecision = []
    momentaPrecisionZeros = 0

    # amp_sv_mag is a dictionary with key = function name and value = [[line number, real part, imaginary part, precision real, precision imaginary, input_precision, diagram_number],...]
    # this dictionary is for one event. It is stored in a dictionary of dictionaries called list_amp_sv_mag with key = event number and value = amp_sv_mag
    # String "Event number:" is used to find the number of event

    list_amp_sv_mag = {} # list_amp_sv_mag[event_number][function_name][line_number/real/imag/precision_real/precision_imag/input_precision, input_precision, diagram_number]


    def string_to_float(str):
        #return Nan if string is @
        if "@" in str:
            return np.nan
        else:
            #parse a string in format -0.10831E-003
            return np.float64(str.replace("D", "E"))


    files_prosessed = 0             #process files
        
            
    print("Number of matrix elements:   "+str(len(matrixElementPrecision)))
    print("Number of         momenta:   "+str(len(momentaPrecision)))
    print("Number of zero matrix elements:   "+str(matrixElementPrecisionZeros))
    print("Number of zero         momenta:   "+str(momentaPrecisionZeros))
    print("Number of events:            "+str(len(list_amp_sv_mag)))
    print("Number of matrix elements:   "+str(len(matrixElementPrecision)))
    events_processed = len(list_amp_sv_mag)
        

    files_to_process = [sys.argv[1]]  #process only one file
    for file in files_to_process:
        
        if os.path.getsize(file)/1_000_000_000 > 8:
            print("Warning file "+file+" is big (>8GB).")

        files_prosessed += 1
        f = open(file, 'r')
        #temporary variables
        last_func_name = ""
        

        print("\t\t\tprocessing file: "+file,"... Size (GB):",os.path.getsize(file)/1_000_000_000)
        for l in f:    
            if "Momenta precision:" in l:
                pos = l.find("Momenta precision: ")+len("Momenta precision: ")
                endpos = l.find("Momentum: ", pos)
                if("@" in l[pos:endpos]):
                    momentaPrecisionZeros+=1
                else:
                    momentaPrecision.append(float(l[pos:endpos]))
                endpos+= len("Momentum: ")
                momentum.append(float(l[endpos:]))
                
            if "Matrix element = " in l:
                pos = l.find("Matrix element = ")+len("Matrix element = ")
                endpos = l.find("GeV^", pos)
                # matrixElement.append(int(l[endpos+4:]))
                if("@" in l[pos:endpos]):
                    matrixElementPrecisionZeros+=1
                    if len(matrixElement)>0:
                        matrixElement.append(matrixElement[-1])
                    else:
                        matrixElement.append(1)
                else:
                    matrixElement.append(float(l[pos:endpos]))
                
            if "Matrix element number of sig dig = " in l:
                pos = l.find("Matrix element number of sig dig = ")+len("Matrix element number of sig dig = ")
                matrixElementPrecision.append(int(l[pos:pos+2]))
            
            # line in the form: 
            # <line number> f_name:       <func_name> precision real: <precision of real part> precision imag: <precision of imaginary part> amp_sv real:  <real part> amp_sv imag:  <imaginary part>
            if "amp_sv" in l:
                #get the line number
                endpos = l.find("Diag.")
                line_number = int(l[:endpos])

                pos = endpos + len("Diag.")

                endpos = l.find("f_name:")
                diag_number = int(l[pos:endpos])
                
                #get the function name
                pos = endpos+len("f_name:")
                endpos = l.find("precision real:", pos)
                func_name = l[pos:endpos].strip()
                
                #get the precision of real part
                pos = endpos+len("precision real:")
                endpos = l.find("precision imag:", pos)
                precision_real = int(l[pos:endpos].strip())
                
                #get the precision of imaginary part
                pos = endpos+len("precision imag:")
                endpos = l.find("amp_sv real:", pos)
                precision_imag = int(l[pos:endpos].strip())
                
                #get the real part
                pos = endpos+len("amp_sv real:")
                endpos = l.find("amp_sv imag:", pos)
                real = string_to_float(l[pos:endpos])
                
                #get the imaginary part
                pos = endpos+len("amp_sv imag:")
                imag = string_to_float(l[pos:])
                
                #add to dictionary
                if not func_name in list_amp_sv_mag[event_number]:
                    list_amp_sv_mag[event_number][func_name] = []
                input_precision = []
                list_amp_sv_mag[event_number][func_name].append([line_number, real, imag, precision_real, precision_imag, input_precision, diag_number])
                last_func_name = func_name
            
            #if last_func_name is not empty and the line has three ":" in it
            if last_func_name != "" and l.count(":") == 3:
                prec = l.split(" ")[1:]
                if list_amp_sv_mag[event_number][func_name][-1][5] == []:
                    for _ in range(int(len(prec)/2)):
                        list_amp_sv_mag[event_number][func_name][-1][5].append(0)
                
                for i in range(int(len(prec)/2)):  
                    list_amp_sv_mag[event_number][func_name][-1][5][i] += float(prec[2*i+1])/12
                
            if "Event number:" in l:
                event_number = int(l.split("Event number: ")[1])
                event_number = event_number + events_processed
                #create a new dictionary for this event
                list_amp_sv_mag[event_number] = {}
                
            

        f.close()
        print("Number of matrix elements:   "+str(len(matrixElementPrecision)))
        print("Number of         momenta:   "+str(len(momentaPrecision)))
        print("Number of zero matrix elements:   "+str(matrixElementPrecisionZeros))
        print("Number of zero         momenta:   "+str(momentaPrecisionZeros))
        print("Number of events:            "+str(len(list_amp_sv_mag)))
        print("Number of matrix elements:   "+str(len(matrixElementPrecision)))
        events_processed = len(list_amp_sv_mag)
        
        if len(matrixElementPrecision) != len(list_amp_sv_mag):
            exit("Number of matrix elements and number of events is not the same. file causing trouble: "+file)


        #show number of times a function was called in one event
        print("Number of times a function was called in one event (excluding multiple calls):")
        history = []
        for event_number in list_amp_sv_mag:
            if not len(list_amp_sv_mag[event_number]) in history:
                history.append(len(list_amp_sv_mag[event_number]))
                print("Event number: "+str(event_number))
                for func_name in list_amp_sv_mag[event_number]:
                    print("    "+func_name+": "+str(len(list_amp_sv_mag[event_number][func_name])))
                print("")

        #print how many events with precision of matrix element less than 10
        number = 0
        print("Number of events with precision of matrix element less than 1:")
        for event_number in list_amp_sv_mag:
            if matrixElementPrecision[event_number] < 1:
                number += 1
        print(number)
    #end of processing files
    #save stats to a file in the same directory as the histograms
    dir = "../../../histograms_functions_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    filename = dir+"/[A]_info_"+process+"_"+precision+"_"+optimisation[1:]+".txt"
    f = open(filename, "w")
    f.write("Number of matrix elements:   "+str(len(matrixElementPrecision))+"\n")
    f.write("Number of         momenta:   "+str(len(momentaPrecision))+"\n")
    f.write("Number of zero matrix elements:   "+str(matrixElementPrecisionZeros)+"\n")
    f.write("Number of zero         momenta:   "+str(momentaPrecisionZeros)+"\n")
    f.write("Number of events:            "+str(len(list_amp_sv_mag))+"\n")
    f.write("Number of matrix elements:   "+str(len(matrixElementPrecision))+"\n")
    f.close()
    cwd = os.getcwd()
    dir = cwd
    if not os.path.exists(dir):
        os.makedirs(dir)
    filename = dir+"/[A]_info_"+process+"_"+precision+"_"+optimisation[1:]+".txt"
    f = open(filename, "w")
    f.write("Number of matrix elements:   "+str(len(matrixElementPrecision))+"\n")
    f.write("Number of         momenta:   "+str(len(momentaPrecision))+"\n")
    f.write("Number of zero matrix elements:   "+str(matrixElementPrecisionZeros)+"\n")
    f.write("Number of zero         momenta:   "+str(momentaPrecisionZeros)+"\n")
    f.write("Number of events:            "+str(len(list_amp_sv_mag))+"\n")
    f.write("Number of matrix elements:   "+str(len(matrixElementPrecision))+"\n")
    f.close()

#save the dict and the lists to a file. In cwd
import pickle
cwd = os.getcwd()
if usingPickledData == False:
    for data,name in [(list_amp_sv_mag,"gdb_list_amp_sv_mag"),(matrixElementPrecision,"gdb_matrixElementPrecision"),(momentaPrecision,"gdb_momentaPrecision"),(matrixElement,"gdb_matrixElement"),(momentum,"gdb_momentum")]:
        filename = cwd+"/"+name+"_"+process+"_"+precision+"_"+optimisation[1:]+".pickle"
        f = open(filename, "wb")
        pickle.dump(data, f)
        f.close()


def find_func_name(line_number):
    for event_number in list_amp_sv_mag:
        for func_name in list_amp_sv_mag[event_number]:
            for line in list_amp_sv_mag[event_number][func_name]:
                if line[0] == line_number:
                    return func_name
    return "Not found"
    
    
import matplotlib.pyplot as plt

def size_function(x):
    num = len(x)
    s = 50/(np.sqrt(num+1))
    # print(s)
    return s
#scatter plot of precision of input to precision of output for every function
# list_amp_sv_mag[event_number][function_name][line_number/real/imag/precision_real/precision_imag/input_precision]

X = {} # input precision
Y = {} # output precision
for event_number in list_amp_sv_mag:
    for func_name in list_amp_sv_mag[event_number]:
        for line in list_amp_sv_mag[event_number][func_name]:
            if not line[0] in X:
                X[line[0]] = []
                Y[line[0]] = []
            X[line[0]].append(line[5])
            # Y[line[0]].append((line[3]+line[4])/2) #mean precision
            Y[line[0]].append( min(line[3],line[4])) #min precision

for line in X:
    fig, ax = plt.subplots()
    #make the plots bigger
    fig.set_size_inches(14, 9)
    
    fig.suptitle("Precision of input vs precision of output for function: "+func_name + " at line number: "+str(line))
    ax.set_title("Real and imaginary part")
    ax.set_xlabel("Digits of precision of input")
    ax.set_ylabel("Digits of precision of output")
    # ax.set_ylim(0, 20)
    # ax.set_xlim(0, 1000)
    # print(X[line][:3])
    temp_X = [tuple(i) for i in zip(*X[line])] # this takes the transpose of X[line]
    # print(temp_X[:3])
    i = 0
    for x in temp_X:
        i+=1
        x_perturbation = np.random.uniform(-0.4/12, 0.4/12, len(x))
        y_perturbation = np.random.uniform(-0.4/2, 0.4/2, len(x))
        ax.scatter(x+x_perturbation, Y[line]+y_perturbation,s=size_function(x),label="variable number: "+str(i))
    if len(temp_X) > 1:
        ax.legend()
        
    dir = "../../../histograms_functions_"+process+"/scatter_input_output"
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_input_output_line_"+str(line)+".png" ,dpi=100)
    plt.close()
        
    
    
#histogram of precision of real and imaginary part for each function.
# list_amp_sv_mag[event_number][function_name][line_number/real/imag/precision_real/precision_imag/input_precision]
histReal = {}
histImag = {}
for event_number in list_amp_sv_mag:
    for func_name in list_amp_sv_mag[event_number]:
        if not func_name in histReal:
            histReal[func_name] = []
            histImag[func_name] = []
        for line in list_amp_sv_mag[event_number][func_name]:
            histReal[func_name].append(line[3])
            histImag[func_name].append(line[4])

for func_name in histReal:
    if histReal[func_name] == []:
        continue
    #plot real and imaginary side by side
    fig, ax = plt.subplots(1,2)
    #make the plots wider
    fig.set_size_inches(14,9)
    fig.suptitle("Precision of real and imaginary part for function: "+func_name)
    ax[0].set_title("Real part")
    ax[1].set_title("Imaginary part")
    ax[0].set_xlabel("Digits of precision")
    ax[1].set_xlabel("Digits of precision")
    ax[0].set_ylabel("Number of times")
    ax[1].set_ylabel("Number of times")
    counts, edges, bars = ax[0].hist(histReal[func_name], histtype='barstacked',bins=range(0, int(max(histReal[func_name]))+2))
    ax[0].bar_label(bars)
    counts, edges, bars = ax[1].hist(histImag[func_name], histtype='barstacked',bins=range(0, int(max(histImag[func_name]))+2))
    ax[1].bar_label(bars)
    
    
    
    dir = "../../../histograms_functions_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/histogram_"+func_name+"_"+process+"_"+precision+"_"+optimisation[1:]+".png" ,dpi=100)
    plt.close()
    
    
#plot on x axes line number an on y mean precision of that line
# list_amp_sv_mag[event_number][function_name][line_number/real/imag/precision_real/precision_imag/input_precision]
import matplotlib.pyplot as plt
histReal = {}
histImag = {}
for event_number in list_amp_sv_mag:
    for func_name in list_amp_sv_mag[event_number]:
        if not func_name in histReal:
            histReal[func_name] = {}
            histImag[func_name] = {}
        for line in list_amp_sv_mag[event_number][func_name]:
            if not line[0] in histReal[func_name]:
                histReal[func_name][line[0]] = []
                histImag[func_name][line[0]] = []
            histReal[func_name][line[0]].append(line[3])
            histImag[func_name][line[0]].append(line[4])

for func_name in histReal:
    #plot real and imaginary in one plot
    fig, ax = plt.subplots()
    #make the plots wider
    fig.set_size_inches(14,9)
    fig.suptitle("Precision of real and imaginary part for function: "+func_name)
    ax.set_title("Real and imaginary part")
    ax.set_xlabel("Line number")
    ax.set_ylabel("Digits of precision")
    # ax.set_ylim(0, 20)
    # ax.set_xlim(0, 1000)
    
    for line_number in histReal[func_name]:
        if histReal[func_name][line_number] == []:
            continue
        #randomize the x axis a bit
        x_perturbation = np.random.uniform(-0.9, 0.9, len(histReal[func_name][line_number]))
        y_perturbation = np.random.uniform(-0.4, 0.4, len(histReal[func_name][line_number]))
        ax.scatter(np.array([line_number]*len(histReal[func_name][line_number]))+x_perturbation, np.array(histReal[func_name][line_number])+y_perturbation,s=size_function(x_perturbation),c='red',label="Real")
        x_perturbation = np.random.uniform(-0.9, 0.9, len(histReal[func_name][line_number]))
        y_perturbation = np.random.uniform(-0.4, 0.4, len(histReal[func_name][line_number]))
        ax.scatter(np.array([line_number]*len(histImag[func_name][line_number]))+x_perturbation, np.array(histImag[func_name][line_number])+y_perturbation,s=size_function(x_perturbation),c='blue',label="Imaginary")
    
    # ax.legend()
    
    
    
    dir = "../../../histograms_functions_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_"+func_name+"_"+process+"_"+precision+"_"+optimisation[1:]+".png" ,dpi=100)
    plt.close()
        
if len(matrixElementPrecision) == len(list_amp_sv_mag):
    corellate = {}
    for event_number in list_amp_sv_mag:
        for func_name in list_amp_sv_mag[event_number]:
            if not event_number in corellate:
                corellate[event_number] = []
            for line in list_amp_sv_mag[event_number][func_name]:
                # corellate[event_number].append((line[3]+line[4])/2) #mean precision
                corellate[event_number].append( min(line[3],line[4])) #min precision

    #plot on x axes mean precision of that event and on y precision of matrix element
    x = []
    y = []
    for event_number in corellate:
        for xx in corellate[event_number]:
            x.append(xx)
            y.append(matrixElementPrecision[event_number])
    
    fig, ax = plt.subplots()
    #make the plots wider
    fig.set_size_inches(14,9)
    fig.suptitle("Minimum precision of real and imaginary part for functions vs precision of matrix element")
    ax.set_title("Real and imaginary part")
    ax.set_xlabel("Minimum of precision of real and imaginary part")
    ax.set_ylabel("Digits of precision of matrix element")
    # ax.set_ylim(0, 20)
    # ax.set_xlim(0, 1000)
    y_perturbation = np.random.uniform(-0.4, 0.4, len(y))
    x_perturbation = np.random.uniform(-0.2, 0.2, len(x))
    ax.scatter(x+x_perturbation, y+y_perturbation,s=size_function(x),c='orange')
    dir = "../../../histograms_functions_"+process
    if not os.path.exists(dir):
        os.makedirs(dir)
    plt.savefig(dir+"/scatter_corellate_min_"+process+"_"+precision+"_"+optimisation[1:]+".png" ,dpi=100)
    plt.close()
    

#plot on x axes line number an on y correlation between mean precision of that line and precision of matrix element
for cutoff in range(3,9):
    MEPrec = []
    if len(matrixElementPrecision) == len(list_amp_sv_mag):
        corellate = {}
        for event_number in list_amp_sv_mag:
            if matrixElementPrecision[event_number] < cutoff :
                MEPrec.append(matrixElementPrecision[event_number])
                for func_name in list_amp_sv_mag[event_number]:
                    for line in list_amp_sv_mag[event_number][func_name]:
                        if not line[0] in corellate:
                            corellate[line[0]] = []
                        # corellate[line[0]].append((line[3]+line[4])/2) #mean precision -> remember to change axes title
                        corellate[line[0]].append( min(line[3],line[4])) #min precision
        
        x = []
        cc = [] #corellation coefficient
        for line_number in corellate:
            x.append(line_number)
            cc.append(np.corrcoef(np.array(corellate[line_number]), np.array(MEPrec))[0, 1])
            
            # plot MEPrec vs corellate[line_number] and save in /histograms_functions_"+process+/bar_corellate_lines_cutoff_<cutoff>/line_number.png
            fig, ax = plt.subplots()
            #make the plots wider
            fig.set_size_inches(14,9)
            #add random noise to the data
            y_perturbation = np.random.uniform(-0.4, 0.4, len(corellate[line_number]))
            x_perturbation = np.random.uniform(-0.1, 0.1, len(corellate[line_number]))
            
            ax.scatter(np.array(corellate[line_number])+x_perturbation , np.array(MEPrec)+y_perturbation,s=size_function(x_perturbation),c='orange')
            
            ax.set_title("Minimum precision of real and imaginary part for line "+str(line_number) +" vs precision of matrix element")
            ax.set_xlabel("Minimum precision of real and imaginary part")
            ax.set_ylabel("Digits of precision of matrix element")
            dir = "../../../histograms_functions_"+process+"/bar_corellate_lines_cutoff_"+str(cutoff)
            if not os.path.exists(dir):
                os.makedirs(dir)
            plt.savefig(dir+"/line_"+str(line_number)+"_"+process+"_"+precision+"_"+optimisation[1:]+".png" ,dpi=100)
            plt.close()
            
        
        fig, ax = plt.subplots()
        #make the plots wider
        fig.set_size_inches(18, 10)
        #bar plot
        x = np.array(x,dtype=str)
        ax.bar(x, cc,width=0.8)
        ax.set_title("Corellation coefficient with ME for cutoff "+str(cutoff)+" digits of precision")
        ax.set_xlabel("Line number")
        ax.set_ylabel("Corellation coefficient")
        
        dir = "../../../histograms_functions_"+process
        if not os.path.exists(dir):
            os.makedirs(dir)
        plt.savefig(dir+"/bar_corellate_lines_cutoff_"+str(cutoff)+"_"+process+"_"+precision+"_"+optimisation[1:]+".png" ,dpi=100)
        plt.close()
        
