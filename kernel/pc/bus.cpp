#include "../platform/bus.hpp"

#include "pci.hpp"

namespace os216 {

void EnumerateBuses(std::vector<BusPointer> &outBuses){
    outBuses.clear();
    // TODO: Check for PCIe.
    BusPointer ptr(new PCIBus());
    outBuses.push_back(ptr);
}

} // namespace os216 {

