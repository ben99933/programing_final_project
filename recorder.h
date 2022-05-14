#include"spend.h"
#include<stdlib.h>
#include<stdio.h>
#include"tree.h"

#ifndef RECORDER_H
    #define RECORDER_H

    //一個月的SPEND
    Spend spendBuffer[31][30];//第I天的第J筆消費

    void recordSpend(int year,int month, int day, int category, int cost, char remark[16], const char* accountName);
    Tree* getAllRecordName(const char* accountName);
    LinkedList* getSpendList(const char* accountName, int year, int month);
#endif

