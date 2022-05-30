#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "spendList.h"
#include "option4_content.h"
#include "word.h"
#include "option4.h"
/* to check whether user chooses to set a budget plan,but he didn't set*/
int check_budget(struct budget userbudget){
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
static void error(){
    printf("Invalid input!\n");
    system("pause");
    system("CLS");
    printf("Please choose again :\n");

}

void option4(keyDataList *keyList){

    int res=0;/*if res==0 means user didn't have a budget plan.  if res==1, user have a budget plan*/
    struct budget userbudget;
    system("CLS");
    while(1){
        printf("Do you want your analysis to consider budget?(Y/N)\n");

        char input[100];
        fgets(input,100,stdin);
        int len = strlen(input);
        input[len-1] = '\0';
        len = strlen(input);

        /*========== user chooses to set a budget plan ==========*/
        if(strcmp(input,"Y")==0 || strcmp(input,"y")==0){
            res=1;
            askbudget(&userbudget);
            
            if(check_budget(userbudget)){   /*=deal with the situation user chooses to set a budget plan,but he didn't set=*/
                printf("You didn't set any budget plan!\n");
                system("pause");
                system("CLS");
                printf("Please choose again :\n");
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
            error();
            continue;
        }/*============================================================================*/
    }

    struct total usertotal;
    struct maxima usermaxima;
    
    while(1){  
        system("CLS");       
        month_summary(&usertotal,keyList,&usermaxima);  //print month summary
        printf("[1] Expense analysis (on category)\n");
        if(res==1){
            printf("[2] Get suggestions of budget about next month\n");
        }

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
                error();
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
                error();
                continue;
            }
        }
    }
}