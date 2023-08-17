#!/bin/bash
export AVX=none
export RNDGEN=hasNoCurand
export CUDA_HOME=""


#Parameters: -O3 -O0, float_st double_st, 
#Outputs:
# time of compilation and execution
# number of errors
# Error info in file gdb_stats.out

config_file=../../src/mgOnGpuConfig.h
save_run_output=gdb_run_output
save_time=gdb_time.out

#clean files
rm -f $save_time



compile_and_run () {
    #save the double or float type
    echo   >> $save_time
    echo "running with $1 precision" >> $save_time
    echo "running with $1 precision"
    echo "optimization: $2"
    
    #if $3 is O3
    if [ "$2" == "O3" ]
    then
        for i in $(seq 1 1);
        do
            #optimalization -O3
            echo   >> $save_time
            echo  "OPTFLAGS = -O3" >> $save_time
            echo  "OPTFLAGS = -O3"

            #get random number
            random_number=$i
            

            make distclean
            echo   >> $save_time
            echo  "make time" >> $save_time
            echo  "make time" 
            
            #randomize the seed
            # ~/CERN/Cadnize.sh exact_momenta random_seed CPPProcess

            

            if [ "$3" == "fortran" ]
                then
            # Compile
                { time  make -j12 OPTFLAGS=" -O3" CUDA_HOME="" AVX=none RNDGEN=hasNoCurand; } 2>> $save_time
                echo   >> $save_time
                echo  "run time" >> $save_time
                echo  "run time" 
            # Run
                { time ./madevent_cpp < ~/CERN/input_app.txt > "f"$save_run_output"_"$1"-O3_"$random_number".out" ; } 2>> $save_time
            else
            # Compile
                { time  make -j12  OPTFLAGS=" -O3" CUDA_HOME="" AVX=none RNDGEN=hasNoCurand; } 2>> $save_time
                # { time  make -j12 check.exe OPTFLAGS=" -O3" CUDA_HOME="" AVX=none RNDGEN=hasNoCurand; } 2>> $save_time
                echo   >> $save_time
                echo  "run time" >> $save_time
                echo  "run time" 
            # Run
                { time ./check.exe 1000 8 1 -p -v > $save_run_output"_"$1"-O3_"$random_number".out" ; } 2>> $save_time
            fi

        done

        # Create a histogram of the run output
        if [ "$3" == "fortran" ]
        then
            python3 ~/CERN/histogram.py "f"$save_run_output"_"$1"-O3_"$random_number".out"
            python3 ~/CERN/histogram_functions_in_CPPProcess.py "f"$save_run_output"_"$1"-O3_"$random_number".out"
        else
            python3 ~/CERN/histogram.py $save_run_output"_"$1"-O3_"$random_number".out"
            python3 ~/CERN/histogram_functions_in_CPPProcess.py $save_run_output"_"$1"-O3_"$random_number".out"
        fi

        return
    fi
    
    if [ "$2" == "O0" ]
    then
        #optimalization -O0
        echo   >> $save_time
        echo  "OPTFLAGS = -O0 -g" >> $save_time
        echo  "OPTFLAGS = -O0 -g" 

        make distclean
        echo   >> $save_time    
        echo  "make time" >> $save_time
        echo  "make time" 
        { time  make -j12 check.exe OPTFLAGS=" -O0 -g" CUDA_HOME="" AVX=none RNDGEN=hasNoCurand; } 2>> $save_time
        echo   >> $save_time

        echo  "run time" >> $save_time
        echo  "run time" 
        { time ./check.exe 1 8 1 -p -v > $save_run_output"_"$1"-O0.out" ; } 2>> $save_time
        # Create a histogram of the run output
        python3 ~/CERN/histogram.py $save_run_output"_"$1"-O0.out"

        return
    fi

    if [ "$2" == "gdb" ]
    then
     #optimalization -O0
        echo   >> $save_time
        echo  "OPTFLAGS = -O0 -g" >> $save_time
        echo  "OPTFLAGS = -O0 -g" 

        make distclean
        echo   >> $save_time    
        echo  "make time" >> $save_time
        echo  "make time" 
        { time  make -j12 OPTFLAGS=" -O0 -g" AVX=none RNDGEN=hasNoCurand CUDA_HOME=""; } 2>> $save_time
        # { time  make -j12 check.exe OPTFLAGS=" -O0 -g" AVX=none RNDGEN=hasNoCurand CUDA_HOME=""; } 2>> $save_time # if make allows making only check.exe it speeds up the compilation
        echo   >> $save_time

        echo "Creating gdb_"$1".out file"
        echo   >> $save_time
        echo  "run gdb" >> $save_time
        echo  "run gdb"
        { time gdb -args check.exe<~/CERN/gdb_c.in>"gdb_"$1".out" 1 8 1 ; } 2>> $save_time

        echo "Running Code_tracer.py"
        python3 ~/CERN/Code_tracer.py gdb_$1.out > gdb_stats_$1.out
        echo "Done"
    fi
    
}


#check for the input is equal to "float" or "double"
if  [ "$1" != "float" ] && [ "$1" != "double" ]
then
    #Change to double_st
    sed -i 's/float_st/double_st/g' $config_file
    compile_and_run "double" "O3"
    # compile_and_run "double" "O0"
    # compile_and_run "double" "gdb"

    # Change to float_st
    sed -i 's/double_st/float_st/g' $config_file
    compile_and_run "float" "O3"
    # compile_and_run "float" "O0"
    # compile_and_run "float" "gdb"

elif [ "$1" == "float" ]
then
    #Change to float_st
    sed -i 's/double_st/float_st/g' $config_file
    compile_and_run "float" $2 $3

elif [ "$1" == "double" ]
then
    #Change to double_st
    sed -i 's/float_st/double_st/g' $config_file
    compile_and_run "double" $2 $3

fi



#clean after yourself
echo "Done Clean"
