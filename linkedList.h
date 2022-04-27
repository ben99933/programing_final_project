#include"dataType.h"

#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    struct LinkedListNode;
    struct LinkedList;
    
    typedef struct LinkedListNode LinkedListNode;
    typedef struct LinkedList LinkedList;
    
    /*建構一個LinkedList 並且把它初始化
     *參數DataType是這個List節點的資料型態 
     *這樣做是為了達到類似泛型(Generic)的效果
     */
    LinkedList* newLinkedList(const DataType type);

    void linkedList_add(LinkedList* list, void* value);
    
    /*
     * 在index之後插入一個value(Node已經封裝起來 不能用到)
     * 如果插入成功 返回true
     * 反之 回傳false
     */
    boolean linkedList_insert(LinkedList* list, int index, void* value);
    
    /*
     * 移除"第一個"遇到的相同VALUE的節點
     * 如果移除成功 返回true
     * 找不到該點 返回false
     */
    boolean linkedList_remove(LinkedList* list,void*value);
    int linkedList_lengeth(LinkedList* list);
#endif