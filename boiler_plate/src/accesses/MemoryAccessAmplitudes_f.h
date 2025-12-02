// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Created by: A. Valassi (Jan 2022) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2022-2024) for the MG5aMC CUDACPP plugin.

#ifndef MemoryAccessAmplitudes_f_H
#define MemoryAccessAmplitudes_f_H 1

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
  class MemoryAccessAmplitudesBase_f //_AOSOAv1
  {
  public:

    // Number of Events Per Page in the amplitude AOSOA memory buffer layout
    static constexpr int neppA = 1; // AOS (just a test...)

  private:

    friend class MemoryAccessHelper<MemoryAccessAmplitudesBase_f>;
    friend class KernelAccessHelper<MemoryAccessAmplitudesBase_f, true>;
    friend class KernelAccessHelper<MemoryAccessAmplitudesBase_f, false>;

    // The number of floating point components of a complex number
    static constexpr int nx2 = mgOnGpu::nx2;

    //--------------------------------------------------------------------------
    // NB all KernelLaunchers assume that memory access can be decomposed as "accessField = decodeRecord( accessRecord )"
    // (in other words: first locate the event record for a given event, then locate an element in that record)
    //--------------------------------------------------------------------------

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (non-const) ===> fptype_f* ieventAccessRecord( fptype_f* buffer, const int ievt ) <===]
    static   inline fptype_f*
    ieventAccessRecord( fptype_f* buffer,
                        const int ievt )
    {
      const int ipagA = ievt / neppA; // #event "A-page"
      const int ieppA = ievt % neppA; // #event in the current event A-page
      constexpr int ix2 = 0;
      return &( buffer[ipagA * nx2 * neppA + ix2 * neppA + ieppA] ); // AOSOA[ipagA][ix2][ieppA]
    }

    //--------------------------------------------------------------------------

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_f& decodeRecord( fptype_f* buffer, Ts... args ) <===]
    // [NB: expand variadic template "Ts... args" to "const int ix2" and rename "Field" as "Ix2"]
    static   inline fptype_f&
    decodeRecord( fptype_f* buffer,
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
  class MemoryAccessAmplitudes_f : public MemoryAccessAmplitudesBase_f
  {
  public:

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (non-const) ===> fptype_f* ieventAccessRecord( fptype_f* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecord = MemoryAccessHelper<MemoryAccessAmplitudesBase_f>::ieventAccessRecord;

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (const) ===> const fptype_f* ieventAccessRecordConst( const fptype_f* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecordConst = MemoryAccessHelper<MemoryAccessAmplitudesBase_f>::ieventAccessRecordConst;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_f& decodeRecord( fptype_f* buffer, const int ix2 ) <===]
    static constexpr auto decodeRecordIx2 = MemoryAccessHelper<MemoryAccessAmplitudesBase_f>::decodeRecord;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (const) ===> const fptype_f& decodeRecordConst( const fptype_f* buffer, const int ix2 ) <===]
    static constexpr auto decodeRecordIx2Const =
      MemoryAccessHelper<MemoryAccessAmplitudesBase_f>::template decodeRecordConst<int>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_f& ieventAccessIx2( fptype_f* buffer, const ievt, const int ix2 ) <===]
    static constexpr auto ieventAccessIx2 =
      MemoryAccessHelper<MemoryAccessAmplitudesBase_f>::template ieventAccessField<int>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (const) ===> const fptype_f& ieventAccessIx2Const( const fptype_f* buffer, const ievt, const int ix2 ) <===]
    static constexpr auto ieventAccessIx2Const =
      MemoryAccessHelper<MemoryAccessAmplitudesBase_f>::template ieventAccessFieldConst<int>;
  };

#endif // #ifndef MGONGPU_TRIVIAL_AMPLITUDES

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on implicit kernel rules
  // Its methods use the KernelAccessHelper template - note the use of the template keyword in template function instantiations
  template<bool onDevice>
  class KernelAccessAmplitudes_f
  {
  public:

#ifndef MGONGPU_TRIVIAL_AMPLITUDES

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_f& kernelAccessIx2( fptype_f* buffer, const int ix2 ) <===]
    static constexpr auto kernelAccessIx2 =
      KernelAccessHelper<MemoryAccessAmplitudesBase_f, onDevice>::template kernelAccessField<int>;

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (const) ===> const fptype_f& kernelAccessIx2Const( const fptype_f* buffer, const int ix2 ) <===]
    static constexpr auto kernelAccessIx2Const =
      KernelAccessHelper<MemoryAccessAmplitudesBase_f, onDevice>::template kernelAccessFieldConst<int>;

#else

    static   inline cxtype_f*
    kernelAccess( fptype_f* buffer )
    {
      return reinterpret_cast<cxtype_f*>( buffer );
    }

    static   inline const cxtype_f*
    kernelAccessConst( const fptype_f* buffer )
    {
      return reinterpret_cast<const cxtype_f*>( buffer );
    }

#endif // #ifndef MGONGPU_TRIVIAL_AMPLITUDES
  };

  //----------------------------------------------------------------------------

  typedef KernelAccessAmplitudes_f<false> HostAccessAmplitudes_f;
  typedef KernelAccessAmplitudes_f<true> DeviceAccessAmplitudes_f;

  //----------------------------------------------------------------------------

} // end namespace mg5amcGpu/mg5amcCpu

#endif // MemoryAccessAmplitudes_f_H
