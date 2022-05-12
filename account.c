#include"account.h"
#include"fileIO.h"
#include<string.h>
#include"dataType.h"
#include"debug.h"
#include"word.h"



static boolean checkID(char*string){
    int len = strlen(string);
    if(len > 32)return False;
    if(!isEnglishChar(string[0])){
        errorMsg("開頭沒有英文",__FILE__,__LINE__);
        return False;
    }
    if(!isEnglishWithNumber(string)){
        
        return False;
    }
    return True;
}
static boolean checkPassword(char*string){
    if(isEnglishWithNumber(string))return True;
    return False;
}
static void clearAccount(){
    currentAccount.name[0] = '\0';
    currentAccount.passowrdHash[0] = '\0';
    debugMsg("account is clear now.",__FILE__,__LINE__);
}
static void changeAccount(const char* name,const char* passwordHash){
    strcpy(currentAccount.name,name);
    strcpy(currentAccount.passowrdHash,passwordHash);
    debugMsg("account changed.",__FILE__,__LINE__);
}

/**
 * 登入帳號
 * 回傳登入是否成功
 */
boolean login(){
    
    FILE* accountFile = NULL;
    while(accountFile == NULL){
        system("CLS");
        printf("Please input your account id:\n(You can input \"back\" to back to previous step.)\n");
        char inputID[1024];
        fgets(inputID,1024,stdin);
        trimString(inputID);
        if(strcmp(inputID,"back") == 0){
            return False;
        }
        accountFile = findAccountFile(inputID);
        if(accountFile == NULL){
            printf("The account dose not exist.\n");
            closeFile(accountFile);
            system("pause");
        }else{
            int chance = 3;
            printf("Please input your password.(You have %d chances.)\n",chance);
            printf("(You can input \"back\" to back to previous step.)\n");
            while(chance > 0){
                char password[1024];
                char passwordInput[1024];
                fgets(passwordInput,1024,stdin);
                trimString(passwordInput);
                if(strcmp(passwordInput,"back")==0){
                    closeFile(accountFile);
                    accountFile = NULL;
                    continue;
                }
                fgets(password,1024,accountFile);
                if(isDebugMode())printf("input=%s,len=%d\n",passwordInput,(int)strlen(passwordInput));
                if(isDebugMode())printf("password=%s,len=%d\n",password,(int)strlen(password));
                
                if(strcmp(password,passwordInput) == 0){
                    closeFile(accountFile);
                    changeAccount(inputID,password);
                    return True;
                }else{
                    chance--;
                    printf("Wrong password!\n");
                    system("pause");
                    continue;
                }
            }
            printf("You input worng password too many times, please login again.\n");
            system("pause");
        }
    }
}
void signUp(){
    boolean canContinue = False;
    while(!canContinue){
        system("CLS");
        printf("Please input your account id.\n");
        printf("1.Your id have to less than 32 character.\n");
        printf("2.Your id have to begin with english alphabet.\n");
        printf("3.Your id contains only number or english alphabet.\n");
        printf("(You can input \"back\" to back to previous step.)\n");
        char id[1024];
        fgets(id,1024,stdin);
        trimString(id);
        int lenID = strlen(id);
        if(isDebugMode())printf("id=%s,len=%d\n", id,lenID);
        if(strcmp(id,"back")==0)return;
        if(checkID(id) == False){
            printf("Invalid format!\n");
            system("pause");
            continue;
        }else{
            FILE* accountFile = findAccountFile(id);
            if(accountFile != NULL){
                printf("The Account has existed!\n");
                closeFile(accountFile);
                system("pause");
                continue;
            }else closeFile(accountFile);
        }
        system("CLS");
        printf("Please input your password.\n");
        printf("1.Your password have to less than 32 character.\n");
        printf("2.Your password contains only number or english alphabet.\n");
        printf("(You can input \"back\" to reinput your id.)\n");
        char password[1024];
        fgets(password,1024,stdin);
        trimString(password);
        int lenPassword = strlen(password);
        if(isDebugMode())printf("password=%s,len=%d\n",password,lenPassword);
        if(strcmp(password,"back")==0)continue;
        if(checkPassword(password) == False){
            printf("Invalid format!\n");
            system("pause");
            continue;
        }
        FILE* accountFile = creatAccountFile(id);
        if(accountFile == NULL){
            errorMsg("File Created failed.",__FILE__,__LINE__);
        }

        fprintf(accountFile,"%s",password);
        closeFile(accountFile);
        printf("Your account created.\nPlease login again.\n");
        canContinue = True;
        system("pause");
        
    }
    
}
boolean hasRecord(const char* accountName){
    return False;
}
void logout(){
    clearAccount();
    system("CLS");
    printf("You logged out.\n");
    system("pause");
}
/**
 * 把帳號的一些功能給初始化
 * 在初始化階段時呼叫
 */
void account_init(){
    clearAccount();
}