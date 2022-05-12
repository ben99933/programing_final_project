#include"menu.h"
#include"dataType.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"account.h"
#include"debug.h"
#include"word.h"


/**
 * @brief 詢問你要登入或註冊帳號
 * 
 */
void loginOrSingUp(){
    boolean canContiune = False;
    printf("Hello,user.\n");
    system("pause");
    while(!canContiune){
        system("CLS");
        printf("Do you had have an account? [Y/n]\n");
        printf("(You can input \"exit\" to close the program.)\n");
        char input[1024];
        fgets(input,1024,stdin);
        int len = strlen(input);
        input[len-1] = '\0';
        len = strlen(input);
        if(isDebugMode())printf("input=%s,len=%d\n",input,len);
        //對比輸入之文字
        if(len == 0 || strcmp(input,"Y")==0 || strcmp(input,"y")==0){
            //登入
            canContiune = login();
            if(canContiune){
                printf("Login successed!\n");
                system("pause");
                system("CLS");
            }
        }else if(strcmp(input,"N")==0 || strcmp(input,"n")==0){
            //詢問是否註冊
            printf("Do you want to sign up an account?[Y/n]\n");
            char input2[1024];
            fgets(input2,1024,stdin);
            int len2 = strlen(input2);
            input2[len2-1] = '\0';
            len = strlen(input2);
            if(len==0 || strcmp(input,"Y")==0 || strcmp(input,"y")==0)signUp();
            else if(strcmp(input,"N")==0 || strcmp(input,"n")==0)continue;
            else {
                printf("Invaild input!\n");
                continue;
            }
        }else if(strcmp(input,"debug") == 0){
            //開啟DEBUG模式 這個功能使用者不會知道的~~嘻嘻
            debugOn();
            system("pause");
        }else if(strcmp(input,"exit")==0){
            //退出程式
            exit(0);
        }else{
            printf("Invalid input!\n");
            system("pause");
        }
    }
}
static void addRecord(){
    system("CLS");
    printf("==========Record==========\n");
}

void onMenu(){
    if(hasRecord(currentAccount.name) == False){

    }
    while(True){
        system("CLS");
        printf("Wellcome, %s.\n",currentAccount.name);
        printf("What do you want to do?\n");
        printf("Plase input the coordinating number.\n");
        printf("[0] Adding consumption  record.\n");
        printf("[1] Remove consumption record.\n");
        printf("[2] Search certain record according to date.\n");
        printf("[3] Search certain record according to category.\n");
        printf("[4] Consumption analysis.\n");
        printf("[5] exit.\n");
        printf("[6] log out.\n");

        char inputString[1024];
        fgets(inputString,1024,stdin);
        trimString(inputString);
        if(!isNumberString(inputString)){
            printf("Invalid input!\n");
            continue;
        }
        int action = toIntValue(inputString);
        if(action == 0){

        }
    }
}