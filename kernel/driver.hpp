#pragma once
#include "cpp.hpp"

#include "platform/fatal.h"

#include "attributes.h"

#include <vector>

namespace os216 {

class Driver {
public:
    
    struct MemoryLocationRange{
        uintptr_t m_start;
        ptrdiff_t m_length;
    };
    
    Driver() {}
    virtual ~Driver() {}
    
    virtual const MemoryLocationRange *getMemoryGrantRangeStart() const = 0;
    virtual size_t getMemoryGrantRangeSize() const = 0;
    
    virtual const uint8_t *getIOPortGrantRangeStart() const = 0;
    virtual size_t getIOPortGrantRangeSize() const = 0;
    
    virtual const unsigned *getInterruptGrantRangeStart() const = 0;
    virtual size_t getInterruptGrantRangeSize() const = 0;
    
    virtual void onInterrupt(unsigned vec) const = 0;
    
    bool hasIOPermission(uint8_t io_port) const;
    bool hasMemPermission(const void *addr, unsigned size) const;
    bool hasIntPermission(unsigned interrupt) const;
    
    template<typename DataT>
    void write(DataT what, void *to) const {
        if(OS216_LIKELY(hasMemPermission(to, sizeof(DataT))))
            static_cast<DataT*>(to)[0] = what;
        else
            OS216_FATAL("Driver attempted to write to an invalid location");
    }
    
    template<typename DataT>
    DataT read(const void *from) const {
        if(OS216_LIKELY(hasMemPermission(from, sizeof(DataT))))
            return static_cast<const DataT*>(from)[0];
        else
            OS216_FATAL("Driver attempted to read from an invalid location");
    }
    
    void write8(uint8_t byte, void *to) const { write<uint8_t>(byte, to); }
    
    void write16(uint16_t word, void *to) const { write<uint16_t>(word, to); }
    void write32(uint32_t dword, void *to) const { write<uint32_t>(dword, to); }
    void write64(uint64_t qword, void *to) const { write<uint64_t>(qword, to); }
    
    uint8_t read8(const void *from) const { return read<uint8_t>(from); }
    uint16_t read16(const void *from) const { return read<uint16_t>(from); }
    uint32_t read32(const void *from) const { return read<uint32_t>(from); }
    uint64_t read64(const void *from) const { return read<uint64_t>(from); }
    
    void out(uint8_t byte, uint8_t to) const;
    uint8_t in(uint8_t from) const;
};

class KernelDriver : public Driver {
    const uint8_t *const m_io_ports;
    const size_t m_num_io_ports;
    
    const MemoryLocationRange *const m_memory_locations;
    const size_t m_num_memory_locations;
    
    const unsigned *const m_interrupt_vectors;
    const size_t m_num_interrupt_vectors;
    
public:
    
    KernelDriver(const uint8_t *io_ports, size_t num_io_ports,
        const MemoryLocationRange *memory_locations, size_t num_memory_locations,
        const unsigned *interrupt_vectors, size_t num_interrupt_vectors);
    
    virtual ~KernelDriver(){}
    
    virtual const MemoryLocationRange *getMemoryGrantRangeStart() const;
    virtual size_t getMemoryGrantRangeSize() const;
    
    virtual const uint8_t *getIOPortGrantRangeStart() const;
    virtual size_t getIOPortGrantRangeSize() const;
    
    virtual const unsigned *getInterruptGrantRangeStart() const;
    virtual size_t getInterruptGrantRangeSize() const;
};

class UserDriver : public Driver {
public:
protected:
    std::vector<uint8_t> m_io_ports;
    std::vector<MemoryLocationRange> m_memory_locations;
    std::vector<unsigned> m_interrupt_vectors;
public:
    
    UserDriver() {}
    virtual ~UserDriver() {}
    
    virtual const MemoryLocationRange *getMemoryGrantRangeStart() const;
    virtual size_t getMemoryGrantRangeSize() const;
    
    virtual const uint8_t *getIOPortGrantRangeStart() const;
    virtual size_t getIOPortGrantRangeSize() const;
    
    virtual const unsigned *getInterruptGrantRangeStart() const;
    virtual size_t getInterruptGrantRangeSize() const;
    
    void addIOPortGrant(uint8_t iop);
    void addMemoryGrant(const MemoryLocationRange& range);
    void addMemoryGrant(uintptr_t start, ptrdiff_t length);
    void addInterruptGrant(unsigned interrupt);
};

} // namespace os216
