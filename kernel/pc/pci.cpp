#include "../platform/bus.hpp"

namespace os216 {

class PCIBus : public Bus {
    static const LocationRange pci_io_location; 
public:
    
    PCIBus();
    
    virtual const LocationRange *getMemoryGrantRangeStart() const { return NULL; }
    virtual size_t getMemoryGrantRangeSize() const { return 0; }
    
    virtual const LocationRange *getIOPortGrantRangeStart() const { return &pci_io_location; }
    virtual size_t getIOPortGrantRangeSize() const { return 1; }
    
    virtual const unsigned *getInterruptGrantRangeStart() const { return NULL; }
    virtual size_t getInterruptGrantRangeSize() const { return 0; }
};

const Driver::LocationRange PCIBus::pci_io_location = {0x0CF8, 8};

PCIBus::PCIBus(){
    
}

void EnumerateBuses(std::vector<BusPointer> &outBuses){
    outBuses.clear();
}

} // namespace os216
