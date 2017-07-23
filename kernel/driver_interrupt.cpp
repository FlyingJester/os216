#include "cpp.hpp"
#include "driver_interrupt.h"
#include "driver.hpp"

void OS216_CallDriverAtInterrupt(void *driver, unsigned vector){
    static_cast<os216::Driver*>(driver)->onInterrupt(vector);
}
