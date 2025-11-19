//
// Created by Frantisek Stloukal on 17.11.2025.
//
#include "../CPPProcess.h"

#ifndef CPPPROCESS_STANDALONE_COMMONNUMS_H
#define CPPPROCESS_STANDALONE_COMMONNUMS_H

//automatically read from CPPProcess
constexpr int nw6 = CPPProcess::nw6;
constexpr int npar = CPPProcess::npar;
constexpr int ncomb = CPPProcess::ncomb;
constexpr int ndcoup = Parameters_sm_dependentCouplings::ndcoup;

//need to be changed manually
//constexpr int nParity = 1; // in CPPProcess.cc - number of SIMD vectors - if CPPNONE, than equals to 1
//constexpr int nIPD = 2; // SM independent parameters used in CPPProcess.cc
//constexpr int nIPC = 0; // SM independent couplings used in CPPProcess.cc
#endif //CPPPROCESS_STANDALONE_COMMONNUMS_H