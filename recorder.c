#include"recorder.h"
#include"fileIO.h"
#include"tree.h"
#include"debug.h"
#include"word.h"
#include<string.h>
#include"spendList.h"
#include"linkedList.h"

/**
 * 先使用fileIO.c的getSpendFile得到存放該月份消費的檔案
 * 然後用fprintf
 */
void recordSpend(int year,int month, int day, int category, int cost, char note[16], const char* accountName){
    FILE* file = getSpendFile(year,month,accountName,appendMode);
    fprintf(file,"%d,%d,%d,%d,%d,%s\n",year,month,day,category,cost,note);
    closeFile(file);
}


/**
 * 取得recorder.txt的內容(路徑為"文件/finalProject/record/<玩家名>/recorder.txt")
 * recorder.txt紀錄這個帳號總共目前有哪些月份可以查看
 */
Tree* getAllRecordName(const char* accountName){
    FILE* recorder = findRecorderFile(accountName);
    Tree* tree = newBinarySearchTree(Int);
    while(!feof(recorder)){
        int num = 0;
        fscanf(recorder, "%d",&num);
        tree_add(tree, newInt(num));
    }
    closeFile(recorder);
    return tree;
}

Tree* getgetSpendRecordTree(const char* accountName,int year, int month){
    FILE* file = getSpendFile(year,month,accountName,appendMode);
    if(file == NULL){
        errorMsg("file not found.",__FILE__,__LINE__);
        return NULL;
    }
    Tree* tree = newBinarySearchTree(SpendType);
    while(!feof(file)){
        char string[1024] = {'\0'};
        fgets(string,1024,file);
        if(strcmp(string,"\n") == 0 || strcmp(string,"\0") == 0)continue;;
        trimString(string);
        if(isDebugMode())printf("string=%s",string);
        debugMsg("",__FILE__,__LINE__);
        //spend
        int year;
        int month;
        int day;
        Category category;
        int cost;
        char note[16];
        char* split = strtok(string,",");
        if(isNumberString(split))year = toIntValue(split);
        split = strtok(NULL,",");
        if(isNumberString(split))month = toIntValue(split);
        split = strtok(NULL,",");
        if(isNumberString(split))day = toIntValue(split);
        split = strtok(NULL,",");
        if(isNumberString(split))category = toCategory(toIntValue(split));
        split = strtok(NULL,",");
        if(isNumberString(split))cost = toIntValue(split);
        split = strtok(NULL,",");
        trimString(split);
        strncpy(note,split,15);
        
        Date date = {.year = year,.month = month,.day = day};
        tree_add(tree,newSpend(cost,category,date,note));
    }
    closeFile(file);
    debugMsg("tree construted.",__FILE__,__LINE__);
    return tree;
}

LLNode* getSpendList(const char* accountName, int year, int month){
    Tree* tree = getgetSpendRecordTree(accountName, year, month);
    LLNode* list = tree_toSpendList(tree);
    tree_destory(tree);
    return list;
}

//LIST做尋訪的時候要用到的
static void traverse_coverSpend(DataType type,void* value){
    if(type != SpendType){
        errorMsg("is not spendType.",__FILE__,__LINE__);
        return;
    }
    FILE* file = fileBuffer[0];
    
    Spend* spend = (Spend*)value;
    Date* date = &spend->date;
    fprintf(file,"%d,%d,%d,%d,%d,%s\n",date->year,date->month,date->day,spend->category,spend->cost,spend->note);
}

void removeSpend(int year,int month, int day, int category, int cost, char note[16], const char* accountName){
    LLNode* listHead = getSpendList(accountName,year,month);
    Occurence *occurList = findOccurence(listHead);
    Date date = {.year = year, .month = month, .day = day};
    Spend* spend = newSpend(cost, category, date, note);
    boolean success;
    listHead = LLNode_removeNode(listHead, *spend, &success);
    
    if(success == False){
        printf("Can not fine record.\n");
    }
    

    clearFileBuffer();
    FILE* file = getSpendFile(year,month,accountName,coverMode);
    fileBuffer[0] = file;
    
    closeFile(file);
    printf("Delete successful.\n");
    destorySpendList(listHead);
    system("pause");

}