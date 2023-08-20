#!/bin/bash
CURRENT_DIR=${0%/*}
# echo $CURRENT_DIR

#check if CPPProcess.cc exists


                # Change to cudacpp.mk
#in the line "LIBFLAGS = -L$(LIBDIR) -l$(MG5AMC_COMMONLIB)" append -lcadnaOpenmpCdebug
#if there is no -lcadnaOpenmpCdebug in the file
if grep -Fq cadnaOpenmpCdebug ../cudacpp.mk
then
    echo "cadnaOpenmpCdebug is already in ../cudacpp.mk"
else
    echo "putting -lcadnaOpenmpCdebug in ../cudacpp.mk"
    sed -i 's/LIBFLAGS = -L$(LIBDIR) -l$(MG5AMC_COMMONLIB)/LIBFLAGS = -L$(LIBDIR) -l$(MG5AMC_COMMONLIB) -lcadnaOpenmpCdebug/g' ../cudacpp.mk
fi

                # Change to ../makefile
#in the line "LIBFLAGS = -L$(LIBDIR) -l$(MG5AMC_COMMONLIB)" append -lcadnaOpenmpCdebug
#if there is no -lcadnaOpenmpCdebug in the file
#check if ../makefile exists:
if [ -f "../makefile" ]
then
    if grep -Fq cadnaOpenmpCdebug ../makefile
    then
        echo "cadnaOpenmpCdebug is already in ../makefile"
    else
        echo "putting -lcadnaOpenmpCdebug in ../makefile"
        sed -i 's/LINKLIBS = $(LINK_MADLOOP_LIB) $(LINK_LOOP_LIBS) -L$(LIBDIR) -ldhelas -ldsample -lmodel -lgeneric -lpdf -lcernlib $(llhapdf) -lbias/LINKLIBS = $(LINK_MADLOOP_LIB) $(LINK_LOOP_LIBS) -L$(LIBDIR) -ldhelas -ldsample -lmodel -lgeneric -lpdf -lcernlib $(llhapdf) -lbias -lcadnaOpenmpCdebug/g' ../makefile
    fi
fi
                # move every $(LIBFLAGS)  and $(LINKLIBS) to the end of the line in ../cudacpp.mk and ../makefile
echo
echo "          cadnize_libflags.py"
python3 $CURRENT_DIR/cadnize_libflags.py ../cudacpp.mk
#check if ../makefile exists:
if [ -f "../makefile" ]
then
    python3 $CURRENT_DIR/cadnize_libflags.py ../makefile
fi


                #changes in mgOnGpuConfig.h
#add cadna.h at 100th line if there is no cadna.h
#if there is no -lcadnaOpenmpCdebug in the file
if grep -Fq cadna.h ../../src/mgOnGpuConfig.h
then
    echo "cadna.h is already in mgOnGpuConfig.h"
else
    sed -i '100i #include <cadna.h>' ../../src/mgOnGpuConfig.h
fi
#if there is no #undef MGONGPU_CPPSIMD in the file
if grep -Fq 'undef MGONGPU_CPPSIMD //for CADNA' ../../src/mgOnGpuConfig.h
then
    echo "#undef MGONGPU_CPPSIMD is already in mgOnGpuConfig.h"
else
    sed -i '177i #undef MGONGPU_CPPSIMD //for CADNA' ../../src/mgOnGpuConfig.h
fi
#change "typedef double fptyp to typedef double_st fptyp" in mgOnGpuConfig.h
sed -i 's/typedef double fptyp/typedef double_st fptyp/g' ../../src/mgOnGpuConfig.h


                #Changes in check_sa.cc and bridge
echo
echo "          cadnize_check_sa.py"
python3 $CURRENT_DIR/cadnize_check_sa.py check_sa.cc
python3 $CURRENT_DIR/cadnize_bridge.py ../Bridge.h

                #repair the std::fun() error, comment some functions and add some castings to (double)
echo
echo "          cadnize_std_replace.py"
files=(../../src/mgOnGpuFptypes.h ../../src/HelAmps_sm.h ../CrossSectionKernels.cc fsampler.cc MadgraphTest.h testxxx.cc runTest.cc)
for file in "${files[@]}"
do
    python3  $CURRENT_DIR/cadnize_std_replace.py $file
done


                #repair the constexpr fptype and volatile fptype errors
echo
echo "          cadnize_constexpr_replace.py"
#  loop over list of files
files=(check_sa.cc ../../src/HelAmps_sm.h CPPProcess.cc fsampler.cc MadgraphTest.h testxxx.cc runTest.cc)
for file in "${files[@]}"
do
    python3 $CURRENT_DIR/cadnize_constexpr_replace.py $file
done


                #paste "\n" after every operator after every "=" in HelAmps_sm.h - make optional
python3 $CURRENT_DIR/cadnize_expand_equations.py ../../src/HelAmps_sm.h


 #change this
                #Make output of phase space picker exact numbers
if [ "$1" == "exact_momenta" ] ||  [ "$2" == "exact_momenta" ] ||  [ "$3" == "exact_momenta" ] ||  [ "$4" == "exact_momenta" ] || [ "$5" == "exact_momenta" ] ||  [ "$6" == "exact_momenta" ] ||  [ "$7" == "exact_momenta" ] ||  [ "$8" == "exact_momenta" ] ||  [ "$9" == "exact_momenta" ] ||  [ "${10}" == "exact_momenta" ] ||  [ "${11}" == "exact_momenta" ] ||  [ "${12}" == "exact_momenta" ] ||  [ "${13}" == "exact_momenta" ] ||  [ "${14}" == "exact_momenta" ] ||  [ "${15}" == "exact_momenta" ] ||  [ "${16}" == "exact_momenta" ] ||  [ "${17}" == "exact_momenta" ] ||  [ "${18}" == "exact_momenta" ] ||  [ "${19}" == "exact_momenta" ] ||  [ "${20}" == "exact_momenta" ] ||  [ "${21}" == "exact_momenta" ] ||  [ "${22}" == "exact_momenta" ] ||  [ "${23}" == "exact_momenta" ] ||  [ "${24}" == "exact_momenta" ] ||  [ "${25}" == "exact_momenta" ] ||  [ "${26}" == "exact_momenta" ] ||  [ "${27}" == "exact_momenta" ] ||  [ "${28}" == "exact_momenta" ] ||  [ "${29}" == "exact_momenta" ] ||  [ "${30}" == "exact_momenta" ] ||  [ "${31}" == "exact_momenta" ] ||  [ "${32}" == "exact_momenta" ] ||  [ "${33}" == "exact_momenta" ] ||  [ "${34}" == "exact_momenta" ] ||  [ "${35}" == "exact_momenta" ] ||  [ "${36}" == "exact_momenta" ] ||  [ "${37}" == "exact_momenta" ] ||  [ "${38}" == "exact_momenta" ] ||  [ "${39}" == "exact_momenta" ] 
then
    python3 $CURRENT_DIR/cadnize_exact_momenta.py ../../src/rambo.h
fi

                #Make output of phase space picker exact numbers
if [ "$1" == "load_momenta" ] ||  [ "$2" == "load_momenta" ] ||  [ "$3" == "load_momenta" ] || [ "$4" == "load_momenta" ] || [ "$5" == "load_momenta" ] ||  [ "$6" == "load_momenta" ] ||  [ "$7" == "load_momenta" ] ||  [ "$8" == "load_momenta" ] ||  [ "$9" == "load_momenta" ] ||  [ "${10}" == "load_momenta" ] ||  [ "${11}" == "load_momenta" ] ||  [ "${12}" == "load_momenta" ] ||  [ "${13}" == "load_momenta" ] ||  [ "${14}" == "load_momenta" ] ||  [ "${15}" == "load_momenta" ] ||  [ "${16}" == "load_momenta" ] ||  [ "${17}" == "load_momenta" ] ||  [ "${18}" == "load_momenta" ] ||  [ "${19}" == "load_momenta" ] ||  [ "${20}" == "load_momenta" ] ||  [ "${21}" == "load_momenta" ] ||  [ "${22}" == "load_momenta" ] ||  [ "${23}" == "load_momenta" ] ||  [ "${24}" == "load_momenta" ] ||  [ "${25}" == "load_momenta" ] ||  [ "${26}" == "load_momenta" ] ||  [ "${27}" == "load_momenta" ] ||  [ "${28}" == "load_momenta" ] ||  [ "${29}" == "load_momenta" ] ||  [ "${30}" == "load_momenta" ] ||  [ "${31}" == "load_momenta" ] ||  [ "${32}" == "load_momenta" ] ||  [ "${33}" == "load_momenta" ] ||  [ "${34}" == "load_momenta" ] ||  [ "${35}" == "load_momenta" ] ||  [ "${36}" == "load_momenta" ] ||  [ "${37}" == "load_momenta" ] ||  [ "${38}" == "load_momenta" ] || [ "$1" == "read_momenta" ] ||  [ "$2" == "read_momenta" ] || [ "$3" == "read_momenta" ] || [ "$4" == "read_momenta" ] || [ "$5" == "read_momenta" ] ||  [ "$6" == "read_momenta" ] ||  [ "$7" == "read_momenta" ] ||  [ "$8" == "read_momenta" ] ||  [ "$9" == "read_momenta" ] ||  [ "${10}" == "read_momenta" ] ||  [ "${11}" == "read_momenta" ] ||  [ "${12}" == "read_momenta" ] ||  [ "${13}" == "read_momenta" ] ||  [ "${14}" == "read_momenta" ] ||  [ "${15}" == "read_momenta" ] ||  [ "${16}" == "read_momenta" ] ||  [ "${17}" == "read_momenta" ] ||  [ "${18}" == "read_momenta" ] ||  [ "${19}" == "read_momenta" ] ||  [ "${20}" == "read_momenta" ] ||  [ "${21}" == "read_momenta" ] ||  [ "${22}" == "read_momenta" ] ||  [ "${23}" == "read_momenta" ] ||  [ "${24}" == "read_momenta" ] ||  [ "${25}" == "read_momenta" ] ||  [ "${26}" == "read_momenta" ] ||  [ "${27}" == "read_momenta" ] ||  [ "${28}" == "read_momenta" ] ||  [ "${29}" == "read_momenta" ] ||  [ "${30}" == "read_momenta" ] ||  [ "${31}" == "read_momenta" ] ||  [ "${32}" == "read_momenta" ] ||  [ "${33}" == "read_momenta" ] ||  [ "${34}" == "read_momenta" ] ||  [ "${35}" == "read_momenta" ] ||  [ "${36}" == "read_momenta" ] ||  [ "${37}" == "read_momenta" ] ||  [ "${38}" == "read_momenta" ] 
then
    python3 $CURRENT_DIR/cadnize_exact_momenta.py ../../src/rambo.h
    python3 $CURRENT_DIR/cadnize_exact_momenta_to_load_momenta.py ../../src/rambo.h $CURRENT_DIR/read_momenta.h
fi

                #cout every amp_fp after a function call
if [ "$1" == "CPPProcess" ] ||  [ "$2" == "CPPProcess" ] ||  [ "$3" == "CPPProcess" ] || [ "$4" == "CPPProcess" ] || [ "$5" == "CPPProcess" ] ||  [ "$6" == "CPPProcess" ] ||  [ "$7" == "CPPProcess" ] ||  [ "$8" == "CPPProcess" ] ||  [ "$9" == "CPPProcess" ] ||  [ "${10}" == "CPPProcess" ] ||  [ "${11}" == "CPPProcess" ] ||  [ "${12}" == "CPPProcess" ] ||  [ "${13}" == "CPPProcess" ] ||  [ "${14}" == "CPPProcess" ] ||  [ "${15}" == "CPPProcess" ] ||  [ "${16}" == "CPPProcess" ] ||  [ "${17}" == "CPPProcess" ] ||  [ "${18}" == "CPPProcess" ] ||  [ "${19}" == "CPPProcess" ] ||  [ "${20}" == "CPPProcess" ] ||  [ "${21}" == "CPPProcess" ] ||  [ "${22}" == "CPPProcess" ] ||  [ "${23}" == "CPPProcess" ] ||  [ "${24}" == "CPPProcess" ] ||  [ "${25}" == "CPPProcess" ] ||  [ "${26}" == "CPPProcess" ] ||  [ "${27}" == "CPPProcess" ] ||  [ "${28}" == "CPPProcess" ] ||  [ "${29}" == "CPPProcess" ] ||  [ "${30}" == "CPPProcess" ] ||  [ "${31}" == "CPPProcess" ] ||  [ "${32}" == "CPPProcess" ] ||  [ "${33}" == "CPPProcess" ] ||  [ "${34}" == "CPPProcess" ] ||  [ "${35}" == "CPPProcess" ] ||  [ "${36}" == "CPPProcess" ] ||  [ "${37}" == "CPPProcess" ] ||  [ "${38}" == "CPPProcess" ] ||  [ "${39}" == "CPPProcess" ] 
then
    python3 $CURRENT_DIR/cadnize_CPPProcess_cout_amp_fp.py CPPProcess.cc
fi

                #set the seed random or original
if [ "$1" == "random_seed" ] ||  [ "$2" == "random_seed" ] ||  [ "$3" == "random_seed" ] || [ "$4" == "random_seed" ] || [ "$5" == "random_seed" ] ||  [ "$6" == "random_seed" ] ||  [ "$7" == "random_seed" ] ||  [ "$8" == "random_seed" ] ||  [ "$9" == "random_seed" ] ||  [ "${10}" == "random_seed" ] ||  [ "${11}" == "random_seed" ] ||  [ "${12}" == "random_seed" ] ||  [ "${13}" == "random_seed" ] ||  [ "${14}" == "random_seed" ] ||  [ "${15}" == "random_seed" ] ||  [ "${16}" == "random_seed" ] ||  [ "${17}" == "random_seed" ] ||  [ "${18}" == "random_seed" ] ||  [ "${19}" == "random_seed" ] ||  [ "${20}" == "random_seed" ] ||  [ "${21}" == "random_seed" ] ||  [ "${22}" == "random_seed" ] ||  [ "${23}" == "random_seed" ] ||  [ "${24}" == "random_seed" ] ||  [ "${25}" == "random_seed" ] ||  [ "${26}" == "random_seed" ] ||  [ "${27}" == "random_seed" ] ||  [ "${28}" == "random_seed" ] ||  [ "${29}" == "random_seed" ] ||  [ "${30}" == "random_seed" ] ||  [ "${31}" == "random_seed" ] ||  [ "${32}" == "random_seed" ] ||  [ "${33}" == "random_seed" ] ||  [ "${34}" == "random_seed" ] ||  [ "${35}" == "random_seed" ] ||  [ "${36}" == "random_seed" ] ||  [ "${37}" == "random_seed" ] ||  [ "${38}" == "random_seed" ] ||  [ "${39}" == "random_seed" ] 
then
    python3 $CURRENT_DIR/cadnize_seed_change.py check_sa.cc random
fi

                #set the seed random or original
if [ "$1" == "original_seed" ] ||  [ "$2" == "original_seed" ] ||  [ "$3" == "original_seed" ] || [ "$4" == "original_seed" ] || [ "$5" == "original_seed" ] ||  [ "$6" == "original_seed" ] ||  [ "$7" == "original_seed" ] ||  [ "$8" == "original_seed" ] ||  [ "$9" == "original_seed" ] ||  [ "${10}" == "original_seed" ] ||  [ "${11}" == "original_seed" ] ||  [ "${12}" == "original_seed" ] ||  [ "${13}" == "original_seed" ] ||  [ "${14}" == "original_seed" ] ||  [ "${15}" == "original_seed" ] ||  [ "${16}" == "original_seed" ] ||  [ "${17}" == "original_seed" ] ||  [ "${18}" == "original_seed" ] ||  [ "${19}" == "original_seed" ] ||  [ "${20}" == "original_seed" ] ||  [ "${21}" == "original_seed" ] ||  [ "${22}" == "original_seed" ] ||  [ "${23}" == "original_seed" ] ||  [ "${24}" == "original_seed" ] ||  [ "${25}" == "original_seed" ] ||  [ "${26}" == "original_seed" ] ||  [ "${27}" == "original_seed" ] ||  [ "${28}" == "original_seed" ] ||  [ "${29}" == "original_seed" ] ||  [ "${30}" == "original_seed" ] ||  [ "${31}" == "original_seed" ] ||  [ "${32}" == "original_seed" ] ||  [ "${33}" == "original_seed" ] ||  [ "${34}" == "original_seed" ] ||  [ "${35}" == "original_seed" ] ||  [ "${36}" == "original_seed" ] ||  [ "${37}" == "original_seed" ] ||  [ "${38}" == "original_seed" ] ||  [ "${39}" == "original_seed" ] 
then
    python3 $CURRENT_DIR/cadnize_seed_change.py check_sa.cc original
fi
