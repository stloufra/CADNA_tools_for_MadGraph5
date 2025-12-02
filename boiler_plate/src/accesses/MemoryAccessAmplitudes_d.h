// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Created by: A. Valassi (Jan 2022) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2022-2024) for the MG5aMC CUDACPP plugin.

#ifndef MemoryAccessAmplitudes_d_H
#define MemoryAccessAmplitudes_d_H 1

#include "../boilerplate/typeTraits.h"

#include "../boilerplate/Complex.h"

#include "MemoryAccessHelpers.h"

#define MGONGPU_TRIVIAL_AMPLITUDES 1

// NB: namespaces mg5amcGpu and mg5amcCpu includes types which are defined in different ways for CPU and GPU builds (see #318 and #725)
#ifdef MGONGPUCPP_GPUIMPL
namespace mg5amcGpu
#else
namespace mg5amcCpu
#endif
{
  //----------------------------------------------------------------------------

#ifndef MGONGPU_TRIVIAL_AMPLITUDES

  // A class describing the internal layout of memory buffers for amplitudes
  // This implementation uses an AOSOA[npagA][nx2][neppA] where nevt=npagA*neppA
  // [If many implementations are used, a suffix _AOSOAv1 should be appended to the class name]
  class MemoryAccessAmplitudesBase_d //_AOSOAv1
  {
  public:

    // Number of Events Per Page in the amplitude AOSOA memory buffer layout
    static constexpr int neppA = 1; // AOS (just a test...)

  private:

    friend class MemoryAccessHelper<MemoryAccessAmplitudesBase_d>;
    friend class KernelAccessHelper<MemoryAccessAmplitudesBase_d, true>;
    friend class KernelAccessHelper<MemoryAccessAmplitudesBase_d, false>;

    // The number of floating point components of a complex number
    static constexpr int nx2 = mgOnGpu::nx2;

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
      const int ipagA = ievt / neppA; // #event "A-page"
      const int ieppA = ievt % neppA; // #event in the current event A-page
      constexpr int ix2 = 0;
      return &( buffer[ipagA * nx2 * neppA + ix2 * neppA + ieppA] ); // AOSOA[ipagA][ix2][ieppA]
    }

    //--------------------------------------------------------------------------

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& decodeRecord( fptype_d* buffer, Ts... args ) <===]
    // [NB: expand variadic template "Ts... args" to "const int ix2" and rename "Field" as "Ix2"]
    static   inline fptype_d&
    decodeRecord( fptype_d* buffer,
                  const int ix2 )
    {
      constexpr int ipagA = 0;
      constexpr int ieppA = 0;
      return buffer[ipagA * nx2 * neppA + ix2 * neppA + ieppA]; // AOSOA[ipagA][ix2][ieppA]
    }
  };

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on explicit event numbers
  // Its methods use the MemoryAccessHelper templates - note the use of the template keyword in template function instantiations
  class MemoryAccessAmplitudes_d : public MemoryAccessAmplitudesBase_d
  {
  public:

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (non-const) ===> fptype_d* ieventAccessRecord( fptype_d* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecord = MemoryAccessHelper<MemoryAccessAmplitudesBase_d>::ieventAccessRecord;

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (const) ===> const fptype_d* ieventAccessRecordConst( const fptype_d* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecordConst = MemoryAccessHelper<MemoryAccessAmplitudesBase_d>::ieventAccessRecordConst;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& decodeRecord( fptype_d* buffer, const int ix2 ) <===]
    static constexpr auto decodeRecordIx2 = MemoryAccessHelper<MemoryAccessAmplitudesBase_d>::decodeRecord;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (const) ===> const fptype_d& decodeRecordConst( const fptype_d* buffer, const int ix2 ) <===]
    static constexpr auto decodeRecordIx2Const =
      MemoryAccessHelper<MemoryAccessAmplitudesBase_d>::template decodeRecordConst<int>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& ieventAccessIx2( fptype_d* buffer, const ievt, const int ix2 ) <===]
    static constexpr auto ieventAccessIx2 =
      MemoryAccessHelper<MemoryAccessAmplitudesBase_d>::template ieventAccessField<int>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (const) ===> const fptype_d& ieventAccessIx2Const( const fptype_d* buffer, const ievt, const int ix2 ) <===]
    static constexpr auto ieventAccessIx2Const =
      MemoryAccessHelper<MemoryAccessAmplitudesBase_d>::template ieventAccessFieldConst<int>;
  };

#endif // #ifndef MGONGPU_TRIVIAL_AMPLITUDES

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on implicit kernel rules
  // Its methods use the KernelAccessHelper template - note the use of the template keyword in template function instantiations
  template<bool onDevice>
  class KernelAccessAmplitudes_d
  {
  public:

#ifndef MGONGPU_TRIVIAL_AMPLITUDES

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& kernelAccessIx2( fptype_d* buffer, const int ix2 ) <===]
    static constexpr auto kernelAccessIx2 =
      KernelAccessHelper<MemoryAccessAmplitudesBase_d, onDevice>::template kernelAccessField<int>;

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (const) ===> const fptype_d& kernelAccessIx2Const( const fptype_d* buffer, const int ix2 ) <===]
    static constexpr auto kernelAccessIx2Const =
      KernelAccessHelper<MemoryAccessAmplitudesBase_d, onDevice>::template kernelAccessFieldConst<int>;

#else

    static   inline cxtype_d*
    kernelAccess( fptype_d* buffer )
    {
      return reinterpret_cast<cxtype_d*>( buffer );
    }

    static   inline const cxtype_d*
    kernelAccessConst( const fptype_d* buffer )
    {
      return reinterpret_cast<const cxtype_d*>( buffer );
    }

#endif // #ifndef MGONGPU_TRIVIAL_AMPLITUDES
  };

  //----------------------------------------------------------------------------

  typedef KernelAccessAmplitudes_d<false> HostAccessAmplitudes_d;
  typedef KernelAccessAmplitudes_d<true> DeviceAccessAmplitudes_d;

  //----------------------------------------------------------------------------

} // end namespace mg5amcGpu/mg5amcCpu

#endif // MemoryAccessAmplitudes_d_H
