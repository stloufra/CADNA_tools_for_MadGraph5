folders=`find -type d -maxdepth 1 -name "*.sa*" `
#sort folders
folders=`echo $folders | tr " " "\n" | sort -n`
for dir0 in $folders; do
    cd $dir0
    for dir1 in `find -maxdepth 1 -name "*SubProcess*" -type d `; do
        cd $dir1
        for dir2 in `find -maxdepth 1 -name "*P*" -type d `; do
            cd $dir2
            # pwd
            ~/CERN/Cadnize.sh exact_momenta #random_seed CPPProcess
            # clear
            # pwd
            ~/CERN/test.sh float O3 &
            pwd
                # for file in `find -maxdepth 1 -name "gdb_run_output_float-O3*" -type f `; do
                #     python3 ~/CERN/histogram_functions_in_CPPProcess.py $file
                #     break
                # done
            cd ..
        done
        cd ..
    done
    cd ..
done
