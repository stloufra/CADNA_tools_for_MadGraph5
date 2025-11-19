//
// Created by Frantisek Stloukal on 17.11.2025.
//
#include "CPPProcess.h"

#ifndef CPPPROCESS_STANDALONE_COMMONNUMS_H
#define CPPPROCESS_STANDALONE_COMMONNUMS_H

constexpr int nw6 = CPPProcess::nw6;
// dimensions of each wavefunction (HELAS KEK 91-11): e.g. 6 for e+ e- -> mu+ mu- (fermions and vectors)
constexpr int npar = CPPProcess::npar; // #particles in total (external = initial + final): e.g. 4 for e+ e- -> mu+ mu-
constexpr int ncomb = CPPProcess::ncomb;
// #helicity combinations: e.g. 16 for e+ e- -> mu+ mu- (2**4 = fermion spin up/down ** npar)
//constexpr int ncolor = CPPProcess::ncolor; // the number of leading colors
constexpr int nParity = 1;
constexpr int ndcoup = Parameters_sm_dependentCouplings::ndcoup;

constexpr int nIPD = 2; // SM independent parameters used in this CPPProcess.cc (FIXME? rename as sm_IndepParam?)
constexpr int nIPC = 0; // SM independent couplings used in this CPPProcess.cc (FIXME? rename as sm_IndepCoupl?)
#endif //CPPPROCESS_STANDALONE_COMMONNUMS_H