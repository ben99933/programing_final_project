#include <stdio.h>
#include <stdlib.h>
#include "mypart.h"

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

//Insert new node and retrun new head. (first element of list)
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
    for (;curr != NULL; curr = curr->next){
        short int year = curr->spend.date.year;
        short int month = curr->spend.date.month;
        short int day = curr->spend.date.day;
        int category = (int) curr->spend.category;
        int cost = curr->spend.cost;
        printf("%hi/%hi/%hi\t%d\t%d\n", year, month, day, category, cost);
    }
}

int isSameDate(Date date1, Date date2){
    if((date1.year == date2.year) && (date1.month == date2.month) && (date1.day == date2.day))
        return 1;
    else
        return 0;
}

//This function creates occurence list for further data extraction purposes.
Occurence *findOccurence(struct LLNode *sortedList){
    struct LLNode *curr = sortedList;
    Occurence *occurList = calloc(DAY_OF_MONTH, sizeof(Occurence));
    
    for (int pos = 0;curr != NULL;)
    {
        Date tempDate = curr->spend.date;
        int currDate = ((int) tempDate.day) - 1; // -1 to match index (start from 0)
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
        if(occurenceList[i].Count == 0)
            continue;
        else
            printf("%d\t%d\t%d\n", i + 1, occurenceList[i].Count, occurenceList[i].initPos);
    }
}

//my test main
int main (){
    int num = 22;
    struct LLNode *head = malloc(sizeof(struct LLNode));
    int listSize = 0;
    for (int i = 0 ; i < num ; i++, listSize++){
        int year, month, day;
        int category, cost;
        scanf("%d/%2d/%2d %d %d",&year ,&month ,&day ,&category ,&cost);
        Spend data;
        data.date.year = (short) year;
        data.date.month = (short) month;
        data.date.day = (short) day;
        data.category = category;
        data.cost = cost;
        struct LLNode *key = malloc(sizeof(struct LLNode));
        key->spend = data;
        key->next = key->prev = NULL;

        if (i == 0)
            head = createList(data);
        else
            sortedInsert(head, NULL, key, listSize);
    }
    for(;head->prev != NULL; head = head->prev);
    printLL(head);

    Occurence *occurList = findOccurence(head);
    printOccurence(occurList, DAY_OF_MONTH);

    system("PAUSE");
    return 0;
}