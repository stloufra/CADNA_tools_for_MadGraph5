//
// Created by Frantisek Stloukal on 18.11.2025.
//

#ifndef CPPPROCESS_STANDALONE_FILLERS_H
#define CPPPROCESS_STANDALONE_FILLERS_H
#include "typeTraits.h"
#include <iostream>
#include <iomanip>
#include "../CPPProcess.h"
#include "../accesses/MemoryAccessMomenta.h"
#include "../accesses/MemoryAccessMatrixElements.h"

using namespace mg5amcCpu;

void fillGs(auto m_gs, const int nevt)
{
    for (int i = 0; i < nevt; ++i)
    {
        m_gs[i] = 1.2177157847767195;
    }
}

void fillRndHel(auto m_hel, const int nevt)
{
    for (int i = 0; i < nevt; ++i)
    {
        m_hel[i] = 0.0;
    }
}

void fillMomentaFromFile(std::string filename, auto& hstMomenta, const int nevt, bool verbose = false, int prec = 3)
{
    using namespace mg5amcCpu;
    auto in_params = readSim_paramsFromFile(filename, prec);

    std::cout << std::string(SEP79, '-') << std::endl;
    std::cout << "Momenta from file: " << filename <<" which has less then "<< prec <<" nb. s.d. are in total - " << in_params.size()<< std::endl;
    std::cout << std::string(SEP79, '-') << std::endl;
    for (unsigned int ievt = 0; ievt < nevt; ++ievt) // Loop over all events in this iteration
    {
        if (verbose)
        {
            std::cout << "Momenta casting for event: " << ievt << std::endl;
        }

        for (int ipar = 0; ipar < CPPProcess::npar; ipar++)
        {
            double mass = in_params[ievt].momenta[ipar].p[0];
            double p1 = in_params[ievt].momenta[ipar].p[1];
            double p2 = in_params[ievt].momenta[ipar].p[2];
            double p3 = in_params[ievt].momenta[ipar].p[3];
            if (verbose)
            {
                // NB: 'setw' affects only the next field (of any type)
                const int ndigits = std::numeric_limits<double>::digits10;
                std::cout << std::scientific // fixed format: affects all floats (default precision: 6)
                    << std::setprecision(ndigits)
                    << std::setw(4) << ipar + 1
                    << std::setw(ndigits + 8) << mass
                    << std::setw(ndigits + 8) << p1
                    << std::setw(ndigits + 8) << p2
                    << std::setw(ndigits + 8) << p3
                    << std::endl
                    << std::defaultfloat; // default format: affects all floats
            }

            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 0, ipar) = static_cast<fptype>(mass);
            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 1, ipar) = static_cast<fptype>(p1);
            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 2, ipar) = static_cast<fptype>(p2);
            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 3, ipar) = static_cast<fptype>(p3);
        }
        if (verbose)
<<<<<<< HEAD
        {
            std::cout << std::string(SEP79, '-') << std::endl;
        }
=======
        std::cout << std::string(SEP79, '-') << std::endl;
>>>>>>> 492951b (transform incoming functions as well)
    }
}

void fillMomentaFromFileNative(std::string filename, auto& hstMomenta, const int nevt, bool verbose = false)
{
    using namespace mg5amcCpu;
    auto in_params = readSim_paramsFromFileNative(filename);

    for (unsigned int ievt = 0; ievt < nevt; ++ievt) // Loop over all events in this iteration
    {
        if (verbose)
        {
            std::cout << "Momenta casting for event: " << ievt << std::endl;
        }

        for (int ipar = 0; ipar < CPPProcess::npar; ipar++)
        {
            double mass = in_params[ievt].momenta[ipar].p[0];
            double p1 = in_params[ievt].momenta[ipar].p[1];
            double p2 = in_params[ievt].momenta[ipar].p[2];
            double p3 = in_params[ievt].momenta[ipar].p[3];
            if (verbose)
            {
                // NB: 'setw' affects only the next field (of any type)
                const int ndigits = std::numeric_limits<double>::digits10;
                std::cout << std::scientific // fixed format: affects all floats (default precision: 6)
                    << std::setprecision(ndigits)
                    << std::setw(4) << ipar + 1
                    << std::setw(ndigits + 8) << mass
                    << std::setw(ndigits + 8) << p1
                    << std::setw(ndigits + 8) << p2
                    << std::setw(ndigits + 8) << p3
                    << std::endl
                    << std::defaultfloat; // default format: affects all floats
            }

            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 0, ipar) = static_cast<fptype>(mass);
            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 1, ipar) = static_cast<fptype>(p1);
            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 2, ipar) = static_cast<fptype>(p2);
            MemoryAccessMomenta::ieventAccessIp4Ipar(hstMomenta.data(), ievt, 3, ipar) = static_cast<fptype>(p3);
        }
        if (verbose)
        std::cout << std::string(SEP79, '-') << std::endl;
    }
}

void printMEandPreccision(auto& hstMomenta, auto& hstMatrixElements, const int nevt, bool verbose = true)
{
    const int meGeVexponent = -(2 * CPPProcess::npar - 8);
#ifdef __CADNA__
    int avg_matrixElementPrecision = 0, avg_matrixElementPrecision_n = 0;
#endif
    for (unsigned int ievt = 0; ievt < nevt; ++ievt) // Loop over all events in this iteration
    {
        if (verbose)
        {
            // Display momenta
            std::cout << "Momenta: for event " << ievt << std::endl;
            for (int ipar = 0; ipar < CPPProcess::npar; ipar++)
            {
                // NB: 'setw' affects only the next field (of any type)
                const int ndigits = std::numeric_limits<double>::digits10;
                std::cout << std::scientific << std::setprecision(ndigits)  // fixed format: affects all floats (default precision: 6)
                    << std::setw(4) << ipar + 1
                    << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                        hstMomenta.data(), ievt, 0, ipar)
                    << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                        hstMomenta.data(), ievt, 1, ipar)
                    << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                        hstMomenta.data(), ievt, 2, ipar)
                    << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                        hstMomenta.data(), ievt, 3, ipar)
                    << std::endl
#ifdef __CADNA__
                    << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                            hstMomenta.data(), ievt, 0, ipar).
                        nb_significant_digit()
                        << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                            hstMomenta.data(), ievt, 1, ipar).
                        nb_significant_digit()
                        << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                            hstMomenta.data(), ievt, 2, ipar).
                        nb_significant_digit()
                        << std::setw(ndigits + 8) << MemoryAccessMomenta::ieventAccessIp4IparConst(
                            hstMomenta.data(), ievt, 3, ipar).
                        nb_significant_digit()

                        << std::endl
#endif
                    << std::defaultfloat; // default format: affects all floats
            }
            std::cout << std::string(SEP79, '-') << std::endl;
            // Display matrix elements
            std::cout << " Matrix element = " << MemoryAccessMatrixElements::ieventAccessConst(
                    hstMatrixElements.data(), ievt)
                << " GeV^" << meGeVexponent << std::endl;
#ifdef __CADNA__
            std::cout << " Matrix element number of sig dig = " <<
                MemoryAccessMatrixElements::ieventAccessConst(hstMatrixElements.data(), ievt).nb_significant_digit() <<
                " " << std::endl;
            avg_matrixElementPrecision += MemoryAccessMatrixElements::ieventAccessConst(hstMatrixElements.data(), ievt).
                nb_significant_digit();
            avg_matrixElementPrecision_n++;
#endif
            std::cout << std::string(SEP79, '-') << std::endl;
            std::cout << std::string(SEP79, '-') << std::endl;
        }
    }

#ifdef __CADNA__
    if (verbose)
    {
        std::cout << "avg_matrixElementPrecision = " << avg_matrixElementPrecision << std::endl;
        std::cout << "avg_matrixElementPrecision_n = " << avg_matrixElementPrecision_n << std::endl;
        std::cout << "(1)/(2) = " << (double)avg_matrixElementPrecision / (double)avg_matrixElementPrecision_n << std::endl;
    }
#endif
}

std::vector<fptype> convert_to_array(auto& hstMatrixElements, const int nevt)
{
    std::vector<fptype> out(nevt);
    for (int ievt = 0; ievt < nevt; ++ievt)
    {
        out[ievt ] = MemoryAccessMatrixElements::ieventAccessConst(hstMatrixElements.data(), ievt);
    }
    return out;
}

#endif //CPPPROCESS_STANDALONE_FILLERS_H
