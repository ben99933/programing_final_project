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
    linkedList_add(list,newDate(2022,5,9));
    Date* date = linkedList_getValueDate(list,0);
    printf("%d %d %d\n",date->year,date->month,date->day);
    date = linkedList_getValueDate(list,1);
    printf("%d %d %d\n",date->year,date->month,date->day);
    return 0;
}