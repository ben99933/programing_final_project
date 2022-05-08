#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"linkedList.h"
#include"dataType.h"
#include"debug.h"
#include"date.h"

int main(){

    LinkedList* list = newLinkedList(DateType);
    linkedList_add(list,newDate(2022,5,8));
    printf("size=%d\n",linkedList_lengeth(list));
    linkedList_removeIndex(list,0);
    printf("size=%d\n",linkedList_lengeth(list));
    return 0;
}