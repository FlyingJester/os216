#include "pci.hpp"
#include "../platform/print.h"

// This file contains the logic to enumerate the PCI bus. The utilities to do this (including class
// codes and functional types) is in pci_utils. The IO abstraction is provided by the driver class.

namespace os216 {

const uintptr_t PCIBus::pci_config_address_port = 0x0CF8;
const uintptr_t PCIBus::pci_config_data_port = 0x0CFC;

const Driver::LocationRange PCIBus::pci_io_location[2] = {
    LocationRange(pci_config_address_port, 4),
    LocationRange(pci_config_data_port, 4)
};

PCIBus::PCIBus()
  : m_pci_config_address(in<uint32_t>(pci_config_address_port), 4)
  , m_pci_configuration_word(read<uint32_t>(configAddress())){
    
}

} // namespace os216
