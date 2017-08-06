#include "pci.hpp"
#include "../platform/print.h"
#include "../assert.h"

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

static OS216_CONSTEXPR_VALUE uint32_t os216_max_bus_number = 0x7F;
static OS216_CONSTEXPR_VALUE uint32_t os216_max_device_number = 0x1F;
static OS216_CONSTEXPR_VALUE uint32_t os216_max_function_number = 0x07;
static OS216_CONSTEXPR_VALUE uint32_t os216_max_register_number = 0x3F;

static inline uint32_t os216_construct_pci_data(
    uint32_t bus_num,
    uint32_t dev_num,
    uint32_t func_num,
    uint32_t reg_num,
    bool enabled = true){
    
    OS216_ASSERT(bus_num <= os216_max_bus_number, "Bus number is too large");
    OS216_ASSERT(dev_num <= os216_max_device_number, "Device number is too large");
    OS216_ASSERT(func_num <= os216_max_function_number, "Function number is too large");
    OS216_ASSERT(reg_num <= os216_max_register_number, "Register number is too large");
    
    return (enabled ? 0x80000000 : 0) |
        (bus_num << 16) |
        (dev_num << 11) |
        (func_num << 8) |
        (reg_num << 2);
}

PCIBus::PCIBus(){
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
    // Enumerate the bus. This is done by reading in device info until we get an initial read of
    // a vender of 0xFFFF
    for(unsigned bus_num = 0; bus_num < os216_max_bus_number; bus_num++){
        for(unsigned dev_num = 0; dev_num < os216_max_device_number; dev_num++){
            uint32_t registers[16];
            for(unsigned i = 0; i < 16; i++){
                const uint32_t data = os216_construct_pci_data(bus_num, dev_num, 0, i);
                out<uint32_t>(data, pci_config_address_port);
                registers[i] = in<uint32_t>(pci_config_data_port);
            }
            
            // If the data is all ones, then this device does not exist, and we reached the end of
            // the configuration space.
            if(*registers == 0xFFFFFFFF){
                if(dev_num == 0)
                    return;
                break;
            }
            const uint16_t vendor = registers[0] & 0xFFFF,
                device_id = registers[0] >> 16;
            
            const uint16_t command = registers[1] & 0xFFFF,
                status = registers[1] >> 16;
            
            const uint8_t rev_id = registers[2] & 0xFF,
                prog_if = (registers[2] >> 8) & 0xFF,
                subclass = (registers[2] >> 16) & 0xFF,
                class_code = (registers[2] >> 24) & 0xFF;
            
            const uint8_t cache_line_size = registers[3] & 0xFF,
                latency_timer = (registers[3] >> 8) & 0xFF,
                header_type = (registers[3] >> 16) & 0xFF,
                bist = (registers[3] >> 24) & 0xFF;
            
            const uint32_t base_address0 = registers[4];
            const uint32_t base_address1 = registers[5];
            const uint32_t base_address2 = registers[6];
            const uint32_t base_address3 = registers[7];
            const uint32_t base_address4 = registers[8];
            const uint32_t base_address5 = registers[9];
            
            const uint32_t cardbus_why = registers[10];
            
            const uint16_t subsystem_vendor_id = registers[11] & 0xFFFF,
                subsystem_id = registers[11] >> 16;
            
            const uint32_t rom_address = registers[12];
            
            // The upper 24 bits of 13 is reserved.
            const uint32_t capabilities_ptr = registers[13] & 0xFF;
            
            // 14 is reserved.
            
            const uint8_t max_latency = registers[15] & 0xFF,
                min_grant = (registers[15] >> 8) & 0xFF,
                interrupt_pin = (registers[15] >> 16) & 0xFF,
                interrupt_line = (registers[15] >> 24) & 0xFF;
        }
    }
    #pragma GCC diagnostic pop
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
