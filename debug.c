#include"debug.h"
#include<stdio.h>


static boolean debugMode = False;

void debugMsg(const char* string, const char* fileName, const int line){
    if(!debugMode)return;
    printf("%s, from %s : line %d\n",string, fileName, line);
}
void errorMsg(const char* string, const char* fileName, const int line){
    if(!debugMode)return;
    printf("Error : %s, from %s : line %d\n",string, fileName, line);
}
boolean isDebugMode(){
    return debugMode;
}
void debugOn(){
    debugMode = True;
    printf("Debug mode on.\n");
}
void debugOff(){
    debugMode = False;
    printf("Debug mode off.\n");
}