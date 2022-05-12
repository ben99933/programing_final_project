#include"spend.h"
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