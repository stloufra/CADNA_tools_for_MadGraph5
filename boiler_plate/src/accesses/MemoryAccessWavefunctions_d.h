// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Created by: A. Valassi (Jan 2022) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2022-2024) for the MG5aMC CUDACPP plugin.

#ifndef MemoryAccessWavefunctions_d_H
#define MemoryAccessWavefunctions_d_H 1

#include "../boilerplate/typeTraits.h"

#include "../boilerplate/Complex.h"

#include "MemoryAccessHelpers.h"

#define MGONGPU_TRIVIAL_WAVEFUNCTIONS 1

// NB: namespaces mg5amcGpu and mg5amcCpu includes types which are defined in different ways for CPU and GPU builds (see #318 and #725)
#ifdef MGONGPUCPP_GPUIMPL
namespace mg5amcGpu
#else
namespace mg5amcCpu
#endif
{
  //----------------------------------------------------------------------------

#ifndef MGONGPU_TRIVIAL_WAVEFUNCTIONS

  // A class describing the internal layout of memory buffers for wavefunctions
  // This implementation uses an AOSOA[npagW][nw6][nx2][neppW] where nevt=npagW*neppW
  // [If many implementations are used, a suffix _AOSOAv1 should be appended to the class name]
  class MemoryAccessWavefunctionsBase_d //_AOSOAv1
  {
  public:

    // Number of Events Per Page in the wavefunction AOSOA memory buffer layout
    static constexpr int neppW = 1; // AOS (just a test...)

  private:

    friend class MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>;
    friend class KernelAccessHelper<MemoryAccessWavefunctionsBase_d, true>;
    friend class KernelAccessHelper<MemoryAccessWavefunctionsBase_d, false>;

    // The number of components of a (fermion or vector) wavefunction
    static constexpr int nw6 = mgOnGpu::nw6;

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
      const int ipagW = ievt / neppW; // #event "W-page"
      const int ieppW = ievt % neppW; // #event in the current event W-page
      constexpr int iw6 = 0;
      constexpr int ix2 = 0;
      return &( buffer[ipagW * nw6 * nx2 * neppW + iw6 * nx2 * neppW + ix2 * neppW + ieppW] ); // AOSOA[ipagW][iw6][ix2][ieppW]
    }

    //--------------------------------------------------------------------------

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& decodeRecord( fptype_d* buffer, Ts... args ) <===]
    // [NB: expand variadic template "Ts... args" to "const int iw6, const int ix2" and rename "Field" as "Iw6Ix2"]
    static   inline fptype_d&
    decodeRecord( fptype_d* buffer,
                  const int iw6,
                  const int ix2 )
    {
      constexpr int ipagW = 0;
      constexpr int ieppW = 0;
      return buffer[ipagW * nw6 * nx2 * neppW + iw6 * nx2 * neppW + ix2 * neppW + ieppW]; // AOSOA[ipagW][iw6][ix2][ieppW]
    }
  };

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on explicit event numbers
  // Its methods use the MemoryAccessHelper templates - note the use of the template keyword in template function instantiations
  class MemoryAccessWavefunctions_d : public MemoryAccessWavefunctionsBase_d
  {
  public:

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (non-const) ===> fptype_d* ieventAccessRecord( fptype_d* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecord = MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>::ieventAccessRecord;

    // Locate an event record (output) in a memory buffer (input) from the given event number (input)
    // [Signature (const) ===> const fptype_d* ieventAccessRecordConst( const fptype_d* buffer, const int ievt ) <===]
    static constexpr auto ieventAccessRecordConst = MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>::ieventAccessRecordConst;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& decodeRecord( fptype_d* buffer, const int iw6, const int ix2 ) <===]
    static constexpr auto decodeRecordIw6Ix2 = MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>::decodeRecord;

    // Locate a field (output) of an event record (input) from the given field indexes (input)
    // [Signature (const) ===> const fptype_d& decodeRecordConst( const fptype_d* buffer, const int iw6, const int ix2 ) <===]
    static constexpr auto decodeRecordIw6Ix2Const =
      MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>::template decodeRecordConst<int, int>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& ieventAccessIw6Ix2( fptype_d* buffer, const ievt, const int iw6, const int ix2 ) <===]
    static constexpr auto ieventAccessIw6Ix2 =
      MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>::template ieventAccessField<int, int>;

    // Locate a field (output) in a memory buffer (input) from the given event number (input) and the given field indexes (input)
    // [Signature (const) ===> const fptype_d& ieventAccessIw6Ix2Const( const fptype_d* buffer, const ievt, const int iw6, const int ix2 ) <===]
    static constexpr auto ieventAccessIw6Ix2Const =
      MemoryAccessHelper<MemoryAccessWavefunctionsBase_d>::template ieventAccessFieldConst<int, int>;
  };

#endif // #ifndef MGONGPU_TRIVIAL_WAVEFUNCTIONS

  //----------------------------------------------------------------------------

  // A class providing access to memory buffers for a given event, based on implicit kernel rules
  // Its methods use the KernelAccessHelper template - note the use of the template keyword in template function instantiations
  template<bool onDevice>
  class KernelAccessWavefunctions_d
  {
  public:

#ifndef MGONGPU_TRIVIAL_WAVEFUNCTIONS

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (non-const) ===> fptype_d& kernelAccessIw6Ix2( fptype_d* buffer, const int iw6, const int ix2 ) <===]
    static constexpr auto kernelAccessIw6Ix2 =
      KernelAccessHelper<MemoryAccessWavefunctionsBase_d, onDevice>::template kernelAccessField<int, int>;

    // Locate a field (output) in a memory buffer (input) from a kernel event-indexing mechanism (internal) and the given field indexes (input)
    // [Signature (const) ===> const fptype_d& kernelAccessIw6Ix2Const( const fptype_d* buffer, const int iw6, const int ix2 ) <===]
    static constexpr auto kernelAccessIw6Ix2Const =
      KernelAccessHelper<MemoryAccessWavefunctionsBase_d, onDevice>::template kernelAccessFieldConst<int, int>;

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

#endif // #ifndef MGONGPU_TRIVIAL_WAVEFUNCTIONS
  };

  //----------------------------------------------------------------------------

  typedef KernelAccessWavefunctions_d<false> HostAccessWavefunctions_d;
  typedef KernelAccessWavefunctions_d<true> DeviceAccessWavefunctions_d;

  //----------------------------------------------------------------------------

} // end namespace mg5amcGpu/mg5amcCpu

#endif // MemoryAccessWavefunctions_H
