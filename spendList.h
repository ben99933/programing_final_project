#include "date.h"
#include "spend.h"
#include"dataType.h"

#ifndef SPENDLIST_H
    #define SPENDLIST_H

    #define DAY_OF_MONTH 31
    #define EXTRACT_UPPER_LIMIT 500

    /*STRUCT PART FOR DATA */
    //Linked list with data with type Spend.
    struct LLNode{
        Spend spend;
        struct LLNode *next;
        struct LLNode *prev;
    };
    typedef struct LLNode LLNode;
    
    /*
    Occurence: It has two members, and it's used as form of array, whose:
    array index : is the actual day - 1  (day 31 -> index 30, day 1 -> index 0)
    intiPos : the first position(index)  a data with that day first appears.
    Count : indicates how much data there is with the same day.
    */
    typedef struct Occurence{
        int initPos; //index of first position of that Date.
        int Count;   //How many repeated data there are.
    }Occurence;

    /*
    keyDataList has the following members:
    extractionType : This indicates what type of data we need. (certain day interval? certain category? or both?)
    keyCategory : the category we're looking for, -1 if the category is not specified.
    dayBegin,dayEnd : day interval, shoule be easy.
    dataList : it's an array of struct Spend, this is the data we extract from the linked list.
    */
    typedef struct{
        short int extractionType;
        short int keyCategory; //we may have -1, so we're not using enum.
        short int dayBegin, dayEnd;
        short int listLength;
        Spend *dataList;
    }keyDataList;

    /* LINKED LIST OPERATION PART */

    //This function is exclusively for linkedlist creation.
    struct LLNode *createList(Spend data);
    //The list is sorted based on this order: date -> catergory -> cost -> note(alphabetically)
    int compDate(Spend tempDate, Spend nodeDate);
    int compCategory(Spend tempData, Spend nodeData);
    int compCost(Spend tempData, Spend nodeData);
    int compNote(Spend tempData, Spend nodeData);

    /*
    This function is for further node(data) insertion, as well as adding expenses(adding node):
    curr     :just put the head(first element) of the list here.
    prev     :just put NULL here.
    key      :The node(data) to be inserted.
    listSize :The size of current linked list.
    The node(data) to be inserted is *key, and the listSize is the current size(number of elements) in linked list.
    Please review the test main function in spendList.c
    example : sortedInsert(head, NULL, key, listSize);
    */
    void sortedInsert(struct LLNode *curr,struct LLNode *prev, struct LLNode *key, int listSize);
    //a function to compare if key and target;s Spend data are identical.
    int compSpend(Spend key, Spend target);
    //a function to delete a data with key Spend from the linked list.
    struct LLNode *deleteNode(struct LLNode *sortedList, Spend keyData);
    //Prints sorted linked list with index in front.
    void printLL(struct LLNode *head);

    /*OCCURENCE LIST OPERATION PART*/

    //Used by createOccurence, to determine if date1 and date2 is the same date.
    int isSameDate(Date date1, Date date2);
    //Create an array of Occurence based on sortedList.
    Occurence *findOccurence(struct LLNode *sortedList);
    //Prints occurence list of sorted linked list(data).
    void printOccurence(Occurence *occurenceList, int size);
    /*
    Function to find actual ending index of occurenceList.
    To avoid possible index overflow in function getKeyData.
    */
    int findOccurTail(Occurence *occurenceList, int dayEnd);


    /*DATA EXTRACTION PART*/
    
    /*
    This is a general data extraction function, you can choose to :
    1. Enter only keyCategory, leaving both day 0 to get data with certain category.
    2. Enter only dayBegin and dayEnd, leaving keyCategory -1 to get data of certain interval
    3. Enter all of those to get data within certain interval and of certain category.
    NOTE: If you want the data from 1 specific day, type same number in dayBegin and dayEnd !
    NOTE: REMEMBER IF YOU DON'T NEED dayBegin and dayEnd OPTION, BE SURE TO LEAVE them AS 0 !!
    AND IF YOU DON'T NEED keyCategory, LEAVE keyCategory AS -1 !
    */
    keyDataList *getKeyData(struct LLNode *sortedList, Occurence *occurenceList, Category keyCategory, const short dayBegin, const short dayEnd);
    //prints keyList with designated type of data.
    void printKeyList(keyDataList *keyList);

    /*DELETE DATA BASED ON EXTRACTED DATA*/

    /*
    This function calls delete node in linked list part to delete a certain data
    The function first asks if user wants to view a data of a certain interval, EXACTLY LIKE getKeydata.
    We use getKeyData to get the data of that certain range, and show it to the users, and ask them which one to delete.
    This function returns the head of the list. (i.e. new sortedList).
    NOTE : THIS FUNCTION MUST BE USED COUPLING WITH findOccurence as follows, please check testing main function.
    //some delete section example:
    sortedList  = deleteAction(sortedList, occurenceList);
    occurenceList = findOccurence(sortedList);
    ...(other actions)
    */
    struct LLNode *deleteAction(struct LLNode *sortedList, Occurence *occurenceList);
    /**
     * 把List給釋放掉
     */
    void destorySpendList(LLNode* head);
    LLNode* LLNode_removeNode(LLNode* head,Spend spend, boolean* boo);

#endif