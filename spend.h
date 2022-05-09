#include"date.h"


#ifndef CONSUMPTION_H
    #define CONSUMPTION_H
    typedef enum Category{
        food,traffic,entertainment,shopping
    }Category;
    typedef struct Spend{
        int cost;
        Category category;
        Date* date;
    } Spend;
    Spend* newSpend(int cost,Category category,Date* date);
    
#endif