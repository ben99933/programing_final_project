#include <stdio.h>
#include <stdlib.h>
#include "spendList.h"
#include"spend.h"

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
            else if (compCost(key->spend, curr->spend) >= 0){
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

void printLL(struct LLNode *head){
    struct LLNode *curr = head;
    printf("Sorted Linked List:\n");
    printf("Date\tCategory\tCost\n");
    for (int i = 0;curr != NULL; curr = curr->next, i++){
        short int year = curr->spend.date.year;
        short int month = curr->spend.date.month;
        short int day = curr->spend.date.day;
        int category = (int) curr->spend.category;
        int cost = curr->spend.cost;
        printf("[%d] %hi/%hi/%hi\t%d\t%d\n", i, year, month, day, category, cost);
    }
}

void deleteData(struct LLNode *list){
    //print the sortedList
    printLL(list);
    printf("Which data would you like to delete? (Type number in [])\n");
    int index;
    scanf("%d",&index);

    struct LLNode *prev = list;
    struct LLNode *key = list;

    for (int i = 0 ; i < index ; i++){
        key = key->next;
        if(i != index-1)
            prev = prev->next;
    }
    printf("[%d] is deleted\n", index);
    prev->next = key->next;
    key->next->prev = prev;
    free(key);

    printLL(list);
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

void printOccurence(Occurence *occurenceList,int size){
    printf("Occurence List\n");
    printf("Date\tCount\tInitPos\n");

    for (int i = 0; i< size ; i++){
        if(occurenceList[i].Count <= 0) //There's no such date in the linked list.
            continue;
        else
            printf("%d\t%d\t%d\n", i + 1, occurenceList[i].Count, occurenceList[i].initPos);
    }
}

int findOccurTail(Occurence *occurenceList){
    int tailIndex = DAY_OF_MONTH;
    while (occurenceList[tailIndex - 1].Count == 0)
        tailIndex--;
    tailIndex = occurenceList[tailIndex - 1].initPos + occurenceList[tailIndex - 1].Count - 1;
    return tailIndex;
}

keyDataList *getKeyData(struct LLNode *sortedList,Occurence *occurenceList, Category keyCategory, const short dayBegin, const short dayEnd){
    //illegal input handling.
    if((int)keyCategory < -1 ||(int)keyCategory > 5 || dayBegin > dayEnd || dayBegin < 0 || dayBegin < 0
       ||(dayBegin < 1 && keyCategory == -1) || (dayEnd < 0 && keyCategory == -1)
       ||dayBegin > 31 ||dayEnd > 31||(dayBegin==0 && dayEnd != 0) || (dayBegin!= 0 && dayEnd == 0)
       ||((int)keyCategory == -1 && (dayBegin == 0 || dayEnd == 0))){
        printf("Invalid Input, please check your input!\n");
        return NULL;
    }
    
    //keyCategory Only
    if (keyCategory != -1 && dayBegin == 0){
        struct LLNode *curr = sortedList;

        Spend *dataList = calloc(EXTRACT_UPPER_LIMIT, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->dayBegin = keyList->dayBegin = 0; //day interval not specified.
        keyList->keyCategory = (short int) keyCategory;
        keyList->extractionType = 0;

        for (int i = 0 ; curr!=NULL, i < EXTRACT_UPPER_LIMIT ; curr = curr->next){
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
        keyList->listLength = i;

        return keyList;
    }
    //Day Interval Only
    else if ((int)keyCategory == -1 && dayBegin != 0){
        struct LLNode *curr = sortedList;

        int startPos = occurenceList[dayBegin - 1].initPos;
        int endPos = occurenceList[dayEnd - 1].initPos + occurenceList[dayEnd - 1].Count;
        if((endPos == startPos) && (dayBegin != dayEnd))
            endPos = findOccurTail(occurenceList);
        int dataLength = endPos - startPos;

        Spend *dataList = calloc(dataLength, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->keyCategory = -1; //Category not specified.
        keyList->dayBegin = dayBegin;
        keyList->dayEnd = dayEnd;
        keyList->listLength = (short) dataLength;
        keyList->extractionType = 1;

        for (int i = 0 ; i < startPos       ; i++, curr = curr->next);
        for (int j = 0 ; j < dataLength     ; j++, curr = curr->next)
            dataList[j] = curr->spend;

        return keyList;
    }
    // BOTH Day Interval and keyCategory.
    else if ((int)keyCategory != -1 && dayBegin != 0){
        struct LLNode *curr = sortedList;
        
        int startPos = occurenceList[dayBegin - 1].initPos;
        int endPos = occurenceList[dayEnd - 1].initPos + occurenceList[dayEnd - 1].Count;
        if((endPos == startPos) && (dayBegin != dayEnd))
            endPos = findOccurTail(occurenceList);
        int dataLength = endPos - startPos;

        Spend *dataList = calloc(dataLength, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->keyCategory = (short) keyCategory;
        keyList->dayBegin = dayBegin;
        keyList->dayEnd = dayEnd;
        
        keyList->extractionType = 2;

        for (int i = 0       ; i < startPos  ; i++, curr = curr->next);
        for (int j = 0,k = 0 ; j < dataLength; j++, curr = curr->next){
            if( curr->spend.category == keyCategory)
                dataList[k++] = curr->spend;
        }
        //Computing actual number of data in the keyList.
        int i = 0;
        while(dataList[i].date.day != 0)
            i++;
        keyList->listLength = (short) i;

        return keyList;
    }
}

void printKeyList(keyDataList *keyList){
    if(keyList->extractionType == 0){
        printf("List of expenses with Category %hi",keyList->keyCategory);
        printf("The list is ordered in date.(ascending)\n");
        printf("Date\tCategory\tCost\n");
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = keyList->keyCategory;
            int cost = keyList->dataList[i].cost;
            printf("%hi/%hi/%hi\t%hi\t%d\n", year, month, day, category, cost);
        }
    }
    else if (keyList->extractionType == 1){
        short yearBegin = keyList->dataList[0].date.year;
        short monthBegin = keyList->dataList[0].date.month;
        short dayBegin = keyList->dataList[0].date.day;
        short yearEnd  = keyList->dataList[keyList->listLength - 1].date.year;
        short monthEnd = keyList->dataList[keyList->listLength - 1].date.month;
        short dayEnd   = keyList->dayEnd;

        printf("List of expenses from date %hi/%hi/%hi to %hi/%hi/%hi\n"
                , yearBegin, monthBegin, dayBegin, yearEnd, monthEnd, dayEnd);
        printf("The list is ordered in date.(ascending)\n");
        printf("Date\tCategory\tCost\n");
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = (short)keyList->dataList->category;
            int cost = keyList->dataList[i].cost;
            printf("%hi/%hi/%hi\t%hi\t%d\n", year, month, day, category, cost);
        }
    }
    else{
        short yearBegin = keyList->dataList[0].date.year;
        short monthBegin = keyList->dataList[0].date.month;
        short dayBegin = keyList->dataList[0].date.day;
        short yearEnd  = keyList->dataList[keyList->listLength - 1].date.year;
        short monthEnd = keyList->dataList[keyList->listLength - 1].date.month;
        short dayEnd   = keyList->dayEnd;

        printf("List of expenses with category %hi and from date %hi/%hi/%hi to %hi/%hi/%hi\n"
                ,keyList->keyCategory, yearBegin, monthBegin, dayBegin, yearEnd, monthEnd, dayEnd);
        printf("The list is ordered in date.(ascending)\n");
        printf("Date\tCategory\tCost\n");
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = (short)keyList->dataList->category;
            int cost = keyList->dataList[i].cost;
            printf("%hi/%hi/%hi\t%hi\t%d\n", year, month, day, category, cost);
        }
    }
}