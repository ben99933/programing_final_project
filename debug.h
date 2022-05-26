#include"dataType.h"

#ifndef DEBUG_H
    #define DEBUG_H
    #define deprecated

    void debugMsg(const char* string, const char* fileName, const int line);
    void errorMsg(const char* string, const char* fileName, const int line);
    boolean isDebugMode();
    void debugOn();
    void debugOff();
#endif