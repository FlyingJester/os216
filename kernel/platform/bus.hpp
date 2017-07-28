#pragma once
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
