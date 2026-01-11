#This script should be copied into the Subprocess folder and automatically run the promise analysis on the subprocess
#Prequiments are: generated process and results in gdb_run_output_float-03_1.out file

# -------------------------------
# Step 1: Creating the boilerplate
# -------------------------------

import os
import shutil

# create dir and cd
# TODO: make a env. var.
CADNA_toolbox_path = "/Users/stloufra/git/CADNA_tools_for_MadGraph5/boiler_plate"
PROMISE_env_path = '/Users/stloufra/git/promiseOld/.venv/bin/activate'
Current_path = os.getcwd()
os.makedirs(Current_path + "/boiler_plate", exist_ok=True)
os.chdir(Current_path + "/boiler_plate")
# Update Current_path to the new working directory
Current_path = os.getcwd()

#copy from toolbox
print("Copying files from toolbox:")
COPY_FILES = ["CMakeLists.txt", "main.cpp", "make_boilerplate.sh", "promise.yml", "src"]
for file in COPY_FILES:
    #print(file)
    src = os.path.join(CADNA_toolbox_path, file)
    dst = os.path.join(Current_path, file)
    
    # Remove destination if it exists to avoid copytree errors
    if os.path.exists(dst):
        if os.path.isdir(dst):
            shutil.rmtree(dst)
        else:
            os.remove(dst)
            
    if os.path.isdir(src):
        shutil.copytree(src, dst)
    else:
        shutil.copy2(src, dst)

FILES_SRC = ["CPPProcess.cc", "CPPProcess.h", "HelAmps_sm.h", "color_sum.h", "color_sum.cc"]
FILES_SRC_BCKP = ["HelAmps_sm_bckp", "CPPProcess_bckp"]
FILES_BOILER = ["Parameters_sm.cc", "Parameters_sm.h"]
FILES_CARDS = ["param_card.dat"]
FILES_MAIN = ["gdb_run_output_float-03_1.out"]

#check for old files and remove
print("Removing old files:")
for f in FILES_SRC:
    if os.path.exists("src/" + f):
        #print("Removing src/" + f)
        os.remove("src/" + f)
for f in FILES_SRC_BCKP:
    if os.path.exists("src/" + f):
        #print("Removing src/" + f)
        os.remove("src/" + f)
for f in FILES_BOILER:
    if os.path.exists("src/boilerplate/" + f):
        #print("Removing src/boilerplate" + f)
        os.remove("src/boilerplate/" + f)
for f in FILES_CARDS:
    if os.path.exists("src/Cards/" + f):
        #print("Removing Cards/" + f)
        os.remove("src/Cards/" + f)
for f in FILES_MAIN:
    if os.path.exists(f):
        #print("Removing from main" + f)
        os.remove(f)

#copy the new files
print("Copying new files")
shutil.copy2("../../../src/Parameters_sm.h", "src/boilerplate")
shutil.copy2("../../../src/Parameters_sm.cc", "src/boilerplate")
shutil.copy2("../../../Cards/param_card.dat", "src/Cards")
shutil.copy2("../gdb_run_output_float-O3_1.out", Current_path)
shutil.copy2("../../../src/HelAmps_sm.h", "src")
shutil.copy2('../color_sum.cc', 'src')
shutil.copy2('../../color_sum.h', 'src')
shutil.copy2('../CPPProcess.cc', 'src')
shutil.copy2('../CPPProcess.h', 'src')

#make boilerplate
print("Making boilerplate")
os.system("./make_boilerplate.sh")

#promises HelAmps_sm.h
print("Promises HelAmps_sm.h")
os.chdir(Current_path+"/src")
os.system("python3 promisesHelAmps.py")
os.chdir(Current_path)

#source promise enviroment
print("Sourcing promise environment")
os.system("source " + PROMISE_env_path)
os.system("promise --precs=sd --nbDigits=3 --debug --verbosity=4")




