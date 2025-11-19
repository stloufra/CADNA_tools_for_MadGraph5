//
// Created by Frantisek Stloukal on 14.11.2025.
//

#ifndef CPPPROCESS_STANDALONE_MEMORYBUFFERS_H
#define CPPPROCESS_STANDALONE_MEMORYBUFFERS_H
#include "typeTraits.h"
#include "CPPProcess.h"
//--------------------------------------------------------------------------

  namespace MemoryBuffers
  {
    using namespace mg5amcCpu;
    // Process-independent compile-time constants
    static constexpr size_t np4 = CPPProcess::np4;
    static constexpr size_t nw6 = CPPProcess::nw6;
    static constexpr size_t nx2 = mgOnGpu::nx2;
    // Process-dependent compile-time constants
    static constexpr size_t nparf = CPPProcess::nparf;
    static constexpr size_t npar = CPPProcess::npar;
    static constexpr size_t ndcoup = Parameters_sm_dependentCouplings::ndcoup;
    static constexpr size_t ncolor = CPPProcess::ncolor;
  }

  //--------------------------------------------------------------------------

  // An abstract interface encapsulating a given number of events
  class INumberOfEvents
  {
  public:
    virtual ~INumberOfEvents() {}
    virtual size_t nevt() const = 0;
  };

  //--------------------------------------------------------------------------

  // A class encapsulating a given number of events
  class NumberOfEvents : virtual public INumberOfEvents
  {
  public:
    NumberOfEvents( const size_t nevt )
      : m_nevt( nevt ) {}
    virtual ~NumberOfEvents() {}
    virtual size_t nevt() const override { return m_nevt; }
  private:
    const size_t m_nevt;
  };

  //--------------------------------------------------------------------------

  // A base class encapsulating a memory buffer (not necessarily an event buffer)
  template<typename T>
  class BufferBase : virtual public INumberOfEvents
  {
  protected:
    BufferBase( const size_t size, const bool onDevice )
      : m_size( size ), m_data( nullptr ), m_isOnDevice( onDevice ) {}
  public:
    virtual ~BufferBase() {}
    T* data() { return m_data; }
    const T* data() const { return m_data; }
    T& operator[]( const size_t index ) { return m_data[index]; }
    const T& operator[]( const size_t index ) const { return m_data[index]; }
    size_t size() const { return m_size; }
    size_t bytes() const { return m_size * sizeof( T ); }
    bool isOnDevice() const { return m_isOnDevice; }
    virtual size_t nevt() const override { throw std::runtime_error( "This BufferBase is not an event buffer" ); }
  protected:
    const size_t m_size;
    T* m_data;
    const bool m_isOnDevice;
  };

  //--------------------------------------------------------------------------

#ifndef MGONGPUCPP_GPUIMPL
  constexpr bool HostBufferALIGNED = false;   // ismisaligned=false
  constexpr bool HostBufferMISALIGNED = true; // ismisaligned=true

  // A class encapsulating a C++ host buffer
  template<typename T, bool ismisaligned>
  class HostBufferBase : public BufferBase<T>
  {
  public:
    HostBufferBase( const size_t size )
      : BufferBase<T>( size, false )
    {
      if constexpr( !ismisaligned )
        this->m_data = new( std::align_val_t( cppAlign ) ) T[size]();
      else
        this->m_data = new( std::align_val_t( cppAlign ) ) T[size + 1]() + 1; // TEST MISALIGNMENT!
    }
    virtual ~HostBufferBase()
    {
      if constexpr( !ismisaligned )
        ::operator delete[]( this->m_data, std::align_val_t( cppAlign ) );
      else
        ::operator delete[]( ( this->m_data ) - 1, std::align_val_t( cppAlign ) ); // TEST MISALIGNMENT!
    }
    static constexpr bool isaligned() { return !ismisaligned; }
  public:
    static constexpr size_t cppAlign = mgOnGpu::cppAlign;
  };
#endif

 // A class encapsulating a C++ host buffer for a given number of events
  template<typename T, size_t sizePerEvent, bool ismisaligned>
  class HostBuffer : public HostBufferBase<T, ismisaligned>, virtual private NumberOfEvents
  {
  public:
    HostBuffer( const size_t nevt )
      : NumberOfEvents( nevt )
      , HostBufferBase<T, ismisaligned>( sizePerEvent * nevt )
    {
      //std::cout << "HostBuffer::ctor " << this << " " << nevt << std::endl;
    }
    virtual ~HostBuffer()
    {
      //std::cout << "HostBuffer::dtor " << this << std::endl;
    }
    virtual size_t nevt() const override final { return NumberOfEvents::nevt(); }
  };
 // A base class encapsulating a memory buffer for momenta random numbers
  typedef BufferBase<fptype> BufferRndNumMomenta;

  // The size (number of elements) per event in a memory buffer for momenta random numbers
  constexpr size_t sizePerEventRndNumMomenta = MemoryBuffers::np4 * MemoryBuffers::nparf;

  // A class encapsulating a C++ host buffer for momenta random numbers
  typedef HostBuffer<fptype, sizePerEventRndNumMomenta, HostBufferALIGNED> HostBufferRndNumMomenta;
 // A base class encapsulating a memory buffer for Gs (related to the event-by-event strength of running coupling constant alphas QCD)
  typedef BufferBase<fptype> BufferGs;

  // The size (number of elements) per event in a memory buffer for Gs
  constexpr size_t sizePerEventGs = 1;
  typedef HostBuffer<fptype, sizePerEventGs, HostBufferALIGNED> HostBufferGs;

  typedef BufferBase<fptype> BufferCouplings;
  constexpr size_t sizePerEventCouplings = MemoryBuffers::ndcoup * MemoryBuffers::nx2;
  typedef HostBuffer<fptype, sizePerEventCouplings, HostBufferALIGNED> HostBufferCouplings;

  typedef BufferBase<fptype> BufferMomenta;
  constexpr size_t sizePerEventMomenta = MemoryBuffers::np4 * MemoryBuffers::npar;
  typedef HostBuffer<fptype, sizePerEventMomenta, HostBufferALIGNED> HostBufferMomenta;

  typedef BufferBase<fptype> BufferWeights;
  constexpr size_t sizePerEventWeights = 1;
  typedef HostBuffer<fptype, sizePerEventWeights, HostBufferALIGNED> HostBufferWeights;

  typedef BufferBase<fptype> BufferMatrixElements;
  constexpr size_t sizePerEventMatrixElements = 1;
  typedef HostBuffer<fptype, sizePerEventMatrixElements, HostBufferALIGNED> HostBufferMatrixElements;

  typedef BufferBase<bool> BufferHelicityMask;
  typedef HostBufferBase<bool, HostBufferALIGNED> HostBufferHelicityMask;

  typedef BufferBase<fptype> BufferWavefunctions;
  constexpr size_t sizePerEventWavefunctions = MemoryBuffers::nw6 * MemoryBuffers::nx2;
  typedef HostBuffer<fptype, sizePerEventWavefunctions, HostBufferALIGNED> HostBufferWavefunctions;

  typedef BufferBase<fptype> BufferRndNumHelicity;
  constexpr size_t sizePerEventRndNumHelicity = 1;
  typedef HostBuffer<fptype, sizePerEventRndNumHelicity, HostBufferALIGNED> HostBufferRndNumHelicity;

  typedef BufferBase<fptype> BufferRndNumColor;
  constexpr size_t sizePerEventRndNumColor = 1;
  typedef HostBuffer<fptype, sizePerEventRndNumColor, HostBufferALIGNED> HostBufferRndNumColor;

  typedef BufferBase<unsigned int> BufferChannelIds;
  constexpr size_t sizePerEventChannelId = 1;
  typedef HostBuffer<unsigned int, sizePerEventChannelId, HostBufferALIGNED> HostBufferChannelIds;

  typedef BufferBase<int> BufferSelectedHelicity;
  constexpr size_t sizePerEventSelectedHelicity = 1;
  typedef HostBuffer<int, sizePerEventSelectedHelicity, HostBufferALIGNED> HostBufferSelectedHelicity;

  typedef BufferBase<int> BufferSelectedColor;
  constexpr size_t sizePerEventSelectedColor = 1;
  typedef HostBuffer<int, sizePerEventSelectedColor, HostBufferALIGNED> HostBufferSelectedColor;
#endif //CPPPROCESS_STANDALONE_MEMORYBUFFERS_H