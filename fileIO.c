#include"fileIO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <shlobj.h>

typedef char* Path;

CHAR documentPath[MAX_PATH];
CHAR accountPath[MAX_PATH];

static FILE* findFile(const char* path){
    
    printf("path=%s\n",path);
    FILE* file = fopen(path,"r");
    if(!file){
        return NULL;
    }else{
        return file;
    }
}
FILE* findAccountFile(const char* accountName){
    char path[1024];
    strcat(path,accountPath);
    strcat(path,"\\");
    strcat(path,accountName);
    strcat(path,".txt");
    FILE* file = findFile(path);
}
static int findDir(const char* path){
    return 1;
}
char* getDocumentPath(){
    return documentPath;
}
char* getAccountPath(){
    return accountPath;
}

void fileIO_init(){
    documentPath[0] = '\0';
    accountPath[0] = '\0';
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, documentPath);
    strcat(documentPath,"\\finalProject");
    strcat(accountPath,documentPath);
    strcat(accountPath,"\\account");
    //printf("documentPath=%s\n",documentPath);
    //printf("accountPath=%s\n",accountPath);
}
void closeFile(FILE* file){
    fclose(file);
}
void closeAccountFile(const char* accountName){

}