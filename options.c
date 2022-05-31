#include"menu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"
#include"spend.h"
#include "spendList.h"
#include"options.h"
#include"color.h"

struct budget{
    int food_budget, clothing_budget, transportation_budget, entertainment_budget, utility_budget, other_budget, total_budget;
};
struct total{
    int totalwage,totalexpense,totalfood, totalclothing, totaltransportation, totalentertainment, totalutility, totalother;
};
struct maxima{
    struct LLNode *food_max, *clothing_max, *transportation_max, *entertainment_max, *utility_max, *other_max;
};

void errormsg_for_option23(){
    setTextColor(ColorRed);
    printf("Invalid input!\nPlease use the correct input format\n");
    system("pause");
    resetTextColor();
}

//free_LL: free the linked list in type LLNode
void free_LL(struct LLNode *p)
{
    struct LLNode *n = p;
    for (struct LLNode *h = p; n != NULL; h = n)
    {
        n = h->next;
        free(h);
    }
}

//print_maxima: print the information of the maxima
//we may have multiple maxima, so use LLNode *p to point at the linked list of maxima
void print_maxima(char *s, struct LLNode *p)
{
    for (struct LLNode *h = p; h != NULL; h = h->next)
    {
        printf("%-16s|    %04d/%02d/%02d     |%12d       |       %s\n", s, h->spend.date.year, h->spend.date.month, h->spend.date.day, h->spend.cost, h->spend.note);
    }
}

//check_budget: input the budet which user chose(target budget), and check the budget is correspond to the condition
//**only use in function askbudget**
//return 1 for "continue" in askbudget
//return 0 for "break" in askbudget
int check_budget(int *total_budget, int *target_budget, int *sum)
{
    char amount[1024];
    fgets(amount,1024,stdin);
    trimString(amount);

    //CHECK INPUT FORMAT
    if(strcmp(amount,"-1") == 0)                //enter "-1" for not consider the budget
    {
        
        if(*target_budget != -1)                //*target_budget != -1 means the user had considering and inputting the budget before
        {                                       
            *sum -= *target_budget;             //subtract the amount of orignal budget from the *sum
            *target_budget = -1;               
        }
        return 0;
    }
    if(strcmp(amount,"back") == 0)              //enter "back" for backing to the previous step
    {
        return 0;
    }


    if(!isNumberString(amount))                 //if the input includes non-numerical character, ouput the warning
    {
        setTextColor(ColorRed);
        printf("Invalid input!\n");
        system("pause");
        resetTextColor();
        return 1;
    }
    if(strlen(amount) == 0)                     //for only enter "\n"
    {
        return 1;
    }
    //CHECK INPUT FORMAT DONE

    //by condition, if you consider the total budget, then total budget most be larger than the sum of all the other types of budgets.
    if(*total_budget != -1)                     //*total_budget != -1 means user have considered total budget
    {                                           //*sum: the sum of all budeget except total budget
        if(*total_budget < (*sum) + toIntValue(amount))         //if *total_budget < (*sum) + toIntValue(amount), it's ineligible
        {   setTextColor(ColorYellow);                                                    //print warning
            printf("The total budget is less than the sum of all the other types of budget.");
            printf("Please enter the budget again.\n");
            system("pause");
            resetTextColor();
            return 1;
        }
    }
    if(*target_budget != -1)                    //*target_budget != -1 means the user have considered and input the budget
    {
        *sum -= *target_budget;                 //subtract the amount of orignal budget form the *sum
    }
    *target_budget = toIntValue(amount);        //store toIntValue(amount) in to *target_budget
    *sum += *target_budget;                     //add the amount of *target_budget into *sum
    return 0;
}

//deal_consumption: judge the consumption is maxima or not, and make the linked list of maxima
//**only use in fumction month_summary**
void deal_consumption(int *target_total, Spend consumption, LLNode **target_maxima)
{
    *target_total += consumption.cost;          //add the cost of consumption into total
    
    if(*target_maxima == NULL)                  //*target_maxima == NULL means this consumption is the first consumtion of this category
    {                                           //set this consumption as the maxima consumptino of this category
        *target_maxima = malloc(sizeof(struct LLNode));
        (*target_maxima)->spend = consumption;
        (*target_maxima)->next = NULL;
    }
    else if(consumption.cost > (*target_maxima)->spend.cost)        //if consumption.cost > (*target_maxima)->spend.cost
    {                                                               //then we change maxima cost into the cost of this consumption
        free_LL(*target_maxima);
        *target_maxima = malloc(sizeof(struct LLNode));
        (*target_maxima)->spend = consumption;
        (*target_maxima)->next = NULL;
    }
    else if(consumption.cost == (*target_maxima)->spend.cost)       //if consumption.cost == (*target_maxima)->spend.cos
    {                                                               //then add node at the linked list of maxima and store this consumption in the node
        struct LLNode *h = *target_maxima;
        while (h->next!= NULL)                                      //find the end of the linked list
        {
            h = h->next;
        }
        h->next = malloc(sizeof(struct LLNode));
        h->next->next = NULL;
        h->next->spend = consumption;
    }
}

//print_budget: print the amount of the budget
void print_budget(int target_budget)            
{
    if(target_budget == -1)                     //target_budget == -1 means user doesn't consider this budget
    {
        printf("None\n");
    }
    else
    {
        printf("%d\n", target_budget);
    }
}

//askbudget: Let user to enter the amount of budget
void askbudget(struct budget *userbudget)
{
    //budget == -1 means user doesn't consider that budget
    userbudget->total_budget = -1;
    userbudget->food_budget = -1;
    userbudget->clothing_budget = -1;
    userbudget->transportation_budget = -1;
    userbudget->entertainment_budget = -1;
    userbudget->utility_budget = -1;
    userbudget->other_budget = -1;

    //sum: the total of all the budget except total_budget
    int sum = 0;

    while(1)
    {
        system("CLS");
        printf("=========================================ASK BUDGET================================================================\n");
        printf("Below shows the menu of budgets you can enter and the amount they are now.\n");
        printf("Please "ColorGreen"input the coordinating number of the budget"ColorReset" you want to set.\n");
        printf("If you consider the total budget, then total budget most be larger than the sum of all the other types of budgets.\n");
        printf("Enter \"back\" when you are done.\n\n");
        printf("[0] Total budget: ");
        print_budget(userbudget->total_budget);
        printf("[1] Food budget: ");
        print_budget(userbudget->food_budget);
        printf("[2] Clothing budget: ");
        print_budget(userbudget->clothing_budget);
        printf("[3] Transportation budget: ");
        print_budget(userbudget->transportation_budget);
        printf("[4] Entertainment budget: ");
        print_budget(userbudget->entertainment_budget);
        printf("[5] Utility budget: ");
        print_budget(userbudget->utility_budget);
        printf("[6] Other budget: ");
        print_budget(userbudget->other_budget);
        printf("===================================================================================================================\n");


        char input[1024];
        fgets(input,1024,stdin);
        trimString(input);

        if(strcmp(input,"back") == 0)               //enter "back" for back to the previous step
        {
            return;
        }
        if(!isNumberString(input))                  //if the input includes non-numerical character, ouput the warning
        {
            setTextColor(ColorRed);
            printf("Invalid input!\n");
            system("pause");
            resetTextColor();
            continue;
        }
        if(strlen(input) == 0)                      //for only enter '\n'
        {
            continue;
        }


        int choice = toIntValue(input);
        if(choice == 0)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"total budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                char amount[1024];
                fgets(amount,1024,stdin);
                trimString(amount);

                if(strcmp(amount,"-1") == 0)
                {
                    userbudget->total_budget = -1;
                    break;
                }
                if(strcmp(amount,"back") == 0)             
                {
                    break;
                }

                if(!isNumberString(amount))
                {
                    setTextColor(ColorRed);
                    printf("Invalid input!\n");
                    system("pause");
                    resetTextColor();
                    continue;
                }
                if(strlen(amount) == 0)
                {
                    continue;
                }
                if(toIntValue(amount) < sum)        //if toIntValue(amount) < sum, it's ineligble by the condition we show in menu
                {
                    setTextColor(ColorYellow);
                    printf("The total budget is less than the sum of all the other types of budget.");
                    printf("Please enter the budget again.\n");
                    system("pause");
                    resetTextColor();
                    continue;
                }
                
                userbudget->total_budget = toIntValue(amount);
                break;
            }
            
        }
        else if(choice == 1)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"food budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                if(check_budget(&(userbudget->total_budget), &(userbudget->food_budget), &sum))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            
        }
        else if(choice == 2)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"clothing budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                if(check_budget(&(userbudget->total_budget), &(userbudget->clothing_budget), &sum))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            
        }
        else if(choice == 3)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"transportation budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                if(check_budget(&(userbudget->total_budget), &(userbudget->transportation_budget), &sum))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            
        }
        else if(choice == 4)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"entertainment budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                if(check_budget(&(userbudget->total_budget), &(userbudget->entertainment_budget), &sum))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            
        }
        else if(choice == 5)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"utility budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                if(check_budget(&(userbudget->total_budget), &(userbudget->utility_budget), &sum))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            
        }
        else if(choice == 6)
        {
            while(1)
            {
                system("CLS");
                printf("===================ENTER BUDGET====================\n");
                printf("Enter your "ColorGreen"other budget.\n"ColorReset);
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");
                printf("===================================================\n");

                if(check_budget(&(userbudget->total_budget), &(userbudget->other_budget), &sum))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            
        }
        else
        {
            setTextColor(ColorRed);
            printf("Invalid input!\n");
            system("pause");
            resetTextColor();
            continue;
        }

    }
    
}

//month_summary: Calculate total expense of each category. Also, print the total revenue, total expense, and balance.
//Also find maxima cost in each category
void month_summary(struct total *usertotal, keyDataList *keyList, struct maxima *usermaxima)
{
    usertotal->totalwage = 0;
    usertotal->totalexpense = 0;
    usertotal->totalfood = 0;
    usertotal->totalclothing = 0;
    usertotal->totaltransportation = 0;
    usertotal->totalentertainment = 0;
    usertotal->totalutility = 0;
    usertotal->totalother = 0;

    usermaxima->food_max = NULL;
    usermaxima->clothing_max = NULL;
    usermaxima->transportation_max = NULL;
    usermaxima->entertainment_max = NULL;
    usermaxima->utility_max = NULL;
    usermaxima->other_max = NULL;
    

    Spend *list = keyList->dataList;
    for (int i = 0; i < keyList->listLength; i++)
    {
        
        if(list[i].category == wage)
        {
            usertotal->totalwage += list[i].cost;
        }
        else
        {
            usertotal->totalexpense += list[i].cost;
            if(list[i].category == food)
            {
                deal_consumption(&(usertotal->totalfood), list[i], &(usermaxima->food_max));
            }
            else if(list[i].category == clothing)
            {
                deal_consumption(&(usertotal->totalclothing), list[i], &(usermaxima->clothing_max));
            }
            else if(list[i].category == transportation)
            {
                deal_consumption(&(usertotal->totaltransportation), list[i], &(usermaxima->transportation_max));
            }
            else if(list[i].category == entertainment)
            {
                deal_consumption(&(usertotal->totalentertainment), list[i], &(usermaxima->entertainment_max));
            }
            else if(list[i].category == utility)
            {
                deal_consumption(&(usertotal->totalutility), list[i], &(usermaxima->utility_max));
            }
            else if(list[i].category == other)
            {
                deal_consumption(&(usertotal->totalother), list[i], &(usermaxima->other_max));
            }
        }
    }

    system("CLS");
    printf(ColorGreen"===========MONTH SUMMARY===========\n"ColorReset);
    printf("Food expense: %d\n", usertotal->totalfood);
    printf("Clothing expense: %d\n", usertotal->totalclothing);
    printf("Transportation expense: %d\n", usertotal->totaltransportation);
    printf("Entertainment expense: %d\n", usertotal->totalentertainment);
    printf("Utility expense: %d\n", usertotal->totalutility);
    printf("Other expense: %d\n", usertotal->totalother);

    printf("\nTotal revenue: %d\n", usertotal->totalwage);
    printf("Total expense: %d\n", usertotal->totalexpense);
    printf("Balance: %d\n", usertotal->totalwage - usertotal->totalexpense);
    printf(ColorGreen"===================================\n\n"ColorReset);
}

//func4_1: Calculate proportion and output it.
void func4_1(struct total usertotal,struct maxima usermaxima)
{
    float food_proportion, clothing_proportion, transportation_proportion, entertainment_proportion, utility_proportion, other_proportion;

    //the following variables will store deciamal of the proportaion rounded to the nearest tenth
    food_proportion = (int)((float)usertotal.totalfood / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    clothing_proportion = (int)((float)usertotal.totalclothing / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    transportation_proportion = (int)((float)usertotal.totaltransportation / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    entertainment_proportion = (int)((float)usertotal.totalentertainment / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    utility_proportion = (int)((float)usertotal.totalutility / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    other_proportion = (int)((float)usertotal.totalother / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;

    system("CLS");
    printf(ColorGreen"=======================PROPORTION OF EACH CATEGORY==========================\n"ColorReset);
    printf("food: %.1f%%\n", food_proportion);
    printf("clothing: %.1f%%\n", clothing_proportion);
    printf("transportation: %.1f%%\n", transportation_proportion);
    printf("entertainment: %.1f%%\n", entertainment_proportion);
    printf("utility: %.1f%%\n", utility_proportion);
    printf("other: %.1f%%\n", other_proportion);
    printf(ColorGreen"============================================================================\n\n"ColorReset);  

    printf(ColorGreen"=====================HIGHEST COST OF EACH CATEGORY==========================\n"ColorReset);
    printf("Highest cost    |       date        |       cost        |       note        \n");
    print_maxima("food:", usermaxima.food_max);
    print_maxima("clothing:", usermaxima.clothing_max);
    print_maxima("transportation:", usermaxima.transportation_max);
    print_maxima("entertainment:", usermaxima.entertainment_max);
    print_maxima("utility:", usermaxima.utility_max);
    print_maxima("other:", usermaxima.other_max);
    printf(ColorGreen"============================================================================\n"ColorReset);  
    system("pause");
}

//func4_2: Ouput the the balance out actual cost and budget. Also give the user suggestion of budget adjustment.
void func4_2(struct total usertotal,struct budget userbudget){
    system("CLS");
    short t=0,f=0,c=0,tr=0,e=0,u=0,o=0;

    /*========== General report of actual cost and budget==========*/
    printf(ColorGreen"==================GENERAL REPORT OF ACTUAL COST AND BUDGET==================\n"ColorReset);    
    printf("                |    actual cost    |      budget       |      balance      \n");
    if(userbudget.total_budget!=-1){
        t=userbudget.total_budget-usertotal.totalexpense;
        printf("total           |%12d       |%12d       |%12hd       \n",usertotal.totalexpense,userbudget.total_budget,t);

    }
    if(userbudget.food_budget!=-1){
        f=userbudget.food_budget-usertotal.totalfood;
        printf("food            |%12d       |%12d       |%12hd       \n",usertotal.totalfood,userbudget.food_budget,f);
        f=(f*7)/100*10;
    }
    if(userbudget.clothing_budget!=-1){
        c=userbudget.clothing_budget-usertotal.totalclothing;
        printf("clothing        |%12d       |%12d       |%12hd       \n",usertotal.totalclothing,userbudget.clothing_budget,c);
        c=(c*5)/100*10;
    }  
    if(userbudget.transportation_budget!=-1){
        tr=userbudget.transportation_budget-usertotal.totaltransportation;
        printf("transportation  |%12d       |%12d       |%12hd       \n",usertotal.totaltransportation,userbudget.transportation_budget,tr);
        tr=(tr*8)/100*10;
    }   
    if(userbudget.entertainment_budget!=-1){
        e=userbudget.entertainment_budget-usertotal.totalentertainment;
        printf("entertainment   |%12d       |%12d       |%12hd       \n",usertotal.totalentertainment,userbudget.entertainment_budget,e);
        e=(e*5)/100*10;
    }   
    if(userbudget.utility_budget!=-1){
        u=userbudget.utility_budget-usertotal.totalutility;
        printf("utility         |%12d       |%12d       |%12hd       \n",usertotal.totalutility,userbudget.utility_budget,u);
        u=(u*8)/100*10;
    }
    if(userbudget.other_budget!=-1){
        o=userbudget.other_budget-usertotal.totalother;
        printf("other           |%12d       |%12d       |%12hd       \n\n\n",usertotal.totalother,userbudget.other_budget,o);
        o=(o*6)/100*10;
    }
    printf(ColorGreen"============================================================================\n\n"ColorReset);

    
    /*==========Suggestion of budget adjustment==========*/
    if(f+c+tr+e+u+o==0)
        t = (t * 0.9) / 100 * 10;
    else
        t = f + c + tr + e + u + o;
    printf(ColorGreen"======================SUGGESTION OF BUDGET ADJUSTMENT=======================\n"ColorReset);
    printf("                |        now        |  after adjustment  \n");
    if(userbudget.total_budget!=-1)
    printf("total           |%12d       |%12d       \n",userbudget.total_budget,userbudget.total_budget-t);
    if(userbudget.food_budget!=-1)
    printf("food            |%12d       |%12d       \n",userbudget.food_budget,userbudget.food_budget-f);
    if(userbudget.clothing_budget!=-1)
    printf("clothing        |%12d       |%12d       \n",userbudget.clothing_budget,userbudget.clothing_budget-c);
    if(userbudget.transportation_budget!=-1)
    printf("transportation  |%12d       |%12d       \n",userbudget.transportation_budget,userbudget.transportation_budget-tr);
    if(userbudget.entertainment_budget!=-1)
    printf("entertainment   |%12d       |%12d       \n",userbudget.entertainment_budget,userbudget.entertainment_budget-e);
    if(userbudget.utility_budget!=-1)
    printf("utility         |%12d       |%12d       \n",userbudget.utility_budget,userbudget.utility_budget-u);
    if(userbudget.other_budget!=-1)
    printf("other           |%12d       |%12d       \n",userbudget.other_budget,userbudget.other_budget-o);
    printf(ColorGreen"============================================================================\n"ColorReset);
    system("pause");
}

/* to check whether user chooses to set a budget plan,but he didn't set*/
int check_budget2(struct budget userbudget){
    if(userbudget.total_budget==-1&&
        userbudget.food_budget==-1&&
        userbudget.clothing_budget==-1&&
        userbudget.transportation_budget==-1&&
        userbudget.entertainment_budget==-1&&
        userbudget.utility_budget==-1&&
        userbudget.other_budget==-1)
        return 1;
    else return 0;
}

/*show error message*/
void errormsg_for_option4(){
    setTextColor(ColorRed);
    printf("Invalid input!\n");
    system("pause");
    resetTextColor();
    system("CLS");
}

void option2(LLNode *sortedList,Occurence *occurenceList,short year,short month){

    short dayBegin = 0, dayEnd = 0;
    while (1){
        system("CLS");
        dayBegin = 0, dayEnd = 0;
        printf("================================SEARCH================================\n");
        printf("Please enter the "ColorGreen"date interval"ColorReset" you want to view?\n");
        printf("You can input \"back\" to back to previous step.\n");
        printf("Format : <day begin> <day end>\n");
        printf("======================================================================\n");

        char input[100];
        fgets(input, 100, stdin);
        trimString(input);

        /*==========if user enter "back",system will back to menu==========*/
        if (strcmp(input, "back") == 0){
            return;
        }/*================================================================*/


        /*==========split the string to get dayBegin and dayEnd==========*/
        char *split = strtok(input, " ");
        if (split == NULL || !isNumberString(split)) {
            setTextColor(ColorRed);
            printf("Invalid input.\n");
            system("pause");
            resetTextColor();
            continue;
        }
        else dayBegin = toIntValue(split);

        split = strtok(NULL, " ");
        if (split == NULL || !isNumberString(split)){
            errormsg_for_option23();
            continue;
        }
        else dayEnd = toIntValue(split);
        /*================================================================*/


        /*===========================to check if the dates are reasonable===========================*/
        if (checkDate(year, month, dayBegin) == False || checkDate(year, month, dayEnd) == False){
            errormsg_for_option23();
            continue;
        }
        else
            break;
        /*==========================================================================================*/
    }

    keyDataList *keyList= getKeyData(sortedList,occurenceList, -1, dayBegin, dayEnd);   //get data
    if(keyList!=NULL){
        printKeyList(keyList);   //print data
        system("pause");
    }
    else
        option2(sortedList,occurenceList,year,month); 
}

void option3(LLNode *sortedList,Occurence *occurenceList,short year,short month){

    int category_id;
    while(1){
        system("CLS");
        printf("=============================================SEARCH=============================================\n");
        printf("Please enter "ColorGreen"category"ColorReset" you want to view?\n");
        printf("You can input \"back\" to back to previous step.\n\n");
        printf("Category id: [0]food [1]clothing [2]transportation [3]entertainment [4]utility [5]other [6]wage\n");
        printf("Format : <category>\n");
        printf("=================================================================================================\n");

        char input[100];
        fgets(input, 100, stdin);
        trimString(input);
        int len = strlen(input);

        /*==========if user enter "back",system will back to menu==========*/
        if (strcmp(input, "back") == 0)
            return;
        /*=================================================================*/

      
        /*=====if the input contains char(s) which is not numbers, system will print error message=====*/
        if(!isNumberString(input)||len==0){
            errormsg_for_option23();
            continue;
        }/*============================================================================================*/

        /*======check whether the input number >=0 && <=6 ======*/
        category_id = toIntValue(input);
        if(category_id>=0&&category_id<=6)
            break;
        else{
            errormsg_for_option23();
            continue;
        } 
        /*=====================================================*/
    }

    keyDataList *keyList= getKeyData(sortedList,occurenceList, category_id, 0, 0);   //get data
    if(keyList!=NULL){
        printKeyList(keyList);   //print data
        system("pause");
    }
    else
        option3(sortedList,occurenceList,year,month); 
}

void option4(keyDataList *keyList){

    struct budget userbudget;
    int res=0;/*if res==0 means user didn't have a budget plan.  if res==1, user have a budget plan*/

    system("CLS");
    while(1){
        res = 0;
        printf("=====================BUDGET========================\n");
        printf("Do you want your analysis to "ColorGreen"consider budget"ColorReset"?(Y/N)\n");
        printf("You can input \"back\" to back to previous step.\n");
        printf("===================================================\n");

        char input[100];
        fgets(input,100,stdin);
        int len = strlen(input);
        input[len-1] = '\0';
        len = strlen(input);

        /*========== user chooses to set a budget plan ==========*/
        if(strcmp(input,"Y")==0 || strcmp(input,"y")==0){
            res=1;
            askbudget(&userbudget);
            
            if(check_budget2(userbudget)){   /*=deal with the situation user chooses to set a budget plan,but he didn't set=*/
                setTextColor(ColorYellow);
                printf("You didn't set any budget plan!\n");
                system("pause");
                resetTextColor();
                system("CLS");
                continue;
            }
            else break;
        }/*=====================================================*/


        /*========== user doesn't want to set a budget plan ==========*/
        else if(strcmp(input,"N")==0 || strcmp(input,"n")==0)
            break;
        /*============================================================*/


        /*==========if user enter "back",system will back to menu==========*/
        else if(strcmp(input,"back")==0)
            return ; 
        /*=================================================================*/


        /*==========if user input neither "back" nor "y/n" print error message==========*/
        else{
            errormsg_for_option4();
            continue;
        }/*============================================================================*/
    }

    struct total usertotal;
    struct maxima usermaxima;
    
    while(1){      
        month_summary(&usertotal,keyList,&usermaxima);  //print month summary
        printf("============================================ANALYSIS============================================\n");
        printf("[1] Expense analysis (on category)\n");
        if(res==1){
            printf("[2] Get suggestions of budget about next month\n");
        }
        printf("You can input \"back\" to back to previous step.\n");
        printf("================================================================================================\n");

        char input[100];
        fgets(input,100,stdin);
        trimString(input);

        /*==================if user enter "back",system will back to menu=================*/
        if(strcmp(input,"back")==0){
            return;
        }/*================================================================================*/


        else{
            /*=====if the input contains char(s) which is not numbers, system will print error message=====*/
            if(!isNumberString(input)){
                errormsg_for_option4();
                continue;
            }/*============================================================================================*/
            
            int action = toIntValue(input);     
            if(action==1){
                func4_1(usertotal,usermaxima);
                continue;
            }
            else if(action==2&&res==1){
                func4_2(usertotal,userbudget);
                continue;
            }
            else{
                errormsg_for_option4();
                continue;
            }
        }
    }
}
