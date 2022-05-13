#include"recorder.h"
#include"fileIO.h"

void recordSpend(int year,int month, int day, int category, int cost, char note[16], const char* accountName){
    FILE* file = getSpendFile(year,month,accountName);
    fprintf(file,"%d,%d,%d,%d,%d,%s\n",year,month,day,category,cost,note);
    closeFile(file);
}