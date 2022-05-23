#include"date.h"
#include"debug.h"
#include<stdlib.h>


boolean isLeapYear(int year){
    if((((year) % 4) == 0 && ((year) % 100) != 0) || ((year) % 400) == 0)return True;
    return False;
}
boolean checkDate(int year, int month, int day){
    
    if(day >31 || day <= 0){
        if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
        return False;
    }
    if(month==2){
        if(isLeapYear(year)){
            if(day >29){
                if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
                return False;
            }
        }else{
            if(day>28){
                if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
                return False;
            }
        }
    }else{
        if(month %2==0 && day >30){
            if(isDebugMode())errorMsg("invalid date",__FILE__,__LINE__);
            return False;
        }else if(day >31){
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
    if(checkDate(date->year,date->month,date->day) == False)return NULL;
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
