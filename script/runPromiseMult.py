import os

cadna_path = '"/Users/stloufra/git/CADNA_tools_for_MadGraph5/boiler_plate/promiseAnalyse.py"'

all_files = os.listdir()
P_dirs = []
for f in all_files:
    if "P1" in f:
        P_dirs.append(f)

base_dir = os.getcwd()
i = 0 
for P in P_dirs:
    if i > 1:
        os.chdir(P)
        os.system('ln -s ' + cadna_path )
        print("Working on subprocess " + P)
        os.system("python3 promiseAnalyse.py")
        os.chdir(base_dir)
    else:
        print("Skipped the " + str(i))
    i = i +1
print("Finished")
    
