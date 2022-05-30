#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "option4_content.h"
#include "option4.h"
#include "spendList.h"
#include "word.h"


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
        printf("Invalid input!\n");
        system("pause");
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
        {                                                       //print warning
            printf("The total budget is less than the sum of all the other types of budget.");
            printf("Please enter the budget again.\n");
            system("pause");
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
        printf("=============================Input_budget=============================\n");
        printf("Above show the menu of budgets you can enter and the amount they are now.\n");
        printf("If you consider the total budget, then total budget most be larger than the sum of all the other types of budgets.\n");
        printf("Please input the coordinating number of the budget you want to set.\n");
        printf("Enter \"back\" when you are done.\n");
        printf("======================================================================\n");
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


        char input[1024];
        fgets(input,1024,stdin);
        trimString(input);

        if(strcmp(input,"back") == 0)               //enter "back" for back to the previous step
        {
            return;
        }
        if(!isNumberString(input))                  //if the input includes non-numerical character, ouput the warning
        {
            printf("Invalid input!\n");
            system("pause");
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
                printf("Enter your total budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
                    printf("Invalid input!\n");
                    system("pause");
                    continue;
                }
                if(strlen(amount) == 0)
                {
                    continue;
                }
                if(toIntValue(amount) < sum)        //if toIntValue(amount) < sum, it's ineligble by the condition we show in menu
                {
                    printf("The total budget is less than the sum of all the other types of budget.");
                    printf("Please enter the budget again.\n");
                    system("pause");
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
                printf("Enter your food budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
                printf("Enter your clothing budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
                printf("Enter your transportation budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
                printf("Enter your entertainment budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
                printf("Enter your utility budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
                printf("Enter your other budget.\n");
                printf("Enter -1 for not consider this budget.\n");
                printf("You can input \"back\" to back to previous step.\n");

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
            printf("Invalid input!\n");
            system("pause");
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
            else if(list->category == other)
            {
                deal_consumption(&(usertotal->totalother), list[i], &(usermaxima->other_max));
            }
        }
    }

    system("CLS");
    printf("Food expense: %d\n", usertotal->totalfood);
    printf("Clothing expense: %d\n", usertotal->totalclothing);
    printf("Transportation expense: %d\n", usertotal->totaltransportation);
    printf("Entertainment expense: %d\n", usertotal->totalentertainment);
    printf("Utility expense: %d\n", usertotal->totalutility);
    printf("Other expense: %d\n", usertotal->totalother);

    printf("\nTotal revenue: %d\n", usertotal->totalwage);
    printf("Total expense: %d\n", usertotal->totalexpense);
    printf("Balance: %d\n", usertotal->totalwage - usertotal->totalexpense);
    system("pause");
}

//func4_1: Calculate proportion and output it.
void func4_1(struct total usertotal,struct maxima usermaxima)
{
    float food_proportion, clothing_proportion, transportation_proportion, entertainment_proportion, utility_proportion, other_proportion;

    //the following variables will store deciamal of the proportaion rounded to the nearest tenth
    food_proportion = (int)((float)usertotal.totalfood / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    clothing_proportion = (int)((float)usertotal.totalclothing / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    transportation_proportion = (int)((float)usertotal.totaltransportation / usertotal.totalexpense * 100 * 10 + 0.5) / 10.0;
    entertainment_proportion = (int)((float)usertotal.totalentertainment / usertotal.totalexpense * 100 * 100 + 0.5) / 10.0;
    utility_proportion = (int)((float)usertotal.totalutility / usertotal.totalexpense * 100 * 100 + 0.5) / 10.0;
    other_proportion = (int)((float)usertotal.totalother / usertotal.totalexpense * 100 * 100 + 0.5) / 10.0;

    system("CLS");
    printf("Proportion:\n");
    printf("food: %.1f%%\n", food_proportion);
    printf("clothing: %.1f%%\n", clothing_proportion);
    printf("transportation: %.1f%%\n", transportation_proportion);
    printf("entertainment: %.1f%%\n", entertainment_proportion);
    printf("utility: %.1f%%\n", utility_proportion);
    printf("other: %.1f%%\n", other_proportion);

    printf("\nHighest cost    |       date        |       cost        |       note        \n");
    print_maxima("food:", usermaxima.food_max);
    print_maxima("clothing:", usermaxima.clothing_max);
    print_maxima("transportation:\n", usermaxima.transportation_max);
    print_maxima("entertainment:", usermaxima.entertainment_max);
    print_maxima("utility:", usermaxima.utility_max);
    print_maxima("other:", usermaxima.other_max);
    system("pause");
}

//func4_2: Ouput the the balance out actual cost and budget. Also give the user suggestion of budget adjustment.
void func4_2(struct total usertotal,struct budget userbudget){
    system("CLS");
    short t=0,f=0,c=0,tr=0,e=0,u=0,o=0;

    /*========== General report of actual cost and budget==========*/
    printf("General report of actual cost and budget :\n");    
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

    
    /*==========Suggestion of budget adjustment==========*/
    t=f+c+tr+e+u+o;
    printf("Suggestion of budget adjustment :\n");
    printf("                |        now        |  after adjustment  \n");
    if(userbudget.total_budget!=-1)
    printf("total           |%12d       |%12d       \n",userbudget.total_budget,userbudget.total_budget+t);
    if(userbudget.food_budget!=-1)
    printf("food            |%12d       |%12d       \n",userbudget.food_budget,userbudget.food_budget+f);
    if(userbudget.clothing_budget!=-1)
    printf("clothing        |%12d       |%12d       \n",userbudget.clothing_budget,userbudget.clothing_budget+c);
    if(userbudget.transportation_budget!=-1)
    printf("transportation  |%12d       |%12d       \n",userbudget.transportation_budget,userbudget.transportation_budget+tr);
    if(userbudget.entertainment_budget!=-1)
    printf("entertainment   |%12d       |%12d       \n",userbudget.entertainment_budget,userbudget.entertainment_budget+e);
    if(userbudget.utility_budget!=-1)
    printf("utility         |%12d       |%12d       \n",userbudget.utility_budget,userbudget.utility_budget+u);
    if(userbudget.other_budget!=-1)
    printf("other           |%12d       |%12d       \n",userbudget.other_budget,userbudget.other_budget+o);
}

