import numpy as np
import os.path

try:
 import tomllib
except ImportError:
    import tomli as tomllib

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

def parse_momentum_accuracy(string):
    split = string.split() #just split by spaces
    return np.array(list(map(int, split)))

#parse the file
def parse_file(f, momentum, momentaAccuracy, matrixElement, matrixElementAccuracy, matrixElementAccuracyZeros):
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
            #parse momenta and momenta accuracy
            if "Momenta:" in l:
                j=1
                momentums=[]
                momentumsAccuracy=[]
                while not "---" in lines[i+j]:
                    momentums.append(parse_momentum(lines[i+j]))
                    if len(lines)>6:
                        momentumsAccuracy.append(parse_momentum_accuracy(lines[i+j+1]))
                        j+=1
                    j+=1
                # Add the parsed momentums to the momentum list
                if len(momentums) > 0:
                    momentum.append(momentums)
                if len(momentumsAccuracy) > 0:
                    momentaAccuracy.append(momentumsAccuracy)

            if "Matrix element = " in l and "Matrix element number of sig dig = " in lines[i+1]:
                pos = l.find("Matrix element = ")+len("Matrix element = ")
                endpos = l.find("GeV^", pos)
                # matrixElement.append(int(l[endpos+4:]))
                if("@" in l[pos:endpos]):
                    matrixElementAccuracyZeros+=1
                    if len(matrixElement)>0:
                        matrixElement.append(1) #append previous value
                    else:
                        matrixElement.append(1) #append 1 if no previous value
                else:
                    matrixElement.append(float(l[pos:endpos]))

            if "Matrix element number of sig dig = " in l:
                pos = l.find("Matrix element number of sig dig = ")+len("Matrix element number of sig dig = ")
                matrixElementAccuracy.append(int(l[pos:pos+2]))
            i+=1

        if not line:
            break
    return matrixElementAccuracyZeros

#parse the file
def parse_file_woMomP(f, momentum, matrixElement, matrixElementAccuracy, matrixElementAccuracyZeros):
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
            #parse momenta and momenta accuracy
            if "Momenta:" in l:
                j=1
                momentums=[]
                while not "---" in lines[i+j]:
                    momentums.append(parse_momentum(lines[i+j]))
                    j+=1
                # Add the parsed momentums to the momentum list
                if len(momentums) > 0:
                    momentum.append(momentums)

            if "Matrix element = " in l and "Matrix element number of sig dig = " in lines[i+1]:
                pos = l.find("Matrix element = ")+len("Matrix element = ")
                endpos = l.find("GeV^", pos)
                # matrixElement.append(int(l[endpos+4:]))
                if("@" in l[pos:endpos]):
                    matrixElementAccuracyZeros+=1
                    if len(matrixElement)>0:
                        matrixElement.append(1) #append previous value
                    else:
                        matrixElement.append(1) #append 1 if no previous value
                else:
                    matrixElement.append(float(l[pos:endpos]))

            if "Matrix element number of sig dig = " in l:
                pos = l.find("Matrix element number of sig dig = ")+len("Matrix element number of sig dig = ")
                matrixElementAccuracy.append(int(l[pos:pos+2]))
            i+=1

        if not line:
            break
    return matrixElementAccuracyZeros


def parse_file_native(f, matrixElement):
    append = matrixElement.append
    key = "Matrix element = "
    unit = "GeV"
    key_len = len(key)

    for line in f:
        pos = line.find(key)
        if pos != -1:
            end  = line.find(unit)
            if end == -1:
                raise ValueError(f"Malformed line: {line!r}")
            start = pos + key_len
            # fixed suffix " GeV^-6"
            
            append(float(line[start:end]))

#-----------------------------------------------------------------------------------
#------------------------------ ADDITIONAL FUNC ------------------------------------
#-----------------------------------------------------------------------------------

def parse_particles(particle_str):
    PARTICLES = {
        'g', 'u', 'c', 'd', 's', 'ux', 'cx', 'dx', 'sx',
        'a', 've', 'vm', 'vt', 'em', 'mum', 'vex', 'vmx', 'vtx', 'ep', 'mup',
        't', 'b', 'tx', 'bx', 'z', 'wp', 'h', 'wm', 'tam', 'tap'
    }
    PARTICLES_SORTED = sorted(PARTICLES, key=len, reverse=True)

    tokens = []
    i = 0
    while i < len(particle_str):
        matched = False
        for p in PARTICLES_SORTED:
            if particle_str[i:i + len(p)] == p:
                tokens.append(p)
                i += len(p)
                matched = True
                break
        if not matched:
            raise ValueError(f"Unknown particle token at position {i}: '{particle_str[i:]}'")
    return tokens

def get_jet_indices(folder_name, jet_particles=None):
    JET_PARTICLES = {'j', 'g', 'u', 'c', 'd', 's', 'ux', 'cx', 'dx', 'sx'}
    if jet_particles is None:
        jet_particles = JET_PARTICLES
    outgoing_str = folder_name.split('_')[2]
    outgoing = parse_particles(outgoing_str)
    return [i + 2 for i, p in enumerate(outgoing) if p in jet_particles]

class CutConfig:
    def __init__(self, process, jets, cuts):
        self.process = process
        self.jets    = jets
        self.pt      = cuts['pt']
        self.eta     = cuts['eta']
        self.mjj     = cuts['mjj']

    def __repr__(self):
        return (f"CutConfig(process={self.process}, jets={self.jets}, "
                f"pt={self.pt}, eta={self.eta}, mjj={self.mjj})")

def read_cuts(folder_name, cuts_file=None):
    DEFAULTS = {
        'process': 'non_vbf',
        'cuts': {
            'pt': 20.0,  # for VBF 30
            'eta': 4.5,
            'mjj': 20.0,  # for VBF 500
        }
    }

    config = {
        'process': DEFAULTS['process'],
        'jets':    None,
        'cuts':    DEFAULTS['cuts'].copy(),
    }

    if cuts_file is None:
        cuts_file = '../cuts.toml'

    if os.path.exists(cuts_file):
        with open(cuts_file, 'rb') as f:
            toml = tomllib.load(f)
        if 'process' in toml:
            config['process'] = toml['process']
        if 'cuts' in toml:
            config['cuts'].update(toml['cuts'])
        if 'jets' in toml:
            config['jets'] = toml['jets']

    if config['jets'] is None:
        config['jets'] = get_jet_indices(folder_name)

    return CutConfig(config['process'], config['jets'], config['cuts'])

#return colinearity for the 3vec momenta
def colinearity(m1, m2):
    m1 = m1[1:]
    m2 = m2[1:]
    #normalize
    m1 = m1/np.linalg.norm(m1)
    m2 = m2/np.linalg.norm(m2)
    return np.dot(m1,m2)

def softness(m1, m2):
    Emax = max(energy(m1), energy(m2))
    Emin = min(energy(m1), energy(m2))
    return Emax/Emin

def energy(m):
    return m[0]

def eta(m):
    #1/2*ln((|p|+z)/(|p|-z))
    px, py, pz = m[1], m[2], m[3] # E, px, py, pz
    p = np.sqrt(px**2 + py**2 + pz**2)
    return 0.5 * np.log((p + pz) / (p - pz))

def pt(m):
    # sqrt(px^2 + py^2)
    return np.sqrt(m[1]**2 + m[2]**2) # E, px, py, pz

def mjj(m1, m2):
    # sqrt((E1+E2)^2 - (px1+px2)^2 - (py1+py2)^2 - (pz1+pz2)^2)
    s = m1 + m2
    m2 = s[0]**2 - s[1]**2 - s[2]**2 - s[3]**2
    return np.sqrt(np.maximum(m2, 0.0))
