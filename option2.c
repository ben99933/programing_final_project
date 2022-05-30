#include"menu.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"word.h"
#include"spend.h"
#include"option2.h"

void error(){
    printf("Invalid input!\nPlease use the correct input format");
    system("pause");
}

void option2(LLNode *sortedList,Occurence *occurenceList,short year,short month){
    short dayBegin = 0, dayEnd = 0;

    while (1){
        system("CLS");
        dayBegin = 0, dayEnd = 0;
        printf("================================Search================================\n");
        printf("Please enter the date interval you want to view?\n");
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
            printf("Invalid input.\n");
            system("pause");
            continue;
        }
        else dayBegin = toIntValue(split);

        split = strtok(NULL, " ");
        if (split == NULL || !isNumberString(split)){
            error();
            continue;
        }
        else dayEnd = toIntValue(split);
        /*================================================================*/


        /*===========================to check if the dates are reasonable===========================*/
        if (checkDate(year, month, dayBegin) == False || checkDate(year, month, dayEnd) == False){
            error();
            continue;
        }
        else
            break;
        /*==========================================================================================*/
    }   

    keyDataList *keyList= getKeyData(sortedList,occurenceList, -1, dayBegin, dayEnd);   //get data
    printKeyList(keyList);   //print data
}