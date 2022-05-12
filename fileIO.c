#include"fileIO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <shlobj.h>
#include <windows.h>
#include <direct.h>
#include<io.h>

#define True 1
#define False 0

CHAR documentPath[MAX_PATH];
CHAR accountPath[MAX_PATH];
CHAR recordPath[MAX_PATH];

static void pathAppend(char* path,const char* destination){
    if(path[0]=='\0'){
        strcpy(path,destination);
        return;
    }
    strcat(path,"\\");
    strcat(path,destination);
}
char* getDocumentPath(){
    return documentPath;
}
char* getAccountPath(){
    return accountPath;
}
char* getRecordPath(){
    return recordPath;
}

static int fileExist(const char* path){
    /**
     * _access的第二個參數為access mode
     * 0為檢測該路徑之檔案是否存在
     * access return 0 表示存在或擁有許可權 -1表示不存在或無許可權
     */
    if(_access(path,0) == 0) return True;
    else return False;
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
    char path[1024] = {'\0'};

    pathAppend(path,accountPath);
    pathAppend(path,accountName);
    strcat(path,".txt");
    FILE* file = readFile(path);
    
    return file;
}
FILE* creatAccountFile(const char* accountName){
    char path[1024] = {'\0'};
    char record[1024]={'\0'};
    pathAppend(path,accountPath);
    pathAppend(path,accountName);
    strcat(path,".txt");

    pathAppend(record,recordPath);
    pathAppend(record,accountName);
    _mkdir(record);

    FILE* file = createFile(path);
    return file;
}
FILE* findSpendFile(const char* accountName,Date* date){
    char path[MAX_PATH] = {'\0'};
    char filename[9] = {'\0'};
    _itoa((date->year*100+date->month), filename, 9);
    pathAppend(path,recordPath);
    pathAppend(path,accountName);
    pathAppend(path,filename);
    strcat(path,".csv");
    FILE* file = fopen(path,"r");
    return file;
}
FILE* creatdSpendFile(const char* accountName,Date* date){
    char path[MAX_PATH] = {'\0'};
    char filename[9] = {'\0'};
    _itoa((date->year*100+date->month), filename, 9);
    pathAppend(path,recordPath);
    pathAppend(path,accountName);
    pathAppend(path,filename);
    strncat(path,".csv",5);
    FILE* file = fopen(path,"a");
    return file;
}


void fileIO_init(){
    documentPath[0] = '\0';
    accountPath[0] = '\0';
    recordPath[0] = '\0';
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, documentPath);
    
    pathAppend(documentPath,"finalProject");
    pathAppend(accountPath,documentPath);
    pathAppend(recordPath,documentPath);
    _mkdir(documentPath);
    _mkdir(accountPath);
    _mkdir(recordPath);

    pathAppend(accountPath,"account");
    pathAppend(recordPath,"record");
    _mkdir(accountPath);
    _mkdir(recordPath);

    //mkdir是創建資料夾 mkdir只能一層一層創
}
void closeFile(FILE* file){
    fclose(file);
}