#pragma once
#ifndef OS216_PRINT_H
#define OS216_PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

void OS216_PrintString(const char *msg);
void OS216_PrintChar(char c);
void OS216_Newline(void);
void OS216_NewScreen(void);
void OS216_ClearScreen(void);
void OS216_PrintInteger(int i);
void OS216_PrintAddress(void *p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* OS216_PRINT_H */
