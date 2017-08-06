#include "../driver.hpp"

namespace os216 {

class PCIBus : public Bus {
    
public:
    
    PCIBus();
    
    virtual const LocationRange *getMemoryGrantRangeStart() const OS216_OVERRIDE { return NULL; }
    virtual size_t getMemoryGrantRangeSize() const OS216_OVERRIDE { return 0; }
    
    virtual const LocationRange *getIOPortGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getIOPortGrantRangeSize() const OS216_OVERRIDE;
    
    virtual const unsigned *getInterruptGrantRangeStart() const OS216_OVERRIDE;
    virtual size_t getInterruptGrantRangeSize() const OS216_OVERRIDE;
};

} // namespace os216
