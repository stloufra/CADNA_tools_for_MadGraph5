CURRENT_DIR=${0%/*}
folders=`find -type d -maxdepth 1 -name "*.mad*" `
#sort folders
folders=`echo $folders | tr " " "\n" | sort -n`
for dir0 in $folders; do
    cd $dir0
    for dir1 in `find -maxdepth 1 -name "*SubProcess*" -type d `; do
        cd $dir1
        for dir2 in `find -maxdepth 1 -name "*P*" -type d `; do
            cd $dir2
            # pwd
            $CURRENT_DIR/Cadnize.sh exact_momenta CPPProcess
            # clear
            # pwd
            $CURRENT_DIR/test.sh float O3 fortran &
            pwd
                # for file in `find -maxdepth 1 -name "gdb_run_output_float-O3*" -type f `; do
                #     python3 ~/CERN/histogram_CPPProcess.py $file
                #     break
                # done
            cd ..
        done
        cd ..
    done
    cd ..
done
