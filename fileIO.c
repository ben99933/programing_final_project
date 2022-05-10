#include"fileIO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <shlobj.h>
#include<direct.h>


typedef char* Path;

CHAR documentPath[MAX_PATH];
CHAR accountPath[MAX_PATH];

static FILE* readFile(const char* path){
    printf("read file, path=%s\n",path);
    FILE* file = fopen(path,"r");
    return file;
}
static FILE* createFile(const char* path){
    printf("write file, path=%s\n",path);
    FILE* file = fopen(path,"w");
    return file;
}
FILE* findAccountFile(const char* accountName){
    char path[1024];
    path[0] = '\0';
    strcat(path,accountPath);
    strcat(path,"\\");
    strcat(path,accountName);
    strcat(path,".txt");
    
    FILE* file = readFile(path);
}
FILE* creatAccountFile(const char* accountName){
    char path[1024];
    path[0] = '\0';
    strcat(path,accountPath);
    strcat(path,"\\");
    strcat(path,accountName);
    strcat(path,".txt");
    _mkdir(path);
    FILE* file = createFile(path);
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
    HRESULT result = SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, documentPath);
    
    strcat(documentPath,"\\ProgramingFinalProject");
    strcat(accountPath,documentPath);
    strcat(accountPath,"\\account");
    printf("documentPath=%s\n",documentPath);
    //printf("documentPath=%s\n",documentPath);
    //printf("accountPath=%s\n",accountPath);
}
void closeFile(FILE* file){
    fclose(file);
}