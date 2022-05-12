#include"word.h"
#include"debug.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

boolean isNumberChar(const char c){
    int ascii = (int)c;
    if((int)'0' <= ascii && ascii <= (int)'9')return True;
    return False;
}
boolean isNumberString(const char* string){
    int len = strlen(string);
    for(int i = 0;i<len;i++){
        if(isNumberChar(string[i]) == False)return False;
    }
    return True;
}
boolean isEnglishChar(const char c){
    int ascii = (int)c;
    if((int)'a' <= ascii && ascii <= (int)'z')return True;
    if((int)'A' <= ascii && ascii <= (int)'Z')return True;
    return False;
}
boolean isEnglishString(const char* string){
    int len = strlen(string);
    for(int i = 0;i<len;i++){
        if(isEnglishChar(string[i]) == False)return False;
    }
    return True;
}
boolean isEnglishWithNumber(const char* string){
    int len = strlen(string);
    for(int i = 0;i<len;i++){
        if(isEnglishChar(string[i]) == False && isNumberChar(string[i]) == False)return False;
    }
    return True;
}
/**
 * 把字串末的換行符號去掉
 * @param string
 */
void trimString(char* string){
    int len = strlen(string);
    if(string[len-1] == '\n')string[len-1] = '\0';
}
int toIntValue(const char* string){
    return atoi(string);
}
char* intToString(char* string,int value){
    return _itoa(value,string,strlen(string));
}