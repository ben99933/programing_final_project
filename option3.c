#include"menu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"
#include"spend.h"
#include"option3.h"

void error(){
    printf("Invalid input!\nPlease use the correct input format");
    system("pause");
}


void option3(LLNode *sortedList,Occurence *occurenceList,short year,short month){
    system("CLS");
    int category_id;

    while(1){
        system("CLS");
        printf("=============================================Search=============================================\n");
        printf("Please enter category you want to view?\n");
        printf("You can input \"back\" to back to previous step.\n");
        printf("Category id: [0]food [1]clothing [2]transportation [3]entertainment [4]utility [5]other [6]wage\n\n");
        printf("Format : <category>\n");
        printf("=================================================================================================\n");

        char input[100];
        fgets(input, 100, stdin);
        trimString(input);

        /*==========if user enter "back",system will back to menu==========*/
        if (strcmp(input, "back") == 0)
            return;
        /*=================================================================*/

      
        /*=====if the input contains char(s) which is not numbers, system will print error message=====*/
        if(!isNumberString(input)){
            error();
            continue;
        }/*============================================================================================*/

        /*======check whether the input number >=0 && <=6 ======*/
        category_id = toIntValue(input);
        if(category_id>=0&&category_id<=6)
            break;
        else{
            error();
            continue;
        } 
        /*=====================================================*/
    }

    keyDataList *keyList= getKeyData(sortedList,occurenceList, category_id, 0, 0);   //get data
    printKeyList(keyList);   //print data
}