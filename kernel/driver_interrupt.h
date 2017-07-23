#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void OS216_CallDriverAtInterrupt(void *driver, unsigned vector);

#ifdef __cplusplus
} // extern "C"
#endif
