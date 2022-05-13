#include"spend.h"
#include"debug.h"
#include<stdlib.h>

/**
 * 用法:
 * Date的部分
 * Spend* spend = newSpend(cost , Category , newDate(2022, 5, 10) );
 */
Spend* newSpend(int cost,Category category,Date* date){
    Spend* spend = malloc(sizeof(Spend));
    spend->cost = cost;
    spend->category = category;
    spend->date = date;
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