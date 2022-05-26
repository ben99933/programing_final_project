#include"dataType.h"

#ifndef WORD_H
    #define WORD_H

    boolean isNumberChar(const char c);
    boolean isNumberString(const char* string);
    boolean isEnglishChar(const char c);
    boolean isEnglishString(const char* string);
    boolean isEnglishWithNumber(const char* string);
    
    
    void trimString(char* string);
    int toIntValue(const char* string);
    char* intToString(char* string,int value);
    char toHexChar(int num);
#endif