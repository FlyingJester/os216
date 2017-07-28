#include "../driver.hpp"

namespace os216 {

class PCIBus : public Bus {
    static const LocationRange pci_io_location[2];
    static const uintptr_t pci_config_address_port;
    static const uintptr_t pci_config_data_port;
    
    LocationRange m_pci_config_address;
    uint32_t m_pci_configuration_word;
    
    void *configAddress() const { return (void*)m_pci_config_address.m_start; }
    
public:
    
    PCIBus();
    
    virtual const LocationRange *getMemoryGrantRangeStart() const { return &m_pci_config_address; }
    virtual size_t getMemoryGrantRangeSize() const { return 1; }
    
    virtual const LocationRange *getIOPortGrantRangeStart() const { return pci_io_location; }
    virtual size_t getIOPortGrantRangeSize() const { return 2; }
    
    virtual const unsigned *getInterruptGrantRangeStart() const { return NULL; }
    virtual size_t getInterruptGrantRangeSize() const { return 0; }
};

} // namespace os216
