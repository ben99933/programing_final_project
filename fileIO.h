#include<stdio.h>
#include<stdlib.h>
#ifndef FILEIO_H
    #define FILEIO_H
    
    char* getDocumentPath();
    char* getAccountPath();
    void fileIO_init();
    FILE* findAccountFile(const char* accountName);
    void closeAccountFile(const char* accountName);
#endif
