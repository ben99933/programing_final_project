#include"spend.h"
#include"debug.h"
#include<stdlib.h>
#include<string.h>

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
void toCategoryString(char* string,Category category){
    //food,traffic,entertainment,shopping,other
    if(category == food){
        strcpy(string,"food");
    }else if(category == traffic){
        strcpy(string,"traffic");
    }else if(category == entertainment){
        strcpy(string,"entertainment");
    }else if(category == shopping){
        strcpy(string,"shopping");
    }else{
        strcpy(string,"other");
    }
}