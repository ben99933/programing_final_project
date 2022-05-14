#include"spend.h"
#include"debug.h"
#include<stdlib.h>
#include<string.h>


const char* FOOD = "Food";
const char* TRAFFIC = "Traffic";
const char* ENTERTAINMENT = "Entertainment";
const char* SHOPPING = "Shopping";
const char* OTHER = "Other";

/**
 * 用法:
 * Date的部分
 * Spend* spend = newSpend(cost , Category , newDate(2022, 5, 10) );
 */
Spend* newSpend(int cost,Category category,Date* date, const char* note){
    Spend* spend = malloc(sizeof(Spend));
    spend->cost = cost;
    spend->category = category;
    spend->date = date;
    strncpy(spend->note,note,15);
    spend->note[15] = '\0';
    return spend;
}
Category toCategory(int num){
    if(num > 4){
        errorMsg("Out of category limit.",__FILE__,__LINE__);
        return 4;
    }else if(num < 0){
        errorMsg("Out of category limit.",__FILE__,__LINE__);
        return 0;
    }
    return num;
}
const char* toCategoryString(Category category){
    //food,traffic,entertainment,shopping,other
    if(category == food){
        return FOOD;
    }else if(category == traffic){
        return TRAFFIC;
    }else if(category == entertainment){
        return ENTERTAINMENT;
    }else if(category == shopping){
        return SHOPPING;
    }else{
        return OTHER;
    }
}