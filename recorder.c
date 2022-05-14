#include"recorder.h"
#include"fileIO.h"
#include"tree.h"
#include"debug.h"
#include"word.h"
#include<string.h>

void recordSpend(int year,int month, int day, int category, int cost, char note[16], const char* accountName){
    FILE* file = getSpendFile(year,month,accountName);
    fprintf(file,"%d,%d,%d,%d,%d,%s\n",year,month,day,category,cost,note);
    closeFile(file);
}
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
    FILE* file = getSpendFile(year,month,accountName);
    if(file == NULL){
        errorMsg("file not found.",__FILE__,__LINE__);
        return NULL;
    }
    Tree* tree = newBinarySearchTree(SpendType);
    while(!feof(file)){
        char string[1024];
        fgets(string,1024,file);
        trimString(string);
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

        Spend* spend = newSpend(cost,category,newDate(year,month,day),note);
        tree_add(tree,spend);
    }
    LinkedList* list = tree_toList(tree);
    closeFile(file);
    return list;
    
}