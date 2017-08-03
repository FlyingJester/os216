#include "pci.hpp"
#include "../platform/print.h"

// This file contains the logic to enumerate the PCI bus. The utilities to do this (including class
// codes and functional types) is in pci_utils. The IO abstraction is provided by the driver class.

namespace os216 {

static OS216_CONSTEXPR_VALUE uintptr_t pci_config_address_port = 0x0CF8;
static OS216_CONSTEXPR_VALUE uintptr_t pci_config_data_port = 0x0CFC;

#define OS216_PCI_NUM_PCI_IO_PORTS 2
OS216_CONSTEXPR_VALUE Driver::LocationRange pci_io_location[OS216_PCI_NUM_PCI_IO_PORTS] = {
    Driver::LocationRange(pci_config_address_port, 4),
    Driver::LocationRange(pci_config_data_port, 4)
};

PCIBus::PCIBus()
  : m_pci_config_address(in<uint32_t>(pci_config_address_port), 4)
  , m_pci_configuration_word(read<uint32_t>(configAddress())){
    
    // Enumerate the bus.
    
    
}

const Driver::LocationRange *PCIBus::getMemoryGrantRangeStart() const {
    return &m_pci_config_address;
}

size_t PCIBus::getMemoryGrantRangeSize() const {
    return 1;
}

const Driver::LocationRange *PCIBus::getIOPortGrantRangeStart() const {
    return pci_io_location;
}

size_t PCIBus::getIOPortGrantRangeSize() const {
    return OS216_PCI_NUM_PCI_IO_PORTS;
}

const unsigned *PCIBus::getInterruptGrantRangeStart() const {
    return NULL;
}

size_t PCIBus::getInterruptGrantRangeSize() const {
    return 0;
}

} // namespace os216
