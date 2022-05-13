#include"date.h"


#ifndef CONSUMPTION_H
    #define CONSUMPTION_H
    typedef enum Category{
        food,traffic,entertainment,shopping,other
    }Category;
    typedef struct Spend{
        int cost;
        Category category;
        Date* date;
        char note[16];//備註
    } Spend;
    Spend* newSpend(int cost,Category category,Date* date);
    Category toCategory(int num);
#endif