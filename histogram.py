import sys
import numpy as np
import re
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
if "fgdb" in sys.argv[1]:
    optimisation += "_fortran"
    
#get current directory:
import os
cwd = os.getcwd()
process = cwd.split("/")[-1]
#split with respect to "_":
process = process.split("_")[-2]+"_"+process.split("_")[-1]


#get all the numbers after "Matrix element = "
matrixElement = []
matrixElementPrecision = []
matrixElementPrecisionZeros = 0

momentum = []
momentaPrecision = []
momentaPrecisionZeros = 0


def string_to_float(str):
    #return Nan if string is @
    if "@" in str:
        return np.nan
    else:
        #parse a string in format -0.10831E-003
        try:
            return np.float64(str.replace("D", "E"))
        except:
            print("Error parsing string: "+str)
            return np.nan

#split by spaces and minus sign that is not proceeded by "E"
def custom_split(line):
    tokens = []
    prev_i = 0
    for i in range(len(line)):
        if line[i] == " ":
            tokens.append(line[prev_i:i])
            prev_i = i+1
        elif line[i] == "-" and line[i-1] != "E":
            tokens.append(line[prev_i:i])
            prev_i = i  
    if prev_i < len(line):
        tokens.append(line[prev_i:])
    return tokens

def parse_momentum(string):
            split = custom_split(string)
            m = []
            for i in range(len(split)):
                s = split[i]
                if  s != '' and s != ' ' and s != "-":
                    m.append(s)
                    
                if s == "-":
                    split[i+1] = "-"+split[i+1]
                
            return np.array(list(map(string_to_float, m[1:])))
            
def parse_momentum_precision(string):
            split = string.split()
            return np.array(list(map(int, split)))
    
#parse the file
skipQ = True
num_iter = 0
while True:
    lines = []
    line = ""

    while skipQ:
        line = f.readline()
        if "Momenta:" in line:
            skipQ = False
            lines.append(line)
            
    while not "---" in line:
        line = f.readline()
        # print(line)
        if not line:
            break
        lines.append(line)
    num_iter += 1
    if num_iter%10000 == 0:
        print("Number iterations:", num_iter)
        
        
    i=0
    for l in lines:   
        #parse momenta and momenta precision
        if "Momenta:" in l:
            j=1
            momentums=[]
            momentumPrecision=[]
            while not "---" in lines[i+j]:
                
                momentums.append(parse_momentum(lines[i+j]))
                momentumPrecision.append(parse_momentum_precision(lines[i+j+1]))
                j+=2
            momentum.append(momentums)
            momentaPrecision.append(momentumPrecision)
                
            
        if "Matrix element = " in l and "Matrix element number of sig dig = " in lines[i+1]:
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
        i+=1
    
    if not line:
        break



matrixElement = np.array(matrixElement)
matrixElementPrecision = np.array(matrixElementPrecision)
momentum = np.array(momentum)
# print(momentum)
momentaPrecision = np.array(momentaPrecision)


print("Number of matrix elements:   "+str(len(matrixElementPrecision)))
print("Number of         momenta:   "+str(len(momentaPrecision)))
if len(momentum)>0:
    print("Number of momenta in proces:   "+str(len(momentum[0])))
    print("Number of momenta in proces:   "+str(len(momentaPrecision[0])))


#return colinearity 
def colinearity(m1, m2):
    # print(m1)
    m1 = m1[1:]
    m2 = m2[1:]
    #normalize
    m1 = m1/np.linalg.norm(m1)
    m2 = m2/np.linalg.norm(m2)
    return np.dot(m1,m2)

def energy(m):
    return m[0]

colinearities = []
for i in range(len(momentum)):
    colinearities.append(colinearity(momentum[i][0], momentum[i][-1]))
colinearities = np.array(colinearities)

energys = momentum[:,0,0]


#flatten the arrays
matrixElement =    matrixElement.flatten()
matrixElementPrecision = matrixElementPrecision.flatten()
momentum =         momentum.flatten()
momentaPrecision = momentaPrecision.flatten()
print("Number of matrix elements:        "+str(len(matrixElementPrecision)))
print("Number of         momenta:        "+str(len(momentaPrecision)))
print("Number of matrix elements prec:   "+str(len(matrixElement)))
print("Number of         momenta prec:   "+str(len(momentum)))


#matplotlib -> default (no argument) or both 
if len(sys.argv) < 3 or (len(sys.argv) > 2 and sys.argv[2] == "both"):

    import matplotlib.pyplot as plt
    
    # Colinearities vs matrix element precision and vs matrix element
    # Energys       vs matrix element precision and vs matrix element
    if len(colinearities)>0:
        #plot scatter plot of colinearities vs matrix element precision
        fig, ax = plt.subplots()
        plt.title("Colinearities vs matrix element precision for: "+process+" "+precision+" "+optimisation)
        plt.xlabel("Colinearity")
        plt.ylabel("Digits of precision")
        #keep outliers
        y_perturbation = np.random.uniform(-0.4, 0.4, colinearities.size)
        plt.scatter(colinearities, matrixElementPrecision+y_perturbation,s=0.01)
        dir = "../../../histograms/colinearities_energys_"+process
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
        plt.scatter(colinearities, np.log10(matrixElement),s=0.01)
        dir = "../../../histograms/colinearities_energys_"+process
        if not os.path.exists(dir):
            os.makedirs(dir)
        plt.savefig(dir+"/scatter_colinearities_ME_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
        plt.close()
            
        #Energys vs matrix element precision
        fig, ax = plt.subplots()
        plt.title("Energys vs matrix element precision for: "+process+" "+precision+" "+optimisation)
        plt.xlabel( "Energy")
        plt.ylabel( "Digits of precision")
        #keep outliers
        y_perturbation = np.random.uniform(-0.4, 0.4, colinearities.size)
        plt.scatter(    energys, matrixElementPrecision + y_perturbation,s=0.01)
        dir = "../../../histograms/colinearities_energys_"+process
        if not os.path.exists(dir):
            os.makedirs(dir)
        plt.savefig(dir+"/scatter_energys_MEP_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
        plt.close()
        
        #Energys vs matrix element
        fig, ax = plt.subplots()
        plt.title("Energys vs matrix element precision for: "+process+" "+precision+" "+optimisation)
        plt.xlabel( "Energy")
        plt.ylabel( "Log10 of matrix element")
        #keep outliers
        plt.scatter(    energys,    np.log10(matrixElement),s=0.01)
        dir = "../../../histograms/colinearities_energys_"+process
        if not os.path.exists(dir):
            os.makedirs(dir)
        plt.savefig(dir+"/scatter_energys_ME_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
        plt.close()
        
    
    #plot histogram of matrix element precision
    if len(matrixElementPrecision)>0:
        fig, ax = plt.subplots()
        plt.title("Matrix element precision for: "+process+" "+precision+" "+optimisation)
        plt.xlabel("Digits of precision.        Sum = "+str(len(matrixElementPrecision)+matrixElementPrecisionZeros))
        counts, edges, bars = ax.hist(matrixElementPrecision, histtype='barstacked',bins=range(0, int(max(matrixElementPrecision))+2))
        plt.bar_label(bars)
        #show the mean in neat way
        plt.axvline(x=sum(matrixElementPrecision)/len(matrixElementPrecision), color='c', linestyle='dashed', linewidth=1)
        min_ylim, max_ylim = plt.ylim()
        plt.text(sum(matrixElementPrecision)/len(matrixElementPrecision), +max_ylim*0.1, 'Mean: {:.2f}'.format(sum(matrixElementPrecision)/len(matrixElementPrecision)),color='black')
        #show the median in neat way

        #create a directory for the histograms if it doesn't exist
        dir = "../../../histograms"
        if not os.path.exists(dir):
            os.makedirs(dir)

        #save histogram
        plt.savefig(dir+"/histogram_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
        plt.close()
    
    
    
    #plot histogram of momenta precision    
    if len(momentaPrecision)>0:        
        fig, ax = plt.subplots()
        plt.title("Momenta precision for: "+process+" "+precision+" "+optimisation)
        plt.xlabel("Digits of precision.        Sum = "+str(len(momentaPrecision)+momentaPrecisionZeros))
        counts, edges, bars = ax.hist(momentaPrecision, histtype='barstacked',color='orange',bins=range(0, int(max(momentaPrecision))+2))
        plt.bar_label(bars)
        #show the mean in neat way
        plt.axvline(x=sum(momentaPrecision)/len(momentaPrecision), color='c', linestyle='dashed', linewidth=1)
        min_ylim, max_ylim = plt.ylim()
        plt.text(sum(momentaPrecision)/len(momentaPrecision), +max_ylim*0.1, 'Mean: {:.2f}'.format(sum(momentaPrecision)/len(momentaPrecision)),color='black')
        #show the median in neat way

        #create a directory for the histograms if it doesn't exist
        dir = "../../../histograms"
        if not os.path.exists(dir):
            os.makedirs(dir)

        #save histogram
        plt.savefig(dir+"/histogram_momenta_"+process+"_"+precision+"_"+optimisation[1:]+".png" )
        plt.close()
    
  

    #scatter plot of matrix element precision vs matrix element
    if len(matrixElementPrecision)>0:
        fig, ax = plt.subplots()
        zeros = matrixElementPrecisionZeros
        plt.title("Matrix element precision vs matrix element for: "+process+" "+precision+" "+optimisation+"\n Plus "+str(zeros)+" zero precision.")
        plt.xlabel("log10(Matrix element)")
        plt.ylabel("Digits of precision")
        #delete outliers. Outlier is a value that is more than 5 standard deviations away from the mean

        matrixElementPrecision = np.array(matrixElementPrecision,dtype=float)
        matrixElement = np.array(matrixElement)
        
        variation = np.random.uniform(-0.4, 0.4, matrixElementPrecision.size)
        matrixElementPrecision += variation

        plt.scatter(np.log10(matrixElement), matrixElementPrecision,s=0.1)
        plt.savefig(dir+"/scatter_"+process+"_"+precision+"_"+optimisation[1:]+".png" )    
    
    


    #scatter plot of momenta precision vs momentum
    if len(momentaPrecision)>0:
        fig, ax = plt.subplots()
        zeros = momentaPrecisionZeros
        plt.title("Momenta precision vs momentum for: "+process+" "+precision+" "+optimisation+"\n Plus "+str(zeros)+" zero precision.")
        plt.xlabel("momentum")
        plt.ylabel("Digits of precision")
        #delete outliers. Outlier is a value that is more than 5 standard deviations away from the mean

        momentaPrecision = np.array(momentaPrecision,dtype=float)
        momentum = np.array(momentum)
        
        variation = np.random.uniform(-0.4, 0.4, momentaPrecision.size)
        momentaPrecision += variation

        plt.scatter(momentum, momentaPrecision,s=0.01,color='black')
        plt.savefig(dir+"/scatter_momentum_"+process+"_"+precision+"_"+optimisation[1:]+".png" )

#Plotly only plots the last two plots and histograms:
#  - histogram of matrix element precision
#  - scatter plot of matrix element precision vs matrix element
#  - histogram of momenta precision
#  - scatter plot of momenta precision vs momentum
#plotly -> plotly or both
if len(sys.argv) > 2 and (sys.argv[2] == "plotly" or sys.argv[2] == "both"):
    #do the same using plotly
    import plotly.express as px
    # fig = px.histogram(df, x="total_bill")
    # fig.show()
    fig = px.histogram(x=matrixElementPrecision , title="Matrix element precision for: "+process+" "+precision+" "+optimisation)
    fig.show()

    #scatter plot of matrix element precision vs matrix element
    fig = px.scatter(x=np.log10(matrixElement), y=matrixElementPrecision, title="Matrix element precision vs matrix element for: "+process+" "+precision+" "+optimisation, labels={"x": "log10(Matrix element)", "y": "Digits of precision"})
    fig.show()

if len(sys.argv) > 2 and (sys.argv[2] != "plotly" and sys.argv[2] != "both"):
    exit("Usage: python histogram.py <filename of ./check.exe -p -v output> <plotly or both or nothing(for matplotlib)>")





