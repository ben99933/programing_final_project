#define MYPART_H

#include "date.h"
#include "spend.h"
#define DAY_OF_MONTH 31
#define EXTRACT_UPPER_LIMIT 500

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
/*
Function to find actual ending index of occurenceList.
To avoid possible index overflow in function getKeyData.
*/
int findOccurTail(Occurence *occurenceList);



/*DATA EXTRACTION PART*/

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

//testing function to print designated keyList.
void printKeyList(keyDataList *keyList);
