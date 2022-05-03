#include"dataType.h"
#include<math.h>
#include<string.h>
#include<stdio.h>
#include"date.h"

int compareTo(DataType type,void* object1, void* object2){
    if(type == Char){
        char c1 = *((char*)object1);
        char c2 = *((char*)object2);
        if(c1 < c2)return -1;
        else if(c1 > c2)return 1;
        else return 0;
    }else if(type == String){
        char* string1 = (char*)object1;
        char* string2 = (char*)object2;
        return strcmp(string1, string2);
    }else if(type == Int || type == Boolean){
        int obj1 = *(int*)object1;
        int obj2 = *(int*)object2;
        if(obj1 < obj2)return -1;
        else if(obj1 > obj2)return 1;
        else return 0;
    }else if(type == Long){
        long long obj1 = *(long long*)object1;
        long long obj2 = *(long long*)object2;
        if(obj1 < obj2)return -1;
        else if(obj1 > obj2)return 1;
        else return 0;
    }else if(type == Float){
        float obj1 = *(float*)object1;
        float obj2 = *(float*)object2;
        if(obj1 < obj2)return -1;
        else if(obj1 > obj2)return 1;
        else return 0;
    }else if(type == Double){
        double obj1 = *(double*)object1;
        double obj2 = *(double*)object2;
        if(obj1 < obj2)return -1;
        else if(obj1 > obj2)return 1;
        else return 0;
    }else if(type == DateType){
        Date* date1 = (Date*)object1;
        Date* date2 = (Date*)object2;
        return getDateDay(date1) == getDateDay(date2) && getDateMonth(date1) == getDateMonth(date2) && getDateYear(date1) == getDateYear(date2);
    }
    else{
        printf("exception : unknown data type\n");
        return object1 == object2 ? 0 : object1 > object2 ? 1 : -1;
    } 
}
boolean isEqualValue(DataType type,void* object1, void* object2){
    if(compareTo(type, object1, object2) == 0)return True;
    else return False;
}