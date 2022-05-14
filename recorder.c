#include"recorder.h"
#include"fileIO.h"
#include"tree.h"
#include"debug.h"
#include"word.h"
#include<string.h>

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
LinkedList* getSpendList(const char* accountName, int year, int month){
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
        if(isDebugMode())printf("string=%s\n",string);
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
        strncpy(note,split,15);

        Spend* spend = newSpend(cost,category,*newDate(year,month,day),note);
        tree_add(tree,spend);
    }
    LinkedList* list = tree_toList(tree);
    closeFile(file);
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
    LinkedList* list = getSpendList(accountName,year,month);
    Date* date = newDate(year,month,day);
    Spend* spend = newSpend(cost,category,*date,note);
    if(isDebugMode())printf("list.len=%d\n",linkedList_lengeth(list));
    boolean success = linkedList_removeValue(list, spend);//比對相同的VALUE 所以要用newSpend
    if(isDebugMode())printf("list.len=%d\n",linkedList_lengeth(list));
    
    if(success == False){
        printf("Can not fine record.\n");
    }
    free(date);
    free(spend);

    clearFileBuffer();
    FILE* file = getSpendFile(year,month,accountName,coverMode);
    fileBuffer[0] = file;
    linkedList_traverse(list,traverse_coverSpend);
    closeFile(file);
    printf("Delete successful.\n");
    system("pause");

}