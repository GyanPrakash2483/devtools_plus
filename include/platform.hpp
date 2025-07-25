#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS
#elif defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    #define OS_UNIX
#else
    #define OS_UNKNOWN
    #error "Unsupported or Unknown operating system"
#endif