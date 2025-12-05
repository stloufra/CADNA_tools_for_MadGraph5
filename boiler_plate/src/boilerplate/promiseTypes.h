#ifndef CPPPROCESS_STANDALONE_PROMISETYPES_H
#define CPPPROCESS_STANDALONE_PROMISETYPES_H

#ifdef __CADNA__
//typedef float_st fptype;
//typedef float_st fptype2;
#else
//typedef float fptype;
//typedef float fptype2;
#endif


typedef __PR_fptype__ fptype;
typedef __PR_fptype2__ fptype2;

//typedef __PR_imzxxx__  FT_imzxxx;
//typedef __PR_ipzxxx__  FT_ipzxxx;
////typedef __PR_ixxxxx__  FT_ixxxxx;
//typedef __PR_ixzxxx__  FT_ixzxxx;
//typedef __PR_omzxxx__  FT_omzxxx;
//typedef __PR_opzxxx__  FT_opzxxx;
////typedef __PR_oxxxxx__  FT_oxxxxx;
//typedef __PR_oxzxxx__  FT_oxzxxx;
//typedef __PR_sxxxxx__  FT_sxxxxx;
////typedef __PR_vxxxxx__  FT_vxxxxx;

typedef float FT_imzxxx;
typedef float FT_ipzxxx;
typedef float FT_ixzxxx;
typedef float FT_omzxxx;
typedef float FT_opzxxx;
typedef float FT_oxzxxx;
typedef float FT_sxxxxx;

typedef __PR_w__ FT_w;
typedef __PR_ampsv__ FT_amp_sv;
typedef __PR_jamps__ FT_jamps;

typedef __PR_ixxxxx__  FT_ixxxxx;
typedef __PR_oxxxxx__  FT_oxxxxx;
typedef __PR_vxxxxx__  FT_vxxxxx;

typedef __PR_VVV10__ FT_VVV1_0;
typedef __PR_FFV1P03__  FT_FFV1P0_3;
typedef __PR_FFV10__  FT_FFV1_0;
typedef __PR_FFV11__  FT_FFV1_1;
typedef __PR_FFV12__  FT_FFV1_2;
typedef __PR_VVV1P01__  FT_VVV1P0_1;
typedef __PR_VVV10__  FT_VVV1_0;
typedef __PR_VVVV1P01__  FT_VVVV1P0_1;
typedef __PR_VVVV10__  FT_VVVV1_0;
typedef __PR_VVVV3P01__  FT_VVVV3P0_1;
typedef __PR_VVVV30__  FT_VVVV3_0;
typedef __PR_VVVV4P01__  FT_VVVV4P0_1;
typedef __PR_VVVV40__  FT_VVVV4_0;

#endif