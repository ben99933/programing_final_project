#include"account.h"
#include"fileIO.h"
#include<string.h>
#include"encrypt.h"


void account_init(){
    currentAccount.name[0] = '\0';
    currentAccount.passowrdHash[0] = '\0';
}

void login(){
    int chance = 3;
    FILE* accountFile = NULL;
    while(accountFile == NULL){
        printf("Please input your account:\n");
        char input[1024];
        fgets(input,1024,stdin);
        input[strlen(input)-1] = '\0';
        char path[1024];
        strcat(path,getAccountPath());
        strcat(path,input);
        strcat(path,".txt");
        //printf("path=%s\n",path);
        accountFile = findFile(path);
        if(accountFile == NULL){
            printf("The account dose not exist.\n");
        }
    }
    
}
void signUp(){

}