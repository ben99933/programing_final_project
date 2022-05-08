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
typedef struct LinkedListNode LinkedListNode;
struct LinkedList{
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
    DataType type;
    int size;
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
    int len = strlen(string);
    node->value.stringValue = malloc(sizeof(char)*(len+1));
    strncpy(node->value.stringValue,string,len);
    node->value.stringValue[len] = '\0';
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
//===============================================================================
LinkedList* newLinkedList(DataType type){
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head =NULL;
    list->tail = NULL;
    list->type = type;
    list->size = 0;
    return list;
}

static boolean indexOutOfBoundry(LinkedList* list,const int index){
    if(index >= list->size){
        errorMsg("index out of Boundry",__FILE__, __LINE__);
        return True;
    }else return False;
}
static LinkedListNode* getNodeAt(LinkedList* list, const int index){
    if(indexOutOfBoundry(list,index))return NULL;
    int count = 0;
    LinkedListNode* focus = list->head;
    while(count<index){
        focus = focus->next;
        count++;
    }
    return focus;
}

static void removeNode(LinkedList* list, LinkedListNode* node){
    
    if(list->type == String){
        free(node->value.stringValue);
    }else if(list->type == DateType){
        free(node->value.dateValue);
    }
    
    if(list->size==1){
        list->head = NULL;
        list->tail = NULL;
    }else if(node == list->head){
        list->head = node->next;
        node->previous = NULL;
    }else if(node == list->tail){
        node->previous->next = NULL;
        list->tail = node->previous;
    }else{
        node->previous->next = node->next;
        node->next->previous = node->previous;
    }
    free(node);
    list->size-=1;
}
boolean linkedList_remove(LinkedList* list,void*value);
boolean linkedList_removeIndex(LinkedList* list,const int index){
    if(indexOutOfBoundry(list,index))return False;

    LinkedListNode* node = getNodeAt(list,index);
    
    removeNode(list,node);
    return True;

}


boolean isEmptyList(const LinkedList* list){
    if(list->head)return False;
    return True;
}
int linkedList_lengeth(const LinkedList* list){
    return list->size;
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
        errorMsg("unknown dataType",__FILE__,__LINE__);
        return;
    }
    debugMsg("Node constructed",__FILE__,__LINE__);

    if(isEmptyList(list)){
        list->head = node;
        list->tail = node;
    }else{
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
    list->size+=1;
}


char linkedList_getValueChar(LinkedList* list, const int index){
    return getNodeAt(list,index)->value.charValue;
}
char* linkedList_getValueString(LinkedList* list, const int index){
    return getNodeAt(list,index)->value.stringValue;
}
int linkedList_getValueInt(LinkedList* list, const int index){
    return getNodeAt(list,index)->value.intValue;
}
long long linkedList_getValueLong(LinkedList* list,const int index){
    return getNodeAt(list,index)->value.longValue;
}
float linkedList_getValueFloat(LinkedList* list,const int index){
    return getNodeAt(list,index)->value.floatValue;
}
double linkedList_getValueDouble(LinkedList* list, const int index){
    return getNodeAt(list,index)->value.doubleValue;
}
boolean linkedList_getValueBool(LinkedList* list, const int index){
    return getNodeAt(list,index)->value.boolValue;
}
Date* linkedList_getValueDate(LinkedList* list, const int index){
    return getNodeAt(list,index)->value.dateValue;
}

