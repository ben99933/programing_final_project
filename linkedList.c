#include"linkedList.h"
#include<stdlib.h>
#include"dataType.h"

struct LinkedListNode{
    struct LinkedListNode* next;
    struct LinkedListNode* previous;
    DataType type;
    void* value;
};
struct LinkedList{
    struct LinkedListNode* head;
    struct LinkedListNode* tail;
    DataType type;
};

//建構一個節點並且把她初始化 外面呼叫不了這個程式
static LinkedListNode* newNode(DataType type, void* value){
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->previous = NULL;
    node->value = value;
    node->type = type;
    return node;
}

LinkedList* newLinkedList(const DataType type){
    LinkedList* list = malloc(sizeof(LinkedList));
    list->type = type;
    return list;
}

void linkedList_add(LinkedList* list, void* value){
    LinkedListNode* node = newNode(list->type, value);
    //if head == null
    if(!list->head){
        list->head = node;
        list->tail = node;
    }else{
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = list->tail->next;
    }
}

boolean linkedList_insert(LinkedList* list, int index, void* value){
    int count = 0;
    LinkedListNode* focus = list->head;
    while(focus){
        if(count == index)break;
        count++;
        focus = focus->next;
    }
    if(count != index)return False;
    if(!focus)return False;
    LinkedListNode* node = newNode(list->type, value);
    if(focus == list->tail){
        
    }else if(focus->next == list->tail){

    }
}


boolean linkedList_remove(LinkedList* list,void*value){
    LinkedListNode* focus = list->head;
    while(focus){
        if(isEqualValue(list->type, focus->value, value)){
            if(focus == list->head){
                if(focus->next == NULL){
                    list->head = NULL;
                    list->tail = NULL;
                }
                else{
                    list->head = list->head->next;
                }
            }else{
                if(focus->next == NULL)list->tail = NULL;
                else {
                    focus->previous->next = focus->next;
                    focus->next->previous = focus->previous;
                }
            }
            free(focus);
            return True;
        }
    }
    return False;
}

int linkedList_lengeth(LinkedList* list){
    LinkedListNode* focus = list->head;
    int len = 0;
    while(focus){
        len++;
        focus = focus->next;
    }
    return len;
}






