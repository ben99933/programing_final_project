#include"spend.h"
#include<stdlib.h>

Spend* newSpend(int cost,Category category,Date* date){
    Spend* spend = malloc(sizeof(Spend));
    spend->cost = cost;
    spend->category = category;
    spend->date = date;
    return spend;
}