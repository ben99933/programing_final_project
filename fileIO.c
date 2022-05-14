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

/**
 * file的暫存器 
 * 因為有一些funcion不能直接取得那一個FILE*
 * 所以事先把那個FILE*放到暫存器
 * 因為他是全域的 所以那些function可以使用
 * 注意 : 小心使用 不要用錯index
 */
FILE* fileBuffer[16] = {NULL};

CHAR documentPath[MAX_PATH];// 文件/finalProject
CHAR accountPath[MAX_PATH];// 文件/finalProject/account
CHAR recordPath[MAX_PATH];// 文件/finalProject/record

// path = path + "\\" + destination
static void pathAppend(char* path,const char* destination){
    if(path[0]=='\0'){
        strcpy(path,destination);
        return;
    }
    strcat(path,"\\");
    strcat(path,destination);
}
/**
 * path = path + name + "." + format
 * 注意format不要加 "."
 */
static void pathAppendFile(char* path,const char* name,const char* format){
    strcat(path,"\\");
    strcat(path,name);
    strcat(path,".");
    strcat(path,format);
}

//取得路徑
char* getDocumentPath(){
    return documentPath;
}
char* getAccountPath(){
    return accountPath;
}
char* getRecordPath(){
    return recordPath;
}


 //檢測該檔案是否存在
static int fileExist(const char* path){
    /**
     * _access的第二個參數為access mode
     * 0為檢測該路徑之檔案是否存在
     * access return 0 表示存在或擁有許可權 -1表示不存在或無許可權
     */
    int acc = _access(path,0);
    //printf("access(path,0)=%d\n",acc);
    if(acc == 0) return True;
    else return False;
}
//讀取檔案 要自己關閉 可以呼叫closeFile(file);
static FILE* readFile(const char* path){
    //printf("read file, path=%s\n",path);
    FILE* file = fopen(path,"r");
    return file;
}
/**
 * 寫入檔案(如果該路徑不存在則建立檔案)
 * 回傳的檔案要自己關閉 可以呼叫closeFile(file);
 */
static FILE* createFile(const char* path){
    //printf("write file, path=%s\n",path);
    FILE* file = fopen(path,"w");
    return file;
}

//回傳 "文件/finalProject/account/<使用者名稱>.txt
FILE* findAccountFile(const char* accountName){
    char path[1024] = {'\0'};

    pathAppend(path,accountPath);
    pathAppendFile(path,accountName,"txt");
    FILE* file = readFile(path);
    
    return file;
}
//創建用於存放該使用者之密碼的檔案
FILE* creatAccountFile(const char* accountName){
    char path[1024] = {'\0'};
    char record[1024]={'\0'};

    pathAppend(record,recordPath);
    pathAppend(record,accountName);
    _mkdir(record);

    pathAppend(path,accountPath);
    pathAppendFile(path,accountName,"txt");
    FILE* file = createFile(path);
    return file;
}

/** 
 * 找到該玩家某月的消費紀錄
 * 路徑 : 文件/finalProject/record/<user>/<date>.csv
 * 檔案要自己關閉
 */
FILE* findSpendFile(const char* accountName,Date* date){
    char path[MAX_PATH] = {'\0'};
    char filename[9] = {'\0'};
    _itoa((date->year*100+date->month), filename, 10);
    pathAppend(path,recordPath);
    pathAppend(path,accountName);
    pathAppendFile(path,filename,"csv");
    FILE* file = readFile(path);
    return file;
}

/** 
 * 創建該玩家在某月的紀錄檔 csv
 * 路徑 : 文件/finalProject/record/<user>/<date>.csv
 * 檔案要自己關閉
 */
FILE* creatdSpendFile(const char* accountName,Date* date){
    char path[MAX_PATH] = {'\0'};
    char filename[9] = {'\0'};
    _itoa((date->year*100+date->month), filename, 10);
    pathAppend(path,recordPath);
    pathAppend(path,accountName);
    pathAppendFile(path,filename,"csv");
    FILE* file = createFile(path);
    return file;
}
/** 
 * 找到該玩家在某月的紀錄檔 csv
 * 路徑 : 文件/finalProject/record/<user>/<date>.csv
 * 檔案要自己關閉
 */
FILE* getSpendFile(int year,int month,const char* accountName,OpenMode mode){
    char path[1024] = {'\0'};
    char name[9];
    _itoa((year*100+month),name,10);
    pathAppend(path,getRecordPath());
    pathAppend(path,accountName);
    pathAppendFile(path,name,"csv");
    //如果這個csv不存在 創建他並且在recorder.txt中記錄該月份
    if(fileExist(path) == False){
        FILE* recorder = findRecorderFile(accountName);
        fprintf(recorder,"%d\n",(year*100+month));
        closeFile(recorder);
    }
    FILE* file = NULL;
    if(mode == readMode || mode == appendMode)file = fopen(path,"a+");//append 不會覆蓋掉
    else if(mode == coverMode)file = fopen(path,"w+");//覆蓋
    if(file == NULL)return NULL;
    return file;
}

/**
 * 找到該玩家的recorder.txt
 * 路徑 : 文件/finalProject/record/<user>/record.txt
 * 檔案要自己關閉
 */
FILE* findRecorderFile(const char* accountName){
    char path[1024] = {'\0'};
    pathAppend(path,recordPath);
    pathAppend(path,accountName);
    pathAppendFile(path,"recorder", "txt");
    FILE* file = fopen(path,"a+");
    return file;
}

/**
 * 創建該玩家的recorder.txt
 * 路徑 : 文件/finalProject/record/<user>/record.txt
 * 檔案要自己關閉
 */
FILE* createRecorderFile(const char* accountName){
    char path[1024] = {'\0'};
    pathAppend(path,recordPath);
    pathAppend(path,accountName);
    pathAppendFile(path,"recorder","txt");
    FILE* file = fopen(path,"a+");//append
    return file;
}

//關閉檔案
void closeFile(FILE* file){
    fclose(file);
}

//清除暫存器
void clearFileBuffer(){
    for(int i = 0;i<15;i++){
        fileBuffer[i] = NULL;
    }
}
/**
 * main.c的初始化會自動呼叫 不要在其他地方呼叫這個funcion
 * 設定路徑
 * 創一些資料夾
 */
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
