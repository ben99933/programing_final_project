#include "date.h"
#include "spend.h"

#ifndef SPENDLIST_H
    #define SPENDLIST_H
    
    #define DAY_OF_MONTH 31

    /*LINKED LIST PART*/
    /*
    Doubly linked list is needed for the ease of access.
    For the searching part, what we can do is to declare three pointers : head, tail and mid.
    For every targetDate, we just need to compare the targetDate's index with these three nodes (compare index).
    Just like binary search, except there's only one search.
    */

    struct LLNode{
        Spend spend;
        struct LLNode *next;
        struct LLNode *prev;
    };

    //This function is exclusively for linkedlist creation.
    struct LLNode *createList(Spend data);
    //The list is sorted based on this order: date -> catergory -> cost
    int compDate(Spend tempDate, Spend nodeDate);
    int compCategory(Spend tempData, Spend nodeData);
    int compCost(Spend tempData, Spend nodeData);
    //This function is for further node(data) insertion, as well as adding expenses(adding node).
    void sortedInsert(struct LLNode *curr,struct LLNode *prev, struct LLNode *key, int listSize);
    /*
    deletaData:
    This function will print the sorted list with distinct index in front of every node.
    So that user can just delete any node on the list.
    */
    void deleteData(struct LLNode *list);
    //Testing function to print sorted linked list with index in front.
    void printLL(struct LLNode *head);

    /*OCCURENCE LIST PART*/
    typedef struct Occurence{
        int initPos; //index of first position of that Date.
        int Count;   //How many repeated data there are.
    }Occurence;

    //Used by createOccurence, to return if date1 and date2 is the same date.
    int isSameDate(Date date1, Date date2);
    //Create an array of Occurence based on sortedList.
    Occurence *findOccurence(struct LLNode *sortedList);
    //Testing function to print occurence list.
    void printOccurence(Occurence *occurenceList, int size);



    /*Data extraction part*/

#endif
