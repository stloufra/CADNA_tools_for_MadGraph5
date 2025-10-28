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
    sed -i 's/-L$(LIBDIR) -l$(MG5AMC_COMMONLIB)/-L$(LIBDIR) -l$(MG5AMC_COMMONLIB) -lcadnaOpenmpCdebug -fopenmp/g' ../cudacpp.mk
fi
                # Change to ../makefile
#in the line "LIBFLAGS = -L$(LIBDIR) -l$(MG5AMC_COMMONLIB)" append -lcadnaOpenmpCdebug
#if there is no -lcadnaOpenmpCdebug in the file
#check if ../makefile exists:
#sed -i 's/LINKLIBS = $(LINK_MADLOOP_LIB) $(LINK_LOOP_LIBS) -L$(LIBDIR) -ldhelas -ldsample -lmodel -lgeneric -lpdf -lcernlib $(llhapdf) -lbias/LINKLIBS = $(LINK_MADLOOP_LIB) $(LINK_LOOP_LIBS) -L$(LIBDIR) -ldhelas -ldsample -lmodel -lgeneric -lpdf -lcernlib $(llhapdf) -lbias -lcadnaOpenmpCdebug/g' ../makefile_original.mk
if [ -f "../makefile_original.mk" ]
then
    if grep -Fq cadnaOpenmpCdebug ../makefile_original.mk
    then
        echo "cadnaOpenmpCdebug is already in ../makefile_original.mk"
    else
        echo "putting -lcadnaOpenmpCdebug in ../makefile_original.mk"

        sed -i 's/LINKLIBS = $(LINK_MADLOOP_LIB) $(LINK_LOOP_LIBS) -L\.\.\/\.\.\/lib\/ -ldhelas -ldsample -lmodel -lgeneric -lpdf -lgammaUPC -lcernlib $(llhapdf) -lbias/LINKLIBS = $(LINK_MADLOOP_LIB) $(LINK_LOOP_LIBS) -L..\/..\/lib\/ -ldhelas -ldsample -lmodel -lgeneric -lpdf -lgammaUPC -lcernlib $(llhapdf) -lbias -lcadnaOpenmpCdebug/g' ../makefile_original.mk
    fi
fi


          #add missing definition for operators on custom complex types
if [ -f "../../src/mgOnGpuCxtypes.h" ]
then
    if grep -Fq "CADNA operator overload" ../../src/mgOnGpuCxtypes.h
    then
        echo "CADNA operator overload is already in ../../src/mgOnGpuCxtypes.h"
    else
        echo "putting CADNA operator overload in ../../src/mgOnGpuCxtypes.h"

       sed -i '292i\
  \n//CADNA operator overload\
  template<typename T>\
    constexpr bool is_special_fp_v =\
    std::is_same_v<T, double_st> || std::is_same_v<T, float_st>;\
\
  template<typename FP, typename FP2,\
         std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>\
  inline __host__ __device__ constexpr cxsmpl<FP>\
  operator+( const cxsmpl<FP>& a, const cxsmpl<FP2>& b )\
  {\
    return cxsmpl<FP>( a.real() + b.real(), a.imag() + b.imag() );\
  }\
\
  template<typename FP, typename FP2,\
          std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>\
   inline __host__ __device__ constexpr cxsmpl<FP>\
   operator-( const cxsmpl<FP>& a, const cxsmpl<FP2>& b )\
  {\
    return cxsmpl<FP>( a.real() - b.real(), a.imag() - b.imag() );\
  }\
\
  template<typename FP, typename FP2,\
          std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>\
   inline __host__ __device__ constexpr cxsmpl<FP>\
   operator*( const cxsmpl<FP>& a, const cxsmpl<FP2>& b )\
  {\
    return cxsmpl<FP>( a.real() * b.real() - a.imag() * b.imag(), a.imag() * b.real() + a.real() * b.imag() );\
  }\
\
  template<typename FP, typename FP2,\
            std::enable_if_t<is_special_fp_v<FP> || is_special_fp_v<FP2>, int> = 0>\
     inline __host__ __device__ constexpr cxsmpl<FP>\
     operator/( const cxsmpl<FP>& a, const cxsmpl<FP2>& b )\
  {\
    FP bnorm = b.real() * b.real() + b.imag() * b.imag();\
    return cxsmpl<FP>( ( a.real() * b.real() + a.imag() * b.imag() ) / bnorm,\
                       ( a.imag() * b.real() - a.real() * b.imag() ) / bnorm );\
  }' ../../src/mgOnGpuCxtypes.h
    fi
else
  echo "../../src/mgOnGpuCxtypes.h does not exist"
fi

           #changes in mgOnGpuConfig.h
#add cadna.h at 100th line if there is no cadna.h
#if there is no -lcadnaOpenmpCdebug in the file
#TODO try safer way to do this
if grep -Fq cadna.h ../../src/mgOnGpuConfig.h
then
    echo "cadna.h is already in mgOnGpuConfig.h"
else
    sed -i '91i #include <cadna.h>' ../../src/mgOnGpuConfig.h
fi
#if there is no #undef MGONGPU_CPPSIMD in the file
if grep -Fq 'undef MGONGPU_CPPSIMD //for CADNA' ../../src/mgOnGpuConfig.h
then
    echo "#undef MGONGPU_CPPSIMD is already in mgOnGpuConfig.h"
else
    sed -i '252i #undef MGONGPU_CPPSIMD //for CADNA' ../../src/mgOnGpuConfig.h
fi
#change "typedef double fptyp to typedef double_st fptyp" in mgOnGpuConfig.h
sed -i 's/typedef double fptyp/typedef double_st fptyp/g' ../../src/mgOnGpuConfig.h

                # move every $(LIBFLAGS)  and $(LINKLIBS) to the end of the line in ../cudacpp.mk and ../makefile
echo
echo "          cadnize_libflags.py"
python3 $CURRENT_DIR/cadnize_libflags.py ../cudacpp.mk
#check if ../makefile exists:
if [ -f "../makefile" ]
then
    python3 $CURRENT_DIR/cadnize_libflags.py ../makefile_original.mk
fi


                #Changes in check_sa.cc and bridge
echo
echo "          cadnize_check_sa.py"
python3 $CURRENT_DIR/cadnize_check_sa.py check_sa.cc

                #Changes in check_sa.cc and bridge
echo
echo "          cadnize_bridge.py"
python3 $CURRENT_DIR/cadnize_bridge.py ../Bridge.h
#TODO check if the bridge in the supprocess individual directory needs to be checked as well


                #repair the constexpr fptype and volatile fptype errors
echo
echo "          cadnize_constexpr_replace.py"
#  loop over list of files
files=(check_sa.cc ../../src/HelAmps_sm.h CPPProcess.cc fsampler.cc MadgraphTest.h testxxx.cc runTest.cc color_sum.cc testmisc.cc)
for file in "${files[@]}"
do
    python3 $CURRENT_DIR/cadnize_constexpr_replace.py $file
done
                #paste "\n" after every operator after every "=" in HelAmps_sm.h - make optional
python3 $CURRENT_DIR/cadnize_expand_equations.py ../../src/HelAmps_sm.h

echo
echo "          cadnize_std_replace.py"
files=(../../src/mgOnGpuFptypes.h ../../src/HelAmps_sm.h ../CrossSectionKernels.cc fsampler.cc MadgraphTest.h testxxx.cc runTest.cc)
for file in "${files[@]}"
do
    python3  $CURRENT_DIR/cadnize_std_replace.py $file
done


#care for the additional options

                #Make output of phase space picker exact numbers
if [[ " $* " =~ " exact_momenta" ]]; then
    echo
    echo "          cadnize_exact_momenta.py"
    python3 $CURRENT_DIR/cadnize_exact_momenta.py ../../src/rambo.h
fi

#does not work for now (dont know the contents of the read_momenta.h)
if [[ " $* " =~ " load_momenta" ]]; then
    echo
    echo "          cadnize_exact_momenta.py + cadnize_exact_momenta_to_load_momenta.py"
    python3 $CURRENT_DIR/cadnize_exact_momenta.py ../../src/rambo.h
    python3 $CURRENT_DIR/cadnize_exact_momenta_to_load_momenta.py ../../src/rambo.h $CURRENT_DIR/read_momenta.h
fi


                #cout every amp_fp after a function call
if [[ " $* " =~ " CPPProcess" ]]; then
    echo
    echo "         cadnize_cppprocess_cout_amp_fp"
    python3 $CURRENT_DIR/cadnize_CPPProcess_cout_amp_fp.py CPPProcess.cc
fi

                #set the seed random or original
if [[ " $* " =~ " random_seed" ]]; then
    echo
    echo "         cadnize_seed_change.py random"
    python3 $CURRENT_DIR/cadnize_seed_change.py check_sa.cc random
fi

                #set the seed random or original
if [[ " $* " =~ " original_seed" ]]; then
    echo
    echo "         cadnize_seed_change.py original"
    python3 $CURRENT_DIR/cadnize_seed_change.py check_sa.cc original
fi

