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

#ifndef OS216_KERNEL_BUS_HPP
#define OS216_KERNEL_BUS_HPP
#pragma once

// PCH must be first
#include "../cpp.hpp"

#include "../driver.hpp"
#include "../device.h"
#include "../attributes.h"

#include <vector>

namespace os216 {

struct BusPointer {
    Bus *m_bus;
public:
    BusPointer() : m_bus(NULL) {}
    
    BusPointer(BusPointer &from)
      : m_bus(from.m_bus) {
        from.m_bus = NULL;
    }
    
    BusPointer(Bus *bus)
      : m_bus(bus) {
        
    }
    
    ~BusPointer(){
        if(m_bus)
            delete m_bus;
    }
    
    BusPointer &operator=(BusPointer &from){
        if(m_bus)
            delete m_bus;
        m_bus = from.m_bus;
        from.m_bus = NULL;
        return *this;
    }
    
    BusPointer &operator=(Bus *const bus){
        if(m_bus)
            delete m_bus;
        m_bus = bus;
        return *this;
    }
    
    inline Bus &operator*() const { return *m_bus; }
    inline Bus *operator->() const { return m_bus; }
    inline Bus *get() const { return m_bus; }
};

// Creates a new instance of the system bus.
void EnumerateBuses(std::vector<BusPointer> &outBuses);

} // namespace os216

#endif // OS216_KERNEL_BUS_HPP
