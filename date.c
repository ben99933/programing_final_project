#include"date.h"
#include"debug.h"
#include<stdlib.h>


static boolean checkDate(Date* date);
static boolean isLeapYear(Date*date){
    int year = date->year;
    if((((year) % 4) == 0 && ((year) % 100) != 0) || ((year) % 400) == 0)return True;
    return False;
}
static boolean checkDate(Date* date){
    int day = date->day;
    int month = date->month;
    int year = date->year;
    if(day >31){
        if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
        return False;
    }
    if(date->month==2){
        if(isLeapYear(date)){
            if(date->day >29){
                if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
                return False;
            }
        }else{
            if(date->day>28){
                if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
                return False;
            }
        }
    }else{
        if(date->month %2==0 && date->day >30){
            if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
            return False;
        }else if(date->day >31){
            if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
            return False;
        }
    }
    return True;
}

Date* newDate(int year, int month, int day){
    Date* date = malloc(sizeof(Date));
    date->day = day;
    date->month = month;
    date->year = year;
    if(checkDate(date) == False)return NULL;
    return date;
}

int getDateYear(Date* date){
    return date->year;
}
int getDateMonth(Date* date){
    return date->month;
}
int getDateDay(Date* date){
    return date->day;
}
