#include "../driver.hpp"

namespace os216 {

class PCIBus : public Bus {
    
    LocationRange m_pci_config_address;
    uint32_t m_pci_configuration_word;
    
    void *configAddress() const { return (void*)m_pci_config_address.m_start; }
    
public:
    
    PCIBus();
    
    virtual const LocationRange *getMemoryGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getMemoryGrantRangeSize() const OS216_OVERRIDE;
    
    virtual const LocationRange *getIOPortGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getIOPortGrantRangeSize() const OS216_OVERRIDE;
    
    virtual const unsigned *getInterruptGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getInterruptGrantRangeSize() const OS216_OVERRIDE;
};

} // namespace os216
