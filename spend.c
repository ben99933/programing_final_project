#include"spend.h"
#include"debug.h"
#include<stdlib.h>
#include<string.h>


 const char* FOOD = "FOOD";
 const char* CLOTHING = "CLOTHING";
 const char* TRANSPORTATION = "TRANSPORTATION";
 const char* ENTERTAINMENT = "ENTERTAINMENT";
 const char* UTILITY  = "UTILITY";
 const char* OTHER = "OTHER";
 const char* WAGE = "WAGE";

Spend* newSpend(int cost,Category category,Date date, const char* note){
    Spend* spend = malloc(sizeof(Spend));
    spend->cost = cost;
    spend->category = category;
    spend->date = date; 
    strncpy(spend->note,note,15);
    spend->note[15] = '\0';
    return spend;
}
Category toCategory(int num){
    if(num > 6){
        errorMsg("Out of category limit.",__FILE__,__LINE__);
        return 6;
    }else if(num < 0){
        errorMsg("Out of category limit.",__FILE__,__LINE__);
        return 0;
    }
    return num;
}
const char* toCategoryString(Category category){
    //food, clothing, transportation, entertainment, utility, other, wage
    if(category == food){
        return FOOD;
    }else if(category == transportation){
        return TRANSPORTATION;
    }else if(category == entertainment){
        return ENTERTAINMENT;
    }else if(category == utility){
        return UTILITY;
    }else if(category == other){
        return OTHER;
    }else if(category == wage){
        return WAGE;
    }else {
        return OTHER;
    }
}