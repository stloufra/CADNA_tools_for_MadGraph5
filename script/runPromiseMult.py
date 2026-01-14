import os

def delete_compile_errors(subprocess_dir):
    current = os.getcwd()
    changed = False

    if not current == subprocess_dir:
        os.chdir(subprocess_dir)
        changed = True

    compil_dir = os.path.join(os.getcwd(), "boiler_plate", "compileErrors")
    debug_dir = os.path.join(os.getcwd(), "boiler_plate", "debug")

    if os.path.exists(compil_dir):
        os.system(f'rm -rf "{compil_dir}"')

    if os.path.exists(debug_dir):
        os.system(f'rm -rf "{debug_dir}"')

    if changed:
        os.chdir(current)

    

cadna_path = '"/Users/stloufra/git/CADNA_tools_for_MadGraph5/boiler_plate/promiseAnalyse.py"'

all_files = os.listdir()
P_dirs = []
for f in all_files:
    if "P1" in f:
        P_dirs.append(f)

P_dirs.sort()

base_dir = os.getcwd()
i = 0 
for P in P_dirs:
    delete_compile_errors(P)
    if not os.path.exists(base_dir + "/" + P + "/boiler_plate/output_promise_files/src/boilerplate/promiseTypes.h"):
        os.chdir(P)
        if os.path.exists("promiseAnalyse.py"):
            os.remove("promiseAnalyse.py")
        os.system('ln -s ' + cadna_path )
        print("=" *20)
        print("Working on subprocess " + P)
        print("=" *20)
        os.system("python3 promiseAnalyse.py")
        os.chdir(base_dir)
    else:
        print("=" *20)
        print("Skipped the " + str(i) + " - " + P)
        print("=" *20)
    delete_compile_errors(P)
    i = i +1
print("Finished")
    
