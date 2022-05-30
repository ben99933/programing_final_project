#ifndef option4_content_h
    #define option4_content_h
    #include "option4.h"
    #include "spendList.h"
    #include "word.h"

    //askbudget: Let user to enter the amount of budget
    void askbudget(struct budget *userbuget);

    //month_summary: Calculate total expense of each category. Also, print the total revenue, total expense, and balance.
    void month_summary(struct total *usertotal, keyDataList *keyList, struct maxima *usermaxima);

    //func4_1: Calculate proportion and output it.
    void func4_1(struct total usertotal, struct maxima usermaxima);
    
    //func4_2: Ouput the the balance out actual cost and budget. Also give the user suggestion of budget adjustment.
    void func4_2(struct total usertotal, struct budget userbudget);
#endif
