#include"date.h"


#ifndef CONSUMPTION_H
    #define CONSUMPTION_H

    extern const char* FOOD;
    extern const char* TRAFFIC;
    extern const char* ENTERTAINMENT;
    extern const char* SHOPPING;
    extern const char* OTHER;

    typedef enum Category{
        food,traffic,entertainment,shopping,other
    }Category;
    typedef struct Spend{
        int cost;
        Category category;
        Date* date;
        char note[16];//備註
    } Spend;
    Spend* newSpend(int cost,Category category,Date* date, const char* note);
    Category toCategory(int num);
    const char* toCategoryString(Category category);
#endif