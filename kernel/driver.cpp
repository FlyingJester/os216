#include "driver.hpp"

#include "arch/io.h"
#include "platform/fatal.h"

namespace os216 {

bool Driver::hasIOPermission(uint8_t io_port) const {
    const uint8_t *const ports = getIOPortGrantRangeStart();
    const size_t count = getIOPortGrantRangeSize();
    for(size_t i = 0; i < count; i++){
        if(ports[i] == io_port)
            return true;
    }
    return false;
}

bool Driver::hasMemPermission(const void *addr, unsigned size) const{
    const Driver::MemoryLocationRange *const ranges = getMemoryGrantRangeStart();
    const size_t count = getMemoryGrantRangeSize();
    const uintptr_t addr_i = (uintptr_t)addr;
    for(size_t i = 0; i < count; i++){
        const uintptr_t start = ranges[i].m_start;
        if(start >= addr_i && addr_i - start <= ranges[i].m_length - size)
            return true;
    }
    return false;
}

bool Driver::hasIntPermission(unsigned interrupt) const {
    const unsigned *const interrupts = getInterruptGrantRangeStart();
    const size_t count = getInterruptGrantRangeSize();
    for(size_t i = 0; i < count; i++){
        if(interrupts[i] == interrupt)
            return true;
    }
    return false;
}

void Driver::out(uint8_t byte, uint8_t to) const {
    if(OS216_LIKELY(hasIOPermission(to)))
        OS216_IOOut(byte, to);
    else
        OS216_FATAL("Driver attempted IO out to an invalid port");
}

uint8_t Driver::in(uint8_t from) const {
    if(OS216_LIKELY(hasIOPermission(from)))
        return OS216_IOIn(from);
    else
        OS216_FATAL("Driver attempted IO out to an invalid port");
}

KernelDriver::KernelDriver(const uint8_t *io_ports, size_t num_io_ports,
    const MemoryLocationRange *memory_locations, size_t num_memory_locations,
    const unsigned *interrupt_vectors, size_t num_interrupt_vectors)
  : m_io_ports(io_ports)
  , m_num_io_ports(num_io_ports)
  , m_memory_locations(memory_locations)
  , m_num_memory_locations(num_memory_locations)
  , m_interrupt_vectors(interrupt_vectors)
  , m_num_interrupt_vectors(num_interrupt_vectors){
    
}
    
const Driver::MemoryLocationRange *KernelDriver::getMemoryGrantRangeStart() const {
    return m_memory_locations;
}

size_t KernelDriver::getMemoryGrantRangeSize() const {
    return m_num_memory_locations;
}

const uint8_t *KernelDriver::getIOPortGrantRangeStart() const {
    return m_io_ports;
}

size_t KernelDriver::getIOPortGrantRangeSize() const {
    return m_num_io_ports;
}

const unsigned *KernelDriver::getInterruptGrantRangeStart() const {
    return m_interrupt_vectors;
}

size_t KernelDriver::getInterruptGrantRangeSize() const {
    return m_num_interrupt_vectors;
}

const Driver::MemoryLocationRange *UserDriver::getMemoryGrantRangeStart() const {
    return &(*m_memory_locations.begin());
}

size_t UserDriver::getMemoryGrantRangeSize() const {
    return m_memory_locations.size();
}

const uint8_t *UserDriver::getIOPortGrantRangeStart() const {
    return &(*m_io_ports.begin());
}

size_t UserDriver::getIOPortGrantRangeSize() const {
    return m_io_ports.size();
}

const unsigned *UserDriver::getInterruptGrantRangeStart() const {
    return &(*m_interrupt_vectors.begin());
}

size_t UserDriver::getInterruptGrantRangeSize() const {
    return m_interrupt_vectors.size();
}

void UserDriver::addIOPortGrant(uint8_t iop){
    m_io_ports.push_back(iop);
}

void UserDriver::addMemoryGrant(const MemoryLocationRange& range){
    m_memory_locations.push_back(range);
}

void UserDriver::addMemoryGrant(uintptr_t start, ptrdiff_t length){
    const MemoryLocationRange range = {start, length};
    m_memory_locations.push_back(range);
}

void UserDriver::addInterruptGrant(unsigned interrupt){
    m_interrupt_vectors.push_back(interrupt);
}

} // namespace os216
