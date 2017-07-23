#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void OS216_InitInterrupts(void);
void OS216_SubscribeDriver(unsigned vector, void *Driver);

#ifdef __cplusplus
} // extern "C"
#endif
