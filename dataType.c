#include"dataType.h"
#include<math.h>
#include<string.h>
#include<stdio.h>
#include"debug.h"
#include"date.h"
#include<stdlib.h>
#include"spend.h"

int intBuffer[16] = {0};
void clearIntBuffer(){
    for(int i = 0;i<15;i++)intBuffer[i] = 0;
}

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
        if(date1->year < date2->year)return -1;
        else if(date1->year > date2->year)return 1;
        else{
            if(date1->month < date2->month)return -1;
            else if(date1->month > date2->month)return 1;
            else{
                if(date1->day < date2->day)return -1;
                else if(date1->day > date2->day)return 1;
                else return 0;
            }
        }
    }else if(type == SpendType){
        Spend* spend1 = (Spend*)object1;
        Spend* spend2 = (Spend*)object2;
        int dateCmp = compareTo(DateType,&spend1->date,&spend2->date);
        if(dateCmp != 0)return dateCmp;
        else{
            if(spend1->category < spend2->category)return -1;
            else if(spend1->category > spend2->category)return 1;
            else{
                if(spend1->cost < spend2->cost)return -1;
                else if(spend1->cost > spend2->cost)return 1;
                else return strcmp(spend1->note,spend2->note);
            }
        }
    }
    else{
        errorMsg("unknown data type",__FILE__,__LINE__);
        return object1 == object2 ? 0 : object1 > object2 ? 1 : -1;
    } 
}
boolean isEqualValue(DataType type,void* object1, void* object2){
    if(compareTo(type, object1, object2) == 0)return True;
    else return False;
}
void copy(DataType type,void* object1,void* object2){
    if(type == Char){
        *(char*)object1 = *(char*)object2;
        
    }else if(type == Int || type == Boolean){
        *(int*)object1 = *(int*)object2;
        
    }else if(type == Long){
        *(long long*)object1 = *(long long*)object2;
        
    }else if(type == Float){
        *(float*)object1 = *(float*)object2;
        
    }else if(type == Double){
        *(double*)object1 = *(double*)object2;
        
    }else if(type == DateType){
        Date* date1 = (Date*)object1;
        Date* date2 = (Date*)object2;
        *date1 = *date2;
    }else if(type == SpendType){
        Spend* spend1 = (Spend*)object1;
        Spend* spend2 = (Spend*)object2;
        *spend1 = *spend2;
    }
    else{
        errorMsg("unknown data type",__FILE__,__LINE__);
    } 
}

char* newChar(char c){
    char* ptr = malloc(sizeof(char));
    *ptr=c;
    return ptr;
}
int* newInt(int i){
    int* ptr = malloc(sizeof(int));
    *ptr=i;
    return ptr;
}
long long* newLong(long long l){
    long long* ptr = malloc(sizeof(long long));
    *ptr = l;
    return ptr;
}
float* newFloat(float f){
    float* ptr = malloc(sizeof(float));
    *ptr = f;
    return ptr;
}
double* newDouble(double d){
    double* ptr = malloc(sizeof(double));
    *ptr = d;
    return ptr;
}
boolean* newBool(boolean b){
    boolean* ptr = malloc(sizeof(boolean));
    *ptr = b;
    return ptr;
}