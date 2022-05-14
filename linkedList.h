
#include"dataType.h"
#include"date.h"

#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    
    struct LinkedList;
    typedef struct LinkedList LinkedList;

    LinkedList* listBuffer;//用於暫存

    /*建構一個LinkedList 並且把它初始化
     *參數DataType是這個List節點的資料型態 
     *這樣做是為了達到類似泛型(Generic)的效果
     */
    LinkedList* newLinkedList(const DataType type);

    void linkedList_add(LinkedList* list, void* value);

    void linkedList_insert(LinkedList* list, int index, void* value);
    void linkedList_compareAndInsert(LinkedList* list, void* value);
    
    /*
     * 移除"第一個"遇到的相同VALUE的節點
     * 如果移除成功 返回true
     * 找不到該點 返回false
     */
    boolean linkedList_removeValue(LinkedList* list,void*value);
    boolean linkedList_removeIndex(LinkedList* list,const int index);
    boolean isEmptyList(const LinkedList* list);
    //void *linkedList_getValue(const LinkedList* list,const int index);
    int linkedList_lengeth(const LinkedList* list);
    
    char linkedList_getValueChar(LinkedList* list, const int index);
    char* linkedList_getValueString(LinkedList* list, const int index);
    int linkedList_getValueInt(LinkedList* list, const int index);
    long long linkedList_getValueLong(LinkedList* list,const int index);
    float linkedList_getValueFloat(LinkedList* list,const int index);
    double linkedList_getValueDouble(LinkedList* list, const int index);
    boolean linkedList_getValueBool(LinkedList* list, const int index);
    Date* linkedList_getValueDate(LinkedList* list, const int index);
    
    void linkedList_traverse(LinkedList* list, void (*action)(DataType type,void* value));

    void list_destory(LinkedList* list);
#endif
