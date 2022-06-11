#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spendList.h"
#include "debug.h"
#include "color.h"

struct LLNode *createList(Spend data){
    struct LLNode *head = malloc(sizeof(struct LLNode));
    head->spend = data;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

//Linked list sorting compare algorithm for date.
int compDate(Spend tempData, Spend nodeData){
    if (tempData.date.day < nodeData.date.day)
        return -1;
    else if (tempData.date.day > nodeData.date.day)
        return 1;
    else
        return 0;
}
//Linked list sorting compare algorithm for Category.
int compCategory(Spend tempData, Spend nodeData){
    if (tempData.category < nodeData.category)
        return -1;
    else if (tempData.category > nodeData.category)
        return 1;
    else
        return 0;
}
//Linked list sorting compare algorithm for Cost.
int compCost(Spend tempData, Spend nodeData){
    if (tempData.cost < nodeData.cost)
        return -1;
    else if (tempData.cost > nodeData.cost)
        return 1;
    else
        return 0;
}

int compNote(Spend tempData, Spend nodeData){
    if (strcmp(tempData.note, nodeData.note) > 0)
        return 1;
    else if (strcmp(tempData.note, nodeData.note) == 0)
        return 0;
    else
        return -1;
}

//Insert new node 
void sortedInsert(struct LLNode *curr,struct LLNode *prev, struct LLNode *key, int listSize){
    //Base Case 1:
    if(curr == NULL){
        curr = key;
        curr->prev = prev;
        prev->next = curr;
        return;
    }
    //Base Case 2:
    if(compDate(key->spend, curr->spend) == -1){
        if (prev == NULL){ //meaning curr is the first element
            key->next =curr;
            curr->prev = key;
            curr = key;
            return;
        }
        else{
            curr->prev = key;
            key->next = curr;
            key->prev = prev;
            prev->next = key;
            return;
        }
    }
    else if (compDate(key->spend, curr->spend) == 0){
        if(compCategory(key->spend, curr->spend) == -1){
            if (prev == NULL){ //meaning curr is the first element
                key->next =curr;
                curr->prev = key;
                curr = key;
                return;
            }
            else{
                curr->prev = key;
                key->next = curr;
                key->prev = prev;
                prev->next = key;
                return;
            }
        }
        else if (compCategory(key->spend, curr->spend) == 0){
            if(compCost(key->spend, curr->spend) == -1){
                if (prev == NULL){ //meaning curr is the first element
                    key->next =curr;
                    curr->prev = key;
                    curr = key;
                    return;
                }
                else{
                    curr->prev = key;
                    key->next = curr;
                    key->prev = prev;
                    prev->next = key;
                    return;
                }
            }
            else if (compCost(key->spend, curr->spend) == 0){
                if(compNote(key->spend, curr->spend) == -1){
                    if (prev == NULL){ //meaning curr is the first element
                    key->next =curr;
                    curr->prev = key;
                    curr = key;
                    return;
                    }
                    else{
                        curr->prev = key;
                        key->next = curr;
                        key->prev = prev;
                        prev->next = key;
                        return;
                    }
                }
                else if (compNote(key->spend, curr->spend) >= 0){
                    prev = curr;
                    curr = curr->next;
                    sortedInsert(curr, prev, key, listSize);
                }
            }
            else{
                prev = curr;
                curr = curr->next;
                sortedInsert(curr, prev, key, listSize);
            }
        }
        else{
            prev = curr;
            curr = curr->next;
            sortedInsert(curr, prev, key, listSize);
        }
    }
    else{
        prev = curr;
        curr = curr->next;
        sortedInsert(curr, prev, key, listSize);
    }
}

int compSpend(Spend key, Spend target){
    if((key.category == target.category) && (key.cost == target.cost) && (key.date.day == target.date.day)
     &&(key.date.month == target.date.month) && (key.date.year == target.date.year))
        return 1;
    else
        return 0;
}

struct LLNode *deleteNode(struct LLNode *list, Spend keyData){
    struct LLNode *prev = list;
    struct LLNode *key = list;

    for (;key!=NULL; prev = key, key = key->next){
        if(compSpend(key->spend, keyData) == 1)
            break;
    }

    if(key == NULL){
        printf("No such node, please retry.\n");
        return list;
    }
    else{
        if(key == prev){                //key is the first element in the list.
            prev = prev->next;
            free(key);
            return prev;
        }
        else if (key->next == NULL){    //key is the last element in the list.
            prev->next = NULL;
            free(key);
            return list;
        }
        else{
            prev->next = key->next;
            key->next->prev = prev;
            free(key);
            return list;
        }
    }
}

int isSameDate(Date date1, Date date2){
    if((date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day))
        return 1;
    else
        return 0;
}

Occurence *findOccurence(struct LLNode *sortedList){
    struct LLNode *curr = sortedList;
    Occurence *occurList = calloc(DAY_OF_MONTH, sizeof(Occurence));
    
    for (int pos = 0;curr != NULL;)
    {
        Date tempDate = curr->spend.date;
        int currDate = ((int) tempDate.day) - 1; // -1 to match index (which starts from 0)
        occurList[currDate].Count = 1;
        occurList[currDate].initPos = pos;

        curr = curr->next;
        while (curr != NULL){
            if(isSameDate(tempDate, curr->spend.date)== 1){
                occurList[currDate].Count++;
                pos++;
                curr = curr->next;
            }
            else{
                pos++;
                break;
            }
        }
    }
    return occurList;
}

int findOccurTail(Occurence *occurenceList, int dayEnd){
    int actualdayEnd = dayEnd;
    while (occurenceList[actualdayEnd - 1].Count == 0)
        actualdayEnd--;
    actualdayEnd = occurenceList[actualdayEnd - 1].initPos + occurenceList[actualdayEnd - 1].Count;
    return actualdayEnd;
}

keyDataList *getKeyData(struct LLNode *sortedList,Occurence *occurenceList, Category keyCategory, short dayBegin, short dayEnd){
    //illegal input handling.
    if((int)keyCategory < -1 ||(int)keyCategory > 6 || dayBegin > dayEnd || dayBegin < 0 || dayBegin < 0
       ||((keyCategory == -1 && dayBegin < 1) && (keyCategory == -1 && dayBegin != 0)) 
       ||((keyCategory == -1 && dayEnd < 1 ) && (keyCategory == -1 && dayEnd != 0))
       ||dayBegin > 31 ||dayEnd > 31||(dayBegin==0 && dayEnd != 0) || (dayBegin!= 0 && dayEnd == 0)){
        setTextColor(ColorRed);
        printf("Invalid Input, please check your input!\n");
        system("pause");
        resetTextColor();
        return NULL;
    }
    
    //keyCategory Only
    if (keyCategory != -1 && dayBegin == 0){
        struct LLNode *curr = sortedList;

        Spend *dataList = calloc(EXTRACT_UPPER_LIMIT, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->dayBegin = keyList->dayEnd = 0; //day interval not specified.
        keyList->keyCategory = (short int) keyCategory;
        keyList->extractionType = 0;

        for (int i = 0 ; curr !=NULL, i < EXTRACT_UPPER_LIMIT ; curr = curr->next){
            if (curr == NULL)
                break;
            if (curr->spend.category == keyCategory){
                dataList[i] = curr->spend;
                i++;
            }
        }
        //Computing actual number of data in the keyList.
        int i = 0;
        while(dataList[i].date.day != 0)
            i++;

        if(i == 0){
            setTextColor(ColorYellow);
            printf("No such data in designated range. Please retry.\n");
            system("pause");
            resetTextColor();
            return NULL;
        }
        else{
            keyList->listLength = i;
            return keyList;
        }
    }
    //Day Interval Only
    else if ((int)keyCategory == -1 && dayBegin != 0){
        int actualDayBegin = dayBegin;
        while (actualDayBegin <= dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
            if(actualDayBegin == dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
                setTextColor(ColorYellow);
                printf("No such data in designated range. Please retry.\n");
                system("pause");
                resetTextColor();
                return NULL;
            }
            else{
                while (occurenceList[actualDayBegin - 1].Count == 0){
                    if(actualDayBegin == dayEnd){ // if dayBegin ==dayEnd and Count is still zero.
                        setTextColor(ColorYellow);
                        printf("No such data in designated range. Please retry.\n");
                        system("pause");
                        resetTextColor();
                        return NULL;
                    }
                    actualDayBegin++;
                }
            }
        }
            
        int startPos = occurenceList[actualDayBegin - 1].initPos;
        int endPos = occurenceList[dayEnd - 1].initPos + occurenceList[dayEnd - 1].Count;
        if((endPos <= startPos) && (dayBegin != dayEnd)){
            endPos = findOccurTail(occurenceList, dayEnd);
        }
        int dataLength = endPos - startPos;
        
        if(dataLength == 0){
            setTextColor(ColorYellow);
            printf("No such data in designated range. Please retry.\n");
            system("pause");
            resetTextColor();
            return NULL;
        }
        
        Spend *dataList = calloc(dataLength, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->keyCategory = -1; //Category not specified.
        keyList->dayBegin = dayBegin;
        keyList->dayEnd = dayEnd;
        keyList->listLength = (short) dataLength;
        keyList->extractionType = 1;

        struct LLNode *curr = sortedList;
        for (int i = 0 ; i < startPos   ; i++, curr = curr->next);
        for (int j = 0 ; j < dataLength ; j++, curr = curr->next)
            dataList[j] = curr->spend;

        return keyList;
    }
    // DEFAULT CASE:
    else if((int)keyCategory == -1 && dayBegin == 0 && dayEnd == 0){
        dayBegin = 1;
        dayEnd = 31;
        int actualDayBegin = dayBegin;
        while (actualDayBegin <= dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
            if(actualDayBegin == dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
                setTextColor(ColorYellow);
                printf("No such data in designated range. Please retry.\n");
                system("pause");
                resetTextColor();
                return NULL;
            }
            else{
                while (occurenceList[actualDayBegin - 1].Count == 0){
                    if(actualDayBegin == dayEnd){ // if dayBegin == dayEnd and Count is still zero.
                        setTextColor(ColorYellow);
                        printf("No such data in designated range. Please retry.\n");
                        system("pause");
                        resetTextColor();
                        return NULL;
                    }
                    actualDayBegin++;
                }
            }
        }
            
        int startPos = occurenceList[dayBegin - 1].initPos;
        int endPos = occurenceList[dayEnd - 1].initPos + occurenceList[dayEnd - 1].Count;
        if((endPos <= startPos) && (dayBegin != dayEnd))
            endPos = findOccurTail(occurenceList, dayEnd);
        int dataLength = endPos - startPos;
        
        if(dataLength == 0){
            setTextColor(ColorYellow);
            printf("No such data in designated range. Please retry.\n");
            system("pause");
            resetTextColor();
            return NULL;
        }
        Spend *dataList = calloc(dataLength, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->keyCategory = -1; //Category not specified.
        keyList->dayBegin = dayBegin;
        keyList->dayEnd = dayEnd;
        keyList->listLength = (short) dataLength;
        keyList->extractionType = 1;
       
        struct LLNode *curr = sortedList;
        for (int i = 0 ; i < startPos   ; i++, curr = curr->next);
        for (int j = 0 ; j < dataLength ; j++, curr = curr->next)
            dataList[j] = curr->spend;

        return keyList;
    }
}

void printKeyList(keyDataList *keyList){
    if(keyList->extractionType == 0){
        printf(ColorGreen"\n=====================LIST OF EXPENSES WITH CATEGORY %hi==========================\n"ColorReset,keyList->keyCategory);
        printf(underscore"       DATE        |     CATEGORY      |       COST        |       NOTE        \n"underscoreReset);
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = (short)keyList->dataList[i].category;
            int cost = keyList->dataList[i].cost;
            char note[16];
            strcpy(note,keyList->dataList[i].note);
            printf("    %04hi/%02hi/%02hi     |  %-17s|%12d       |       %s\n", year, month, day, toCategoryString(category), cost, note);
        }
        printf(ColorGreen"===============================================================================\n"ColorReset);
    }
else if (keyList->extractionType == 1){
        short yearBegin = keyList->dataList[0].date.year;
        short monthBegin = keyList->dataList[0].date.month;
        short dayBegin = keyList->dayBegin;
        short yearEnd  = keyList->dataList[keyList->listLength - 1].date.year;
        short monthEnd = keyList->dataList[keyList->listLength - 1].date.month;
        short dayEnd   = keyList->dayEnd;

        printf(ColorGreen"\n==============LIST OF EXPENSES FROM DATE %04hi/%02hi/%02hi TO %04hi/%02hi/%02hi==============\n"ColorReset
                , yearBegin, monthBegin, dayBegin, yearEnd, monthEnd, dayEnd);
        printf(underscore"       DATE        |     CATEGORY      |       COST        |       NOTE        \n"underscoreReset);
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = (short)keyList->dataList[i].category;
            int cost = keyList->dataList[i].cost;
            char note[16];
            strcpy(note,keyList->dataList[i].note);
            printf("    %04hi/%02hi/%02hi     |  %-17s|%12d       |       %s\n", year, month, day, toCategoryString(category), cost, note);
        }
        printf(ColorGreen"===============================================================================\n"ColorReset);
    }
else{
        short yearBegin = keyList->dataList[0].date.year;
        short monthBegin = keyList->dataList[0].date.month;
        short dayBegin = keyList->dayBegin;
        short yearEnd  = keyList->dataList[keyList->listLength - 1].date.year;
        short monthEnd = keyList->dataList[keyList->listLength - 1].date.month;
        short dayEnd   = keyList->dayEnd;

        printf(ColorGreen"\n==============LIST OF EXPENSES WITH CATEGORY %s AND FROM DATE %04hi/%02hi/%02hi TO %04hi/%02hi/%02hi==============\n"ColorReset
                ,toCategoryString(keyList->keyCategory), yearBegin, monthBegin, dayBegin, yearEnd, monthEnd, dayEnd);
        printf(underscore"       DATE        |     CATEGORY      |       COST        |       NOTE        \n"underscoreReset);
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = (short)keyList->dataList[i].category;
            int cost = keyList->dataList[i].cost;
            char note[16];
            strcpy(note,keyList->dataList[i].note);
            printf("    %04hi/%02hi/%02hi     |  %-17s|%12d       |       %s\n", year, month, day, toCategoryString(category), cost, note);
        }
        printf(ColorGreen"===============================================================================\n"ColorReset);
    }
}
/**
 * 把list釋放掉
 */
void destorySpendList(LLNode* head){
    if(head == NULL)return;
    if(head->next != NULL)destorySpendList(head->next);
    free(head);
}