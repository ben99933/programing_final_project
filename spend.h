#include"date.h"


#ifndef CONSUMPTION_H
    #define CONSUMPTION_H

    extern const char* FOOD;
    extern const char* CLOTHING;
    extern const char* TRANSPORTATION;
    extern const char* ENTERTAINMENT;
    extern const char* UTILITY;
    extern const char* OTHER;
    extern const char* WAGE;


    typedef enum Category{
        food, clothing, transportation, entertainment, utility, other, wage
    }Category;
    typedef struct Spend{
        int cost;
        Category category;
        Date date;
        char note[16];//這筆消費的備註
    } Spend;
    Spend* newSpend(int cost,Category category,Date date, const char* note);
    Category toCategory(int num);
    const char* toCategoryString(Category category);
#endif