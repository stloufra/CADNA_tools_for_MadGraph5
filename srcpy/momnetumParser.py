import numpy as np

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
        elif line[i] == "-" and line[i-1] not in "Ee":
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

        #if s == "-":
        #    split[i+1] = "-"+split[i+1]
    #map -> lazy iter -> list(regular list) -> np.array
    return np.array(list(map(string_to_float, m[1:]))) #first one is the particle number, dont want it [1:]

def parse_momentum_precision(string):
    split = string.split() #just split by spaces
    return np.array(list(map(int, split)))

#parse the file
def parse_file(f, momentum, momentaPrecision, matrixElement, matrixElementPrecision, matrixElementPrecisionZeros):
    skipQ = True
    num_iter = 0
    while True:
        lines = []
        line = ""

        while skipQ: #skip first lines until "Momenta:"
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
                momentumsPrecision=[]
                while not "---" in lines[i+j]:
                    momentums.append(parse_momentum(lines[i+j]))
                    if len(lines)>6:
                        momentumsPrecision.append(parse_momentum_precision(lines[i+j+1]))
                        j+=1
                    j+=1
                # Add the parsed momentums to the momentum list
                if len(momentums) > 0:
                    momentum.append(momentums)
                if len(momentumsPrecision) > 0:
                    momentaPrecision.append(momentumsPrecision)

            if "Matrix element = " in l and "Matrix element number of sig dig = " in lines[i+1]:
                pos = l.find("Matrix element = ")+len("Matrix element = ")
                endpos = l.find("GeV^", pos)
                # matrixElement.append(int(l[endpos+4:]))
                if("@" in l[pos:endpos]):
                    matrixElementPrecisionZeros+=1
                    if len(matrixElement)>0:
                        matrixElement.append(1) #append previous value
                    else:
                        matrixElement.append(1) #append 1 if no previous value
                else:
                    matrixElement.append(float(l[pos:endpos]))

            if "Matrix element number of sig dig = " in l:
                pos = l.find("Matrix element number of sig dig = ")+len("Matrix element number of sig dig = ")
                matrixElementPrecision.append(int(l[pos:pos+2]))
            i+=1

        if not line:
            break
    return matrixElementPrecisionZeros


def parse_file_native(f, momentum, matrixElement):
    skipQ = True
    num_iter = 0
    while True:
        lines = []
        line = ""

        while skipQ: #skip first lines until "Momenta:"
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
        if num_iter%100000 == 0:
            print("Number iterations:", num_iter)


        i=0
        for l in lines:
            #parse momenta and momenta precision
            if "Momenta:" in l:
                j=1
                momentums=[]
                while not "---" in lines[i+j]:
                    momentums.append(parse_momentum(lines[i+j]))
                    j+=1
                # Add the parsed momentums to the momentum list
                if len(momentums) > 0:
                    momentum.append(momentums)

            if "Matrix element = " in l:
                pos = l.find("Matrix element = ")+len("Matrix element = ")
                endpos = l.find("GeV^", pos)
                # matrixElement.append(int(l[endpos+4:]))
                matrixElement.append(float(l[pos:endpos]))

            i+=1

        if not line:
            break
    return
#return colinearity for the 3vec momenta
def colinearity(m1, m2):
    m1 = m1[1:]
    m2 = m2[1:]
    #normalize
    m1 = m1/np.linalg.norm(m1)
    m2 = m2/np.linalg.norm(m2)
    return np.dot(m1,m2)

def energy(m):
    return m[0]
