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
    void* value;
};
typedef struct LinkedListNode LinkedListNode;
struct LinkedList{
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
    DataType type;
    int size;
};

static LinkedListNode* newNode(DataType type,void *value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->type = type;
    node->value = value;
    return node;
}

//===========================這部分已經捨去==========================================
/***
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
}***/
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
    
    free(node->value);
    
    if(list->size==1){
        list->head = NULL;
        list->tail = NULL;
    }else if(node == list->head){
        list->head = node->next;
        list->head->previous = NULL;
    }else if(node == list->tail){
        list->tail = node->previous;
        list->tail->next = NULL;
    }else{
        node->previous->next = node->next;
        node->next->previous = node->previous;
    }
    free(node);
    list->size-=1;
}
boolean linkedList_removeValue(LinkedList* list,void*value){
    if(isEmptyList(list)){
        if(isDebugMode())errorMsg("list is empty",__FILE__,__LINE__);
        return False;
    }
    LinkedListNode* focus = list->head;
    while(focus){
        if(isEqualValue(list->type,focus->value,value)){
            removeNode(list, focus);
            return True;
        }
        focus = focus->next;
    }
    if(isDebugMode())errorMsg("value not found",__FILE__,__LINE__);
    return False;
}
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
    LinkedListNode* node = newNode(list->type,value);
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
void linkedList_insert(LinkedList* list, int index, void* value){
    if(isEmptyList(list)){
        linkedList_add(list,value);
        return;
    }else if(list->size == 1){
        linkedList_add(list,value);
        return;
    }else{
        LinkedListNode* current = getNodeAt(list, index);
        LinkedListNode* node = newNode(list->type,value);
        if(current == list->tail){
            current->next = node;
            node->previous = current;
            node->next = NULL;
            list->tail = node;
            return;
        }else{
            node->next = current->next;
            current->next->previous = node;
            node->previous = current;
            current->next = node;
        }
    }
    
}
void linkedList_compareAndInsert(LinkedList* list,void* value){
    LinkedListNode* focus = list->head;
    while(focus!=list->tail){
        if(compareTo(list->type,value,focus->value) <= 0){
            LinkedListNode* node = newNode(list->type,value);
            if(focus == list->head){
                node->next = focus;
                focus->previous = node;
                node->previous = NULL;
                list->head = node;
            }else{
                focus->previous->next = node;
                node->previous = focus->previous;
                node->next = focus;
                focus->previous = node; 
            }
        }else focus = focus->next;
    }
    linkedList_add(list,value);
}

char linkedList_getValueChar(LinkedList* list, const int index){
    return *(char*)getNodeAt(list,index)->value;
}
char* linkedList_getValueString(LinkedList* list, const int index){
    return (char*)getNodeAt(list,index)->value;
}
int linkedList_getValueInt(LinkedList* list, const int index){
    return *(int*)getNodeAt(list,index)->value;
}
long long linkedList_getValueLong(LinkedList* list,const int index){
    return *(long long*)getNodeAt(list,index)->value;
}
float linkedList_getValueFloat(LinkedList* list,const int index){
    return *(float*)getNodeAt(list,index)->value;
}
double linkedList_getValueDouble(LinkedList* list, const int index){
    return *(double*)getNodeAt(list,index)->value;
}
boolean linkedList_getValueBool(LinkedList* list, const int index){
    return *(boolean*)getNodeAt(list,index)->value;
}
Date* linkedList_getValueDate(LinkedList* list, const int index){
    return (Date*)getNodeAt(list,index)->value;
}


void linkedList_traverse(LinkedList* list, void (*action)(DataType type,void* value)){
    LinkedListNode* focus = list->head;
    while(focus){
        action(list->type,focus->value);
        focus = focus->next;
    }
    
}

void list_destory(LinkedList* list){
    LinkedListNode* focus = list->head;
    while(focus){
        LinkedListNode* node = focus;
        focus = focus->next;
        free(node->value);
        free(node);
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}