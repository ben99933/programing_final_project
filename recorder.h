#include"spend.h"
#include<stdlib.h>
#include<stdio.h>
#include"tree.h"

/**
 * 這裡主要存放一些跟fileIO.c做溝通的funciton
 * 特別是要存取或修改Spend的file的時候
 * 
 */

#ifndef RECORDER_H
    #define RECORDER_H

    void recordSpend(int year,int month, int day, int category, int cost, char remark[16], const char* accountName);
    void removeSpend(int year,int month, int day, int category, int cost, char remark[16], const char* accountName);
    Tree* getAllRecordName(const char* accountName);
    LLNode* getSpendList(const char* accountName, int year, int month);
#endif

