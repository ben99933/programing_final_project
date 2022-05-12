#include"fileIO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <shlobj.h>
#include<direct.h>


CHAR documentPath[MAX_PATH];
CHAR accountPath[MAX_PATH];

static void pathAppend(char* path,const char* destination){
    if(path[0]=='\0'){
        strcpy(path,destination);
        return;
    }
    strcat(path,"\\");
    strcat(path,destination);
}

static FILE* readFile(const char* path){
    //printf("read file, path=%s\n",path);
    FILE* file = fopen(path,"r");
    return file;
}
static FILE* createFile(const char* path){
    //printf("write file, path=%s\n",path);
    FILE* file = fopen(path,"w");
    return file;
}
FILE* findAccountFile(const char* accountName){
    char path[1024];
    path[0] = '\0';
    pathAppend(path,accountPath);
    pathAppend(path,accountName);
    strcat(path,".txt");
    FILE* file = readFile(path);

    return file;
}
FILE* creatAccountFile(const char* accountName){
    char path[1024];
    path[0] = '\0';
    pathAppend(path,accountPath);
    pathAppend(path,accountName);
    strcat(path,".txt");
    
    FILE* file = createFile(path);
    return file;
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
    
    pathAppend(documentPath,"finalProject");
    pathAppend(accountPath,documentPath);
    _mkdir(documentPath);
    pathAppend(accountPath,"account");
    _mkdir(accountPath);
    printf("documentPath=%s\n",documentPath);
    //printf("documentPath=%s\n",documentPath);
    //printf("accountPath=%s\n",accountPath);
}
void closeFile(FILE* file){
    fclose(file);
}