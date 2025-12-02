// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Created by: A. Valassi (Jan 2022) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2022-2024) for the MG5aMC CUDACPP plugin.

#ifndef MemoryAccessMatrixElements_d_H
#define MemoryAccessMatrixElements_d_H 1

#include "../boilerplate/typeTraits.h"

#include "../boilerplate/Complex.h"

#include "MemoryAccessHelpers.h"
#include "MemoryAccessVectors.h"
#include "../boilerplate/MemoryBuffers.h"

// NB: namespaces mg5amcGpu and mg5amcCpu includes types which are defined in different ways for CPU and GPU builds (see #318 and #725)
#ifdef MGONGPUCPP_GPUIMPL
namespace mg5amcGpu
#else
namespace mg5amcCpu
#endif
{
  //----------------------------------------------------------------------------

  // A class describing the internal layout of memory buffers for matrix elements
  // This implementation uses a plain ARRAY[nevt]
  // [If many implementations are used, a suffix _ARRAYv1 should be appended to the class name]
  class MemoryAccessMatrixElementsBase_d //_ARRAYv1
  {
  private:

    friend class MemoryAccessHelper<MemoryAccessMatrixElementsBase_d, fptype_d>;
    friend class KernelAccessHelper<MemoryAccessMatrixElementsBase_d, true, fptype_d>;
    friend class KernelAccessHelper<MemoryAccessMatrixElementsBase_d, false, fptype_d>;

    //--------------------------------------------------------------------------
    // NB all KernelLaunchers assume that memory access can be decomposed as "accessField = decodeRecord( accessRecord )"
    // (in other words: first locate the event record for a given event, then locate an element in that record)
    //--------------------------------------------------------------------------

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (non-const) ===> fptype_d* ieventAccessRecord( fptype_d* buffer, const int ievt ) <===]
    static   inline fptype_d*
    ieventAccessRecord( fptype_d* buffer,
                        const int ievt )
    {
      return &( buffer[ievt] ); // ARRAY[nevt]
    }

    //--------------------------------------------------------------------------

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& decodeRecord( fptype_d* buffer, Ts... args ) <===]
    // [NB: expand variadic template "Ts... args" to empty and rename "Field" as empty]
    static   inline fptype_d&
    decodeRecord( fptype_d* buffer )
    {
      constexpr int ievt = 0;
      return buffer[ievt]; // ARRAY[nevt]
    }
  };

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on explicit event numbers
  // Its methods use the MemoryAccessHelper templates - note the use of the template keyword in template function instantiations
  class MemoryAccessMatrixElements_d : public MemoryAccessMatrixElementsBase_d
  {
  public:

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (non-const) ===> fptype_d* ieventAccessRecord( fptype_d* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecord = MemoryAccessHelper<MemoryAccessMatrixElementsBase_d, fptype_d>::ieventAccessRecord;

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (const) ===> const fptype_d* ieventAccessRecordConst( const fptype_d* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecordConst = MemoryAccessHelper<MemoryAccessMatrixElementsBase_d, fptype_d>::ieventAccessRecordConst;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& decodeRecord( fptype_d* buffer ) <===]
    static constexpr auto decodeRecord = MemoryAccessHelper<MemoryAccessMatrixElementsBase_d, fptype_d>::decodeRecord;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (const) ===> const fptype_d& decodeRecordConst( const fptype_d* buffer ) <===]
    static constexpr auto decodeRecordConst =
      MemoryAccessHelper<MemoryAccessMatrixElementsBase_d,fptype_d>::template decodeRecordConst<>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& ieventAccess( fptype_d* buffer, const ievt ) <===]
    static constexpr auto ieventAccess =
      MemoryAccessHelper<MemoryAccessMatrixElementsBase_d,fptype_d>::template ieventAccessField<>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (const) ===> const fptype_d& ieventAccessConst( const fptype_d* buffer, const ievt ) <===]
    static constexpr auto ieventAccessConst =
      MemoryAccessHelper<MemoryAccessMatrixElementsBase_d,fptype_d>::template ieventAccessFieldConst<>;
  };

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on implicit kernel rules
  // Its methods use the KernelAccessHelper template - note the use of the template keyword in template function instantiations
  template<bool onDevice>
  class KernelAccessMatrixElements_d
  {
  public:

    // Expose selected functions from MemoryAccessMatrixElements_d
    static constexpr auto ieventAccessRecord = MemoryAccessMatrixElements_d::ieventAccessRecord;

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (non-const, SCALAR) ===> fptype_d& kernelAccess_s( fptype_d* buffer ) <===]
    static constexpr auto kernelAccess_s =
      KernelAccessHelper<MemoryAccessMatrixElementsBase_d, onDevice, fptype_d>::template kernelAccessField<>; // requires cuda 11.4

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal)
    // [Signature (non const, SCALAR OR VECTOR) ===> fptype_d& kernelAccess( const fptype_d* buffer ) <===]
    static   inline fptype_d&
    kernelAccess( fptype_d* buffer )
    {
      fptype_d& out = kernelAccess_s( buffer );
#ifndef MGONGPU_CPPSIMD
      return out;
#else
      // NB: derived from MemoryAccessMomenta, restricting the implementation to contiguous aligned arrays (#435)
      static_assert( mg5amcCpu::HostBufferMatrixElements::isaligned() ); // ASSUME ALIGNED ARRAYS (reinterpret_cast will segfault otherwise!)
      //assert( (size_t)( buffer ) % mgOnGpu::cppAlign == 0 ); // ASSUME ALIGNED ARRAYS (reinterpret_cast will segfault otherwise!)
      return mg5amcCpu::fptype_dvFromAlignedArray( out ); // SIMD bulk load of neppV, use reinterpret_cast
#endif
    }

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (const) ===> const fptype_d& kernelAccessConst( const fptype_d* buffer ) <===]
    static constexpr auto kernelAccessConst =
      KernelAccessHelper<MemoryAccessMatrixElementsBase_d, onDevice, fptype_d>::template kernelAccessFieldConst<>; // requires cuda 11.4
  };

  //----------------------------------------------------------------------------

  typedef KernelAccessMatrixElements_d<false> HostAccessMatrixElements_d;
  typedef KernelAccessMatrixElements_d<true> DeviceAccessMatrixElements_d;

  //----------------------------------------------------------------------------

} // end namespace mg5amcGpu/mg5amcCpu

#endif // MemoryAccessMatrixElements_H
