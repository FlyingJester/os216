#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum OS216_PC_PrintMode {
    eOS216_PC_Normal,
    eOS216_PC_Warning,
    eOS216_PC_Error,
    eOS216_PC_Fatal,
    eOS216_PC_NUM_MODES
};

void OS216_PC_PrintString(enum OS216_PC_PrintMode mode, const char *msg);
void OS216_PC_PrintChar(enum OS216_PC_PrintMode mode, char c);
void OS216_PC_Newline(enum OS216_PC_PrintMode mode);
void OS216_PC_NewScreen(enum OS216_PC_PrintMode mode);
void OS216_PC_ClearScreen(enum OS216_PC_PrintMode mode);
void OS216_PC_PrintInteger(enum OS216_PC_PrintMode mode, int i);
void OS216_PC_PrintAddress(enum OS216_PC_PrintMode mode, void *p);

#ifdef __cplusplus
} // extern "C"
#endif
