#include "pci_utils.h"

#define OS216_NUM_NAMES (unsigned)OS216_NUM_KNOWN_DEVICES

static const char *const os216_pci_class_names[OS216_NUM_NAMES] = {
    
    "Ancient Device",
    "Mass Storage",
    "Network Controller",
    "Display Controller",
    "Multimedia Controller",
    "Memory Controller",
    "Bridge Device",
    "Simple Communications Device",
    "Base System Peripheral",
    "Input Device",
    "Docking Station",
    "Processor",
    "Serial Bus Controller",
    "Wifi Controller",
    "Smart IO Controller",
    "Satellite Communications Device",
    "Crypto Device",
    "DSP"
};

const char *OS216_PCIClassName(enum OS216_EnumPCIClass clazz){
    const unsigned clazz_num = (unsigned)clazz;
    
    if(clazz_num < OS216_NUM_NAMES)
        return os216_pci_class_names[clazz_num];
    else if(clazz_num == 0xFF)
        return "Unknown Device";
    else
        return "Reserved Device";
}
