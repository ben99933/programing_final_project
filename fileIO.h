#include<stdio.h>
#include<stdlib.h>
#include"date.h"
#ifndef FILEIO_H
    #define FILEIO_H
    
    char* getDocumentPath();
    char* getAccountPath();
    char* getRecordPath();
    void fileIO_init();

    FILE* findAccountFile(const char* accountName);
    FILE* creatAccountFile(const char* accountName);

    FILE* findSpendFile(const char* accountName,Date* date);
    FILE* creatdSpendFile(const char* accountName,Date* date);

    FILE* findRecorderFile(const char* accountName);
    FILE* createRecorderFile(const char* accountName);
    
    FILE* getSpendFile(int year,int month,const char* accountName);

    //int fileExist(const char* path);

    void recordSpend(int year,int month, int day, int category, int cost, char remark[16], const char* accountName);
    void closeFile(FILE* file);

#endif
