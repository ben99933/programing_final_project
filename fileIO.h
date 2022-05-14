#include<stdio.h>
#include<stdlib.h>
#include"date.h"
#ifndef FILEIO_H
    #define FILEIO_H
    
    extern FILE* fileBuffer[16];

    char* getDocumentPath();
    char* getAccountPath();
    char* getRecordPath();
    
    void fileIO_init();
    typedef enum WriteMode{
        readMode,appendMode,coverMode
    }OpenMode;
    FILE* findAccountFile(const char* accountName);
    FILE* creatAccountFile(const char* accountName);

    FILE* findSpendFile(const char* accountName,Date* date);
    FILE* creatdSpendFile(const char* accountName,Date* date);

    FILE* findRecorderFile(const char* accountName);
    FILE* createRecorderFile(const char* accountName);
    
    FILE* getSpendFile(int year,int month,const char* accountName,OpenMode mode);

    //int fileExist(const char* path);

    void recordSpend(int year,int month, int day, int category, int cost, char remark[16], const char* accountName);
    void closeFile(FILE* file);
    void clearFileBuffer();
#endif
