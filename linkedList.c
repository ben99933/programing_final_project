#include"linkedList.h"
#include<stdlib.h>
#include"dataType.h"
#include"date.h"
#include"debug.h"
#include<stdio.h>
#include<string.h>

struct LinkedListNode{
    struct LinkedListNode* next;
    struct LinkedListNode* previous;
    DataType type;
    union 
    {
        char charValue;
        char* stringValue;
        int intValue;
        long long longValue;
        float floatValue;
        double doubleValue;
        boolean boolValue;
        Date* dateValue;
    }value;
    
};
struct LinkedList{
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
    DataType type;
};
/***
static LinkedListNode* newNode(DataType type,void *value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->value = value;
    node->type = type;
    return node;
}***/

//===========================new Node()==========================================
static LinkedListNode* newNode_Char(DataType type, char value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.charValue = value;
    return node;
}
static LinkedListNode* newNode_String(DataType type, char* string){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    strncpy_s(node->value.stringValue, strlen(string),string,INT_MAX);
    return node;
}
static LinkedListNode* newNode_Int(DataType type, int value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.intValue = value;
    return node;
}
static LinkedListNode* newNode_Long(DataType type, long long value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.longValue = value;
    return node;
}
static LinkedListNode* newNode_Float(DataType type, float value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.floatValue = value;
    return node;
}
static LinkedListNode* newNode_Double(DataType type, double value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.doubleValue = value;
    return node;
}
static LinkedListNode* newNode_Boolean(DataType type, boolean value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.boolValue = value;
    return node;
}
static LinkedListNode* newNode_Date(DataType type, Date* value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value.dateValue = value;
    return node;
}

LinkedList* newLinkedList(DataType type){
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head =NULL;
    list->tail = NULL;
    list->type = type;
    return list;
}
boolean isEmptyList(LinkedList* list){
    if(list->head)return True;
    return False;
}
int linkedList_lengeth(LinkedList* list){
    int count = 0;
    LinkedListNode* focus = list->head;
    while(focus){
        focus = focus->next;
        count++;
    }
    return count;
}
void linkedList_add(LinkedList* list, void* value){
    DataType type = list->type;
    LinkedListNode* node;
    if(type == Char){
        node = newNode_Char(type,*(char*)value);
    }else if(type==String){
        node = newNode_String(type,(char*)value);
    }else if(type == Int){
        node = newNode_Int(type,*(int*)value);
    }else if(type == Long){
        node = newNode_Long(type,*(long long*)value);
    }else if(type == Float){
        node = newNode_Float(type, *(float*)value);
    }else if(type == Double){
        node = newNode_Double(type, *(double*)value);
    }else if(type == Boolean){
        node = newNode_Boolean(type,*(boolean*)value);
    }else if(type == DateType){
        node = newNode_Date(type,(Date*)value);
    }else{
        if(isDebugMode())errorMsg("unknown dataType",__FILE__,__LINE__);
        return;
    }

    if(isEmptyList(list)){
        list->head = node;
        list->tail = node;
    }else{
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
}