#pragma once
#ifndef OS216_PCI_UTILS_H
#define OS216_PCI_UTILS_H

#include "../attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

enum OS216_EnumPCIClass {
    OS216_ePCIAncientDevice = 0,    /* 0  */
    OS216_ePCIMassStorage,          /* 1  */
    OS216_ePCINetworkController,    /* 2  */
    OS216_ePCIDisplayController,    /* 3  */
    OS216_ePCIMultimediaController, /* 4  */
    OS216_ePCIMemoryController,     /* 5  */
    OS216_ePCIBridgeDevice,         /* 6  */
    OS216_ePCISimpleComDevice,      /* 7  */
    OS216_ePCIBaseSystemPeripheral, /* 8  */
    OS216_ePCIInputDevice,          /* 9  */
    OS216_ePCIDockingStation,       /* 10 */
    OS216_ePCIProcessor,            /* 11 */
    OS216_ePCISerialBusController,  /* 12 */
    OS216_ePCIWifiController,       /* 13 */
    OS216_ePCISmartIOController,    /* 14 */
    OS216_ePCISatelliteComDevice,   /* 15 */
    OS216_ePCICryptoDevice,         /* 16 */
    OS216_ePCIDSP,                  /* 17 */
    OS216_NUM_KNOWN_DEVICES,
    OS216_ePCIUnknown = 0xFF
};

enum OS216_EnumPCIAncientFunctions {
    OS216_eAncientNotVGADevice = 0,
    OS216_eAncientVGADevice,        /* 1  */
    OS216_NUM_KNOWN_ANCIENT_FUNCTIONS
};

enum OS216_EnumPCIMassStorageFunctions {
    OS216_eStorageSCSIController = 0,
    OS216_eStorageIDEController,    /* 1  */
    OS216_eStorageFloppyController, /* 2  */
    OS216_eStorageIPIBusController, /* 3  */
    OS216_eStorageRAIDController,   /* 4  */
    OS216_eStorageATAController,    /* 5  */
    OS216_eStorageSATAController,   /* 6  */    
    OS216_eStorageSASController,    /* 7  */
    OS216_NUM_KNOWN_STORAGE_FUNCTIONS
};

enum OS216_EnumPCINetworkFunctions {
    OS216_eEthernetController = 0
    OS216_NUM_KNOWN_NETWORK_FUNCTIONS
};

enum OS216_EnumPCIDisplayFunctions {
    OS216_eDisplayVGAController = 0,
    OS216_eDisplay8512Controller,   /* 1  */
    OS216_eDisplayXGAController,    /* 2  */
    OS216_eDisplay3DController,     /* 3  */
    OS216_NUM_KNOWN_DISPLAY_FUNCTIONS
};

enum OS216_EnumPCIMultimediaFunctions {
    OS216_eMediaVideoDevice = 0,
    OS216_eMediaAudioDevice,        /* 1  */
    OS216_eMediaTelephony,          /* 2  */
    OS216_NUM_KNOWN_MEDIA_FUNCTIONS
};

enum OS216_EnumPCIMemoryFunctions {
    OS216_eMemoryRAMController = 0,
    OS216_eMemoryFlashController,   /* 1  */
    OS216_NUM_KNOWN_MEMORY_FUNCTIONS
};

enum OS216_EnumPCIBridgeFunctions {
    OS216_eBridgeHostBridge = 0,
    OS216_eBridgeISABridge,         /* 1  */
    OS216_eBridgeEISABridge,        /* 2  */
    OS216_eBridgeMCABridge,         /* 3  */
    OS216_eBridgePCIBridge,         /* 4  */
    OS216_eBridgePCMCIABridge,      /* 5  */
    OS216_eBridgeNuBusBridge,       /* 6  */
    OS216_eBridgeCardBusBridge,     /* 7  */
    OS216_NUM_KNOWN_BRIDGE_FUNCTIONS
};

enum OS216_EnumPCIComFunctions {
    OS216_eComSerialController = 0,
    OS216_eComParallelController,   /* 1  */
    OS216_eComMultiSerialController,/* 2  */
    OS216_eComModem,                /* 3  */
    OS216_NUM_KNOWN_COM_FUNCTIONS
};

enum OS216_EnumPCIBaseFunctions {
    OS216_eBaseInterruptController = 0,
    OS216_eBaseDMAController,       /* 1  */
    OS216_eBaseTimer,               /* 2  */
    OS216_eBaseRTC,                 /* 3  */
    OS216_eBaseHotPlugController,   /* 4  */    
    OS216_NUM_KNOWN_BASE_FUNCTIONS
};

enum OS216_EnumPCIInputFunctions {
    OS216_eInputKeyboard = 0,
    OS216_eInputDigitizer,          /* 1  */
    OS216_eInputMouseController,    /* 2  */
    OS216_eInputScannerController,  /* 3  */
    OS216_eInputGameport,           /* 4  */
    OS216_NUM_KNOWN_INPUT_FUNCTIONS
};

enum OS216_EnumPCIProcessorFunctions {
    OS216_eProcessorPCI386 = 0,
    OS216_eProcessorPCI486,         /* 1  */
    OS216_eProcessorPCIPentium,     /* 2  */
    OS216_NUM_KNOWN_INPUT_FUNCTIONS
};

OS216_MEMORY_PURE const char *OS216_PCIClassName(enum OS216_EnumPCIClass);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
