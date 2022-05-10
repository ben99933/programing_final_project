#include<stdio.h>
#include<stdlib.h>
#ifndef FILEIO_H
    #define FILEIO_H
    
    char* getDocumentPath();
    char* getAccountPath();
    void fileIO_init();
    FILE* findAccountFile(const char* accountName);
    FILE* creatAccountFile(const char* accountName);
    void closeFile(FILE* file);

#endif
