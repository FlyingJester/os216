/* 
 *  Copyright (c) 2017 Martin McDonough.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 * 
 * - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 * - Products derived from this software may not be called "os216", nor may
 *     "216" appear in their name, without prior written permission of
 *     the copyright holders.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "pci_utils.h"

/*****************************************************************************/

#define OS216_NUM_NAMES (unsigned)OS216_NUM_KNOWN_DEVICES

/*****************************************************************************/

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

/*****************************************************************************/

const char *OS216_PCIClassName(enum OS216_EnumPCIClass clazz){
    const unsigned clazz_num = (unsigned)clazz;
    
    if(clazz_num < OS216_NUM_NAMES)
        return os216_pci_class_names[clazz_num];
    else if(clazz_num == 0xFF)
        return "Unknown Device";
    else
        return "Reserved Device";
}

/*****************************************************************************/
