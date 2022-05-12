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
    void closeFile(FILE* file);

#endif
