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
        
        //printf("path=%s\n",path);
        accountFile = findAccountFile(input);
        if(accountFile == NULL){
            printf("The account dose not exist.\n");
        }
    }
    
}
void signUp(){

}