# CADNA_tools_for_MadGraph5
Tools for putting CADNA in MG C++ code and mesuring the accuracy of results. Also some graphs. 

## How to use
There are 2 main scripts to run from within process directory (/SubProcess/P*/):
 - Cadnize.sh (exact_momenta) (CPPProcess) (random_seed/original_seed)
 - test.sh float/double/mixed (O3/gdb) (fortran)

Cadnize.sh arguments:
 - exact_momenta -> assumes Rambo momenta have maximum precision
 - CPPProcess -> prints out digits of precision of funtions in CPPProcess. Required for histogram_functions_in_CPPProcess.py
 - random/original_seed -> changes the seed of RAMBO to random or reverts to original. Setting to random only changes the start seed - if you compile and run the program twice the output will be the same.

test.sh arguments:
- float/double/mixed -> changes the precision. Mixed means colour algebra in float and rest in double.
- O3/gdb -> 'O3' runs with -O3 and runs ./check.exe 10000 8 1 for histogram perpouses. 'gdb' runs with -O0 and runs debugger on ./check.exe 1 8 1 - creates gdb_stats_*.out file
- fortran -> run from .mad folder. Runs ./madevent instead of ./check.exe. input to madevent is in file 'input_app.txt' in repo. Currently works only for making histograms - 'O3 fortran'

run_stats_*.out file:
 - gives the exact line number of where the instability happens.
 - shows what operator caused the problem and how many times is was invoked.
 - after displaying in terminal of vs code (less gdb_stats_*.out) ctrl + click on filename:line goes to the exact location of instability.

  ## Manually generate stats file from gdb output
  To generate gdb_stats_*.out run:
    gdb -args check.exe<gdb_c.in>gdb_stats_*.out 1 8 1
    less gdb_stats_*.out ;#(in vs code)
  You can exchange check.exe with any Cadnized code.
  


