#include "spendList.h"

#ifndef OPTION4_H
    #define OPTION4_H
    
    struct budget{
        int food_budget, clothing_budget, transportation_budget, entertainment_budget, utility_budget, other_budget, total_budget;
    };
    struct total{
        int totalwage,totalexpense,totalfood, totalclothing, totaltransportation, totalentertainment, totalutility, totalother;
    };
    struct maxima{
        struct LLNode *food_max, *clothing_max, *transportation_max, *entertainment_max, *utility_max, *other_max;
    };
    void option4(keyDataList *keyList);

#endif