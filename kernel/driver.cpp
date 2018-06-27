/* 
 *  Copyright (c) 2017-2018 Martin McDonough.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 * 
 * - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 * - Products derived from this software may not be called "os216", nor may
 *     "216" appear in their name, without prior written permission of
 *     the copyright holders.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "driver.hpp"

#include "platform/fatal.h"

/*****************************************************************************/

namespace os216 {

Driver::LocationRange::LocationRange()
  : m_start(0)
  , m_length(0){
    
}

/*****************************************************************************/

bool Driver::hasIOPermission(uintptr_t io_port, unsigned size) const {
    const Driver::LocationRange *const ranges = getIOPortGrantRangeStart();
    const size_t count = getIOPortGrantRangeSize();
    for(size_t i = 0; OS216_LIKELY(i < count); i++){
        const uintptr_t start = ranges[i].m_start;
        if(start >= io_port && io_port - start <= ranges[i].m_length - size)
            return true;
    }
    return false;
}

/*****************************************************************************/

bool Driver::hasMemPermission(const void *addr, unsigned size) const{
    const Driver::LocationRange *const ranges = getMemoryGrantRangeStart();
    const size_t count = getMemoryGrantRangeSize();
    const uintptr_t addr_i = (uintptr_t)addr;
    for(size_t i = 0; OS216_LIKELY(i < count); i++){
        const uintptr_t start = ranges[i].m_start;
        if(start >= addr_i && addr_i - start <= ranges[i].m_length - size)
            return true;
    }
    return false;
}

/*****************************************************************************/

bool Driver::hasIntPermission(unsigned interrupt) const {
    const unsigned *const interrupts = getInterruptGrantRangeStart();
    const size_t count = getInterruptGrantRangeSize();
    for(size_t i = 0; OS216_LIKELY(i < count); i++){
        if(interrupts[i] == interrupt)
            return true;
    }
    return false;
}

/*****************************************************************************/

const Driver::LocationRange *UserDriver::getMemoryGrantRangeStart() const {
    return &(m_memory_locations[0]);
}

/*****************************************************************************/

size_t UserDriver::getMemoryGrantRangeSize() const {
    return m_memory_locations.size();
}

/*****************************************************************************/

const Driver::LocationRange *UserDriver::getIOPortGrantRangeStart() const {
    return &(m_io_ports[0]);
}

/*****************************************************************************/

size_t UserDriver::getIOPortGrantRangeSize() const {
    return m_io_ports.size();
}

/*****************************************************************************/

const unsigned *UserDriver::getInterruptGrantRangeStart() const {
    return &(m_interrupt_vectors[0]);
}

/*****************************************************************************/

size_t UserDriver::getInterruptGrantRangeSize() const {
    return m_interrupt_vectors.size();
}

/*****************************************************************************/

void UserDriver::addIOPortGrant(const LocationRange& range){
    m_io_ports.push_back(range);
}

/*****************************************************************************/

void UserDriver::addIOPortGrant(uintptr_t start, ptrdiff_t length){
    const LocationRange range(start, length);
    m_io_ports.push_back(range);
}

/*****************************************************************************/

void UserDriver::addMemoryGrant(const LocationRange& range){
    m_memory_locations.push_back(range);
}

/*****************************************************************************/

void UserDriver::addMemoryGrant(uintptr_t start, ptrdiff_t length){
    const LocationRange range(start, length);
    m_memory_locations.push_back(range);
}

/*****************************************************************************/

void UserDriver::addInterruptGrant(unsigned interrupt){
    m_interrupt_vectors.push_back(interrupt);
}

/*****************************************************************************/

template<>
void Driver::out<uint8_t>(uint8_t data, uintptr_t to) const {
    if(OS216_LIKELY(hasIOPermission(to, 1)))
        OS216_IOOut8(data, to);
    else
        OS216_FATAL("Driver attempted IO out to an invalid port");
}

/*****************************************************************************/

template<>
void Driver::out<uint16_t>(uint16_t data, uintptr_t to) const {
    if(OS216_LIKELY(hasIOPermission(to, 2)))
        OS216_IOOut16(data, to);
    else
        OS216_FATAL("Driver attempted IO out to an invalid port");
}

/*****************************************************************************/

template<>
void Driver::out<uint32_t>(uint32_t data, uintptr_t to) const {
    if(OS216_LIKELY(hasIOPermission(to, 4)))
        OS216_IOOut32(data, to);
    else
        OS216_FATAL("Driver attempted IO out to an invalid port");
}

/*****************************************************************************/

template<>
uint8_t Driver::in<uint8_t>(uintptr_t from) const {
    if(OS216_LIKELY(hasIOPermission(from, 1)))
        return OS216_IOIn8(from);
    else
        OS216_FATAL("Driver attempted IO in to an invalid port");
}

/*****************************************************************************/

template<>
uint16_t Driver::in<uint16_t>(uintptr_t from) const {
    if(OS216_LIKELY(hasIOPermission(from, 2)))
        return OS216_IOIn16(from);
    else
        OS216_FATAL("Driver attempted IO in to an invalid port");
}

/*****************************************************************************/

template<>
uint32_t Driver::in<uint32_t>(uintptr_t from) const {
    if(OS216_LIKELY(hasIOPermission(from, 4)))
        return OS216_IOIn32(from);
    else
        OS216_FATAL("Driver attempted IO in to an invalid port");
}

/*****************************************************************************/

} // namespace os216
