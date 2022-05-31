#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spendList.h"
#include "debug.h"

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

void printLL(struct LLNode *head){
    struct LLNode *curr = head;
    printf("Sorted Linked List:\n");
    printf("Date\tCategory\tCost\tNote\n");
    for (int i = 0;curr != NULL; curr = curr->next, i++){
        short int year = curr->spend.date.year;
        short int month = curr->spend.date.month;
        short int day = curr->spend.date.day;
        int category = (int) curr->spend.category;
        int cost = curr->spend.cost;
        char note[16];
        strcpy(note, curr->spend.note);
        printf("[%d] %hi/%hi/%hi\t%d\t%d\t%s\n", i, year, month, day, category, cost, note);
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
       ||((keyCategory == -1 && dayEnd < 1 )) && (keyCategory == -1 && dayEnd != 0)
       ||dayBegin > 31 ||dayEnd > 31||(dayBegin==0 && dayEnd != 0) || (dayBegin!= 0 && dayEnd == 0)){
        printf("Invalid Input, please check your input!\n");
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
            printf("No such data in designated range. Please retry.\n");
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
        while (dayBegin <= dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
            if(dayBegin == dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
                printf("No such data in designated range. Please retry.\n");
                return NULL;
            }
            else{
                while (occurenceList[actualDayBegin - 1].Count == 0){
                    if(dayBegin == dayEnd){ // if dayBegin ==dayEnd and Count is still zero.
                        printf("No such data in designated range. Please retry.\n");
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
            printf("No such data in designated range. Please retry.\n");
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
    // BOTH Day Interval and keyCategory.
    else if ((int)keyCategory != -1 && dayBegin != 0){
        int actualDayBegin = dayBegin;
        while (dayBegin <= dayEnd && occurenceList[actualDayBegin - 1].Count == 0){
            if(dayBegin == dayEnd){
                printf("No such data in designated range. Please retry.\n");
                return NULL;
            }
            else{
                while (occurenceList[actualDayBegin - 1].Count == 0){
                    if(dayBegin == dayEnd){ // if dayBegin == dayEnd and Count is still zero.
                        printf("No such data in designated range. Please retry.\n");
                        return NULL;
                    }
                    actualDayBegin++;
                }
            }
        }
        
        int startPos = occurenceList[actualDayBegin - 1].initPos;
        int endPos = occurenceList[dayEnd - 1].initPos + occurenceList[dayEnd - 1].Count;
        if((endPos <= startPos) && (dayBegin != dayEnd))
            endPos = findOccurTail(occurenceList, dayEnd);
        int dataLength = endPos - startPos;

        Spend *dataList = calloc(dataLength, sizeof(Spend));
        keyDataList *keyList = malloc(sizeof(keyDataList));
        keyList->dataList = dataList;
        keyList->keyCategory = (short) keyCategory;
        keyList->dayBegin = dayBegin;
        keyList->dayEnd = dayEnd;
        keyList->extractionType = 2;

        struct LLNode *curr = sortedList;
        for (int i = 0       ; i < startPos  ; i++, curr = curr->next);
        for (int j = 0,k = 0 ; j < dataLength; j++, curr = curr->next){
            if( curr->spend.category == keyCategory)
                dataList[k++] = curr->spend;
        }
        //Computing actual number of data in the keyList.
        int i = 0;
        while(dataList[i].date.day != 0)
            i++;

        if(i == 0){
            printf("No such data in designated range. Please retry.\n");
            return NULL;
        }
        else{
            keyList->listLength = (short) i;
            return keyList;
        }   
    }
    // DEFAULT CASE:
    else if((int)keyCategory == -1 && dayBegin == 0 && dayEnd == 0){
        dayBegin = 1;
        dayEnd = 31;
        while (dayBegin <= dayEnd && occurenceList[dayBegin - 1].Count == 0){
            if(dayBegin == dayEnd && occurenceList[dayBegin - 1].Count == 0){
                printf("No such data in designated range. Please retry.\n");
                return NULL;
            }
            else{
                while (occurenceList[dayBegin - 1].Count == 0)
                    dayBegin++;
            }
        }
            
        int startPos = occurenceList[dayBegin - 1].initPos;
        int endPos = occurenceList[dayEnd - 1].initPos + occurenceList[dayEnd - 1].Count;
        if((endPos <= startPos) && (dayBegin != dayEnd))
            endPos = findOccurTail(occurenceList, dayEnd);
        int dataLength = endPos - startPos;
        
        if(dataLength == 0){
            printf("No such data in designated range. Please retry.\n");
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
        printf("List of expenses with Category %hi\n",keyList->keyCategory);
        printf("The list is ordered in date.(ascending)\n");
        printf("Date\tCategory\tCost\n");
        for (int i = 0; i < keyList->listLength; i++){
            short year = keyList->dataList[i].date.year;
            short month = keyList->dataList[i].date.month;
            short day = keyList->dataList[i].date.day;
            short category = (short)keyList->dataList[i].category;
            int cost = keyList->dataList[i].cost;
            printf("[%d] %hi/%hi/%hi\t%hi\t%d\n", i, year, month, day, category, cost);
        }
    }
    else if (keyList->extractionType == 1){
        short yearBegin = keyList->dataList[0].date.year;
        short monthBegin = keyList->dataList[0].date.month;
        short dayBegin = keyList->dayBegin;
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
            short category = (short)keyList->dataList[i].category;
            int cost = keyList->dataList[i].cost;
            printf("[%d] %hi/%hi/%hi\t%hi\t%d\n", i, year, month, day, category, cost);
        }
    }
    else{
        short yearBegin = keyList->dataList[0].date.year;
        short monthBegin = keyList->dataList[0].date.month;
        short dayBegin = keyList->dayBegin;
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
            short category = (short)keyList->dataList[i].category;
            int cost = keyList->dataList[i].cost;
            printf("[%d] %hi/%hi/%hi\t%hi\t%d\n", i, year, month, day, category, cost);
        }
    }
}

struct LLNode *deleteAction(struct LLNode *sortedList, Occurence *occurenceList){
    printf("Do you want to view a certain range of data to select which data to delete?\n");
    printf("[0] Show every data without any filthering (NOT RECOMMENDED).\n");
    printf("[1] Show all data with certain category.\n");
    printf("[2] Show all data with certain range of date.\n");
    printf("[3] Show all data with both certain range and category\n");
    printf("[-1] Back to menu\n");
    int userOption;
    scanf("%d",&userOption);

    if (userOption == 0){            //Every data in the list
        keyDataList *keyList = getKeyData(sortedList, occurenceList, -1, 1, 31);
        if (keyList == NULL){
            printf("No such data in designated range, please retry.\n");
            return sortedList;
        }
        else{
            while(1){
                printKeyList(keyList);
                printf("Please select which data you would like to delete: (Enter index in [])\n");
                int keyIndex;
                scanf("%d",&keyIndex);
                if (keyIndex < keyList->listLength && keyIndex >= 0){
                    Spend keyData = keyList->dataList[keyIndex];
                    sortedList = deleteNode(sortedList, keyData);
                    return sortedList;
                }
                else{   //Invalid keyIndex
                    printf("Invalid input, please retry\n");
                    continue;
                }                    
            }
        }
    }
    else if (userOption == 1){      //Category only
        printf("Which kind of category of would you like to view?\n");
        printf("[0]food\t[1]Clothing\t[2]Transportation\t[3]Utility\n");
        printf("[4]Misc\t[5]Wage\n");

        int keyCategory;
        scanf("%d",&keyCategory);
        //illegal input handling
        if (keyCategory < 0 || keyCategory > 6){
            printf("Invalid input, please retry\n");
            return sortedList;
        }
        else{
            keyDataList *keyList = getKeyData(sortedList, occurenceList, keyCategory, 1, 31);
            if (keyList == NULL){
                printf("No such data in designated range, please retry.\n");
                return sortedList;
            }
            else{
                while(1){       //Selecting which data to delete.
                    printKeyList(keyList);
                    printf("Please select which data you would like to delete: (Enter index in [])\n");
                    int keyIndex;
                    scanf("%d",&keyIndex);
                    if (keyIndex < keyList->listLength && keyIndex >= 0){
                        Spend keyData = keyList->dataList[keyIndex];
                        sortedList = deleteNode(sortedList, keyData);
                        return sortedList;
                    }
                    else{   //Invalid keyIndex
                        printf("Invalid input, please retry\n");
                        continue;
                    }                    
                }
            }
        }
    }
    else if (userOption == 2){      //Date Interval Only
        printf("What date interval would you like to view?\n");
        printf("Format:<dayBegin> <dayEnd> (e.g. 10 25)\n");
        printf("Enter same number in dayBegin, dayEnd if you want to view data of a certain day. (e.g. 15 15)\n");

        short int dayBegin, dayEnd;
        scanf("%hi %hi",&dayBegin ,&dayEnd);
        //illegal input handling
        if (dayBegin < 1 || dayEnd < 1 || dayBegin > dayEnd || dayBegin > 31 || dayEnd > 31){
            printf("Invalid input, please retry\n");
            return sortedList;
        }
        else{
            keyDataList *keyList = getKeyData(sortedList, occurenceList, -1, dayBegin, dayEnd);
            if (keyList == NULL){
                printf("No such data in designated range, please retry.\n");
                return sortedList;
            }
            else{
                while(1){
                    printKeyList(keyList);
                    printf("Please select which data you would like to delete: (Enter index in [])\n");
                    int keyIndex;
                    scanf("%d",&keyIndex);
                    if (keyIndex < keyList->listLength && keyIndex >= 0){
                        Spend keyData = keyList->dataList[keyIndex];
                        sortedList = deleteNode(sortedList, keyData);
                        return sortedList;
                    }
                    else{   //Invalid keyIndex
                        printf("Invalid input, please retry\n");
                        continue;
                    }                    
                }
            }
        }
    }
    else if (userOption == 3){      //Both category and date interval.
        printf("Which kind of category of would you like to view?\n");
        printf("[0]food\t[1]Clothing\t[2]Transportation\t[3]Utility\n");
        printf("[4]Misc\t[5]Wage\n");

        int keyCategory;
        scanf("%d",&keyCategory);
        //illegal input handling
        if (keyCategory < 0 || keyCategory > 6){
            printf("Invalid input, please retry\n");
            return sortedList;
        }
        else{
            printf("And what date interval would you like to view?\n");
            printf("Format:<dayBegin> <dayEnd> (e.g. 10 25)\n");
            printf("Enter same number in dayBegin, dayEnd if you want to view data of a certain day. (e.g. 15 15)\n");

            short int dayBegin, dayEnd;
            scanf("%hi %hi",&dayBegin ,&dayEnd);
            // Illegal Input
            if (dayBegin < 1 || dayEnd < 1 || dayBegin > dayEnd || dayBegin > 31 || dayEnd > 31){
                printf("Invalid input, please retry\n");
                return sortedList;
            }
            else{   //Correct Input
                keyDataList *keyList = getKeyData(sortedList, occurenceList, keyCategory, dayBegin, dayEnd);
                if (keyList == NULL){   //No data in range
                    printf("No such data in designated range, please retry.\n");
                    return sortedList;
                }
                else{                   //There's data in range
                    while(1){
                        printKeyList(keyList);
                        printf("Please select which data you would like to delete: (Enter index in [])\n");
                        int keyIndex;
                        scanf("%d",&keyIndex);
                        if (keyIndex < keyList->listLength && keyIndex >= 0){
                            Spend keyData = keyList->dataList[keyIndex];
                            sortedList = deleteNode(sortedList, keyData);
                            return sortedList;
                        }
                        else{
                            printf("Invalid input, please retry\n");
                            continue;
                        }                    
                    }
                }
            }
        }
    }
    else if (userOption == -1){
        return sortedList;
    }
    else{       //Illegal option input.
        printf("Invalid option, please retry.\n");
        return sortedList;
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

static LLNode* getNode(LLNode* head, Spend spend){
    LLNode* focus = head;
    while(focus){
        if(isEqualValue(SpendType,&focus->spend,&spend)){
            return focus;
        }else focus = focus->next;
    }
    errorMsg("Node not found.",__FILE__,__LINE__);
    return NULL;
}
/**
 * 回傳移除某資料後的list的head
 */
LLNode* LLNode_removeNode(LLNode* head,Spend spend,boolean* boo){
    LLNode* node = getNode(head, spend);
    if(node==NULL){
        *boo = False;
        return head;
    }
    *boo = True;
    if(node == head){
        if(node->next == NULL){
            free(node);
            return NULL;
        }else{
            LLNode* nextHead = node->next;
            nextHead->prev = NULL;
            free(node);
            return nextHead;
        }
    }else{
        //tail
        if(node->next == NULL){
            node->prev->next = NULL;
            free(node);
            return head;
        }else{
            node->prev->next = node->next;
            node->next->prev = node->prev;
            free(node);
            return head;
        }
    }
}



//my test main
/***
int main (){
    int num = 22;
    struct LLNode *head = malloc(sizeof(struct LLNode));
    int listSize = 0;
    for (int i = 0 ; i < num ; i++, listSize++){
        int year, month, day;
        int category, cost;
        char note[16];
        scanf("%d/%2d/%2d %d %d %s",&year ,&month ,&day ,&category ,&cost ,note);

        Spend data;
        data.date.year = (short) year;
        data.date.month = (short) month;
        data.date.day = (short) day;
        data.category = category;
        data.cost = cost;
        strcpy(data.note, note);

        struct LLNode *key = malloc(sizeof(struct LLNode));
        key->spend = data;
        key->next = key->prev = NULL;

        if (i == 0)
            head = createList(data);    //first element in the list.
        else
            sortedInsert(head, NULL, key, listSize);
    }
    for(;head->prev != NULL; head = head->prev);
    printLL(head);

    Occurence *occurList = findOccurence(head);
    printOccurence(occurList, DAY_OF_MONTH);

    //testing delete function for 5 times
    for(int i = 0; i < 5 ; i++){
        head = deleteAction(head, occurList);
        occurList = findOccurence(head);
        printLL(head);
        printOccurence(occurList, DAY_OF_MONTH);
    }
    
    // keyDataList *keyList = getKeyData(head, occurList, food, 1, 15);
    // printKeyList(keyList);

    // keyDataList *keyList1 = getKeyData(head, occurList, transportation, 0, 0);
    // printKeyList(keyList1);

    // keyDataList *keyList2 = getKeyData(head, occurList, -1, 1, 25);
    // printKeyList(keyList2);

    // printf("illgal Input Example, Category Overflow :getKeyData(head, occurList, 6, 1, 25)\n");
    // keyDataList *keyList3 = getKeyData(head, occurList, 6, 1, 25);
    // printf("illgal Input Example, Incorrect Date :getKeyData(head, occurList, 1, 0, 25)\n");
    // keyDataList *keyList4 = getKeyData(head, occurList, 1, 0, 25);
    // printf("illgal Input Example, No specifier :getKeyData(head, occurList, -1, 0, 0)\n");
    // keyDataList *keyList5 = getKeyData(head, occurList, -1, 0, 0);

    system("PAUSE");
    return 0;
}***/