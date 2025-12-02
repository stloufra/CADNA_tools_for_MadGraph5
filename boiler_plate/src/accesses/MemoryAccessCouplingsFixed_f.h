// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Created by: A. Valassi (Apr 2022) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2022-2024) for the MG5aMC CUDACPP plugin.

#ifndef MemoryAccessCouplingsFixed_f_H
#define MemoryAccessCouplingsFixed_f_H 1
#include "../boilerplate/typeTraits.h"

#include "../boilerplate/Complex.h"



//#include "MemoryAccessHelpers.h"

// NB: namespaces mg5amcGpu and mg5amcCpu includes types which are defined in different ways for CPU and GPU builds (see #318 and #725)
#ifdef MGONGPUCPP_GPUIMPL
namespace mg5amcGpu
#else
namespace mg5amcCpu
#endif
{
  //----------------------------------------------------------------------------

  // A class describing the internal layout of memory buffers for fixed couplings
  // This implementation uses a STRUCT[ndcoup][nx2] "super-buffer" layout: in practice, the cIPC global array
  // From the "super-buffer" for ndcoup different couplings, use idcoupAccessBuffer to access the buffer for one specific coupling
  // [If many implementations are used, a suffix _Sv1 should be appended to the class name]
  class MemoryAccessCouplingsFixedBase_f //_Sv1
  {
  public:

    // Locate the buffer for a single coupling (output) in a memory super-buffer (input) from the given coupling index (input)
    // [Signature (const) ===> const fptype* iicoupAccessBufferConst( const fptype* buffer, const int iicoup ) <===]
    static   inline const fptype_f*
    iicoupAccessBufferConst( const fptype_f* buffer, // input "super-buffer": in practice, the cIPC global array
                             const int iicoup )
    {
      constexpr int ix2 = 0;
      // NB! this effectively adds an offset "iicoup * nx2"
      return &( buffer[iicoup * nx2 + ix2] ); // STRUCT[idcoup][ix2]
    }

  private:

    // The number of floating point components of a complex number
    static constexpr int nx2 = mgOnGpu::nx2;
  };

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on implicit kernel rules
  // Its methods use the KernelAccessHelper template - note the use of the template keyword in template function instantiations
  template<bool onDevice>
  class KernelAccessCouplingsFixed_f
  {
  public:

    // Expose selected functions from MemoryAccessCouplingsFixedBase
    static constexpr auto iicoupAccessBufferConst = MemoryAccessCouplingsFixedBase_f::iicoupAccessBufferConst;

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (const, SCALAR OR VECTOR) ===> cxtype_sv kernelAccessConst( const fptype* buffer ) <===]
    static   inline const cxtype_f
    kernelAccessConst( const fptype_f* buffer )
    {
      // TRIVIAL ACCESS to fixed-couplings buffers!
      //return cxmake( fptype_sv{ buffer[0] }, fptype_sv{ buffer[1] } ); // NO! BUG #339!
      const fptype_f r_sv = fptype_f{ 0 } + buffer[0];
      const fptype_f i_sv = fptype_f{ 0 } + buffer[1];
      return cxmake<fptype_f>( r_sv, i_sv ); // ugly but effective
    }
  };

  //----------------------------------------------------------------------------

  typedef KernelAccessCouplingsFixed_f<false> HostAccessCouplingsFixed_f;
  typedef KernelAccessCouplingsFixed_f<true> DeviceAccessCouplingsFixed_f;

  //----------------------------------------------------------------------------

} // end namespace mg5amcGpu/mg5amcCpu

#endif // MemoryAccessCouplingsFixed_H
