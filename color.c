#include"color.h"
#include<stdio.h>

void setTextColor(const char* colorFormat){
    printf("%s",colorFormat);
}
void resetTextColor(){
    setTextColor(ColorReset);
}