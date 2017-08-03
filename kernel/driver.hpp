#pragma once
#include "cpp.hpp"

#include "arch/io.h"

#include "platform/fatal.h"

#include "attributes.h"
#include "device.h"

#include <vector>

namespace os216 {

class Driver {
public:
    
    struct LocationRange{
        LocationRange();
        OS216_CONSTEXPR_CONSTRUCTOR LocationRange(const LocationRange &other)
          : m_start(other.m_start)
          , m_length(other.m_length){}
        
        OS216_CONSTEXPR_CONSTRUCTOR LocationRange(uintptr_t start, ptrdiff_t length)
          : m_start(start)
          , m_length(length){}
        
        uintptr_t m_start;
        ptrdiff_t m_length;
    };
    
    OS216_CONSTEXPR_CONSTRUCTOR Driver(){}
    
    virtual ~Driver() {}
    
    virtual const LocationRange *getMemoryGrantRangeStart() const = 0;
    virtual size_t getMemoryGrantRangeSize() const = 0;
    
    virtual const LocationRange *getIOPortGrantRangeStart() const = 0;
    virtual size_t getIOPortGrantRangeSize() const = 0;
    
    virtual const unsigned *getInterruptGrantRangeStart() const = 0;
    virtual size_t getInterruptGrantRangeSize() const = 0;
    
    OS216_WARN_UNUSED_RESULT bool hasIOPermission(uintptr_t io_port, unsigned size) const;
    OS216_WARN_UNUSED_RESULT bool hasMemPermission(const void *addr, unsigned size) const;
    OS216_WARN_UNUSED_RESULT bool hasIntPermission(unsigned interrupt) const;
    
    template<typename DataT>
    inline void write(DataT what, void *to) const {
        if(OS216_LIKELY(hasMemPermission(to, sizeof(DataT))))
            static_cast<DataT*>(to)[0] = what;
        else
            OS216_FATAL("Driver attempted to write to an invalid location");
    }
    
    template<typename DataT>
    inline OS216_WARN_UNUSED_RESULT DataT read(const void *from) const {
        if(OS216_LIKELY(hasMemPermission(from, sizeof(DataT))))
            return static_cast<const DataT*>(from)[0];
        else
            OS216_FATAL("Driver attempted to read from an invalid location");
    }
    
    template<typename DataT>
    inline void out(DataT byte, uintptr_t to) const {
        if(OS216_LIKELY(hasIOPermission(to, sizeof(DataT))))
            OS216_IOOut(byte, to, sizeof(DataT));
        else
            OS216_FATAL("Driver attempted IO out to an invalid port");
    }
    
    template<typename DataT>
    inline OS216_WARN_UNUSED_RESULT DataT in(uintptr_t from) const {
        if(OS216_LIKELY(hasIOPermission(from, sizeof(DataT))))
            return OS216_IOIn(from, sizeof(DataT));
        else
            OS216_FATAL("Driver attempted IO out to an invalid port");
    }
};

class Bus : public Driver {
protected:
    std::vector<OS216_Device> m_devices;
public:
    
    OS216_CONSTEXPR_CONSTRUCTOR Bus(){}
    virtual ~Bus(){}
    
    virtual const OS216_Device *getDevicesStart() const { return &(m_devices[0]); }
    virtual size_t getDevicesSize() const { return m_devices.size(); }
    
};

class DeviceDriver : public Driver {
public:
    
    const struct OS216_Device &m_device;
    
    OS216_CONSTEXPR_CONSTRUCTOR DeviceDriver(const struct OS216_Device &device)
      : m_device(device){}
    
    virtual ~DeviceDriver(){}
    
    virtual void onInterrupt(unsigned vec) const = 0;
    
};

class UserDriver : public DeviceDriver {
public:
protected:
    std::vector<LocationRange> m_io_ports;
    std::vector<LocationRange> m_memory_locations;
    std::vector<unsigned> m_interrupt_vectors;
public:
    
    OS216_CONSTEXPR_CONSTRUCTOR UserDriver(const struct OS216_Device &device)
      : DeviceDriver(device){
        
    }
    
    virtual ~UserDriver() {}
    
    virtual const LocationRange *getMemoryGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getMemoryGrantRangeSize() const OS216_OVERRIDE;
    
    virtual const LocationRange *getIOPortGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getIOPortGrantRangeSize() const OS216_OVERRIDE;
    
    virtual const unsigned *getInterruptGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getInterruptGrantRangeSize() const OS216_OVERRIDE;
    
    void addIOPortGrant(const LocationRange& iop);
    void addIOPortGrant(uintptr_t start, ptrdiff_t length);
    void addMemoryGrant(const LocationRange& range);
    void addMemoryGrant(uintptr_t start, ptrdiff_t length);
    void addInterruptGrant(unsigned interrupt);
};

// These specializations have slightly more efficient representations.
template<>
void Driver::out<uint8_t>(uint8_t data, uintptr_t to) const;

template<>
void Driver::out<uint16_t>(uint16_t data, uintptr_t to) const;

template<>
void Driver::out<uint32_t>(uint32_t data, uintptr_t to) const;

template<>
uint8_t Driver::in<uint8_t>(uintptr_t from) const;

template<>
uint16_t Driver::in<uint16_t>(uintptr_t from) const;

template<>
uint32_t Driver::in<uint32_t>(uintptr_t from) const;

} // namespace os216
