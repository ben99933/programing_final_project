#include"account.h"
#include"fileIO.h"
#include<string.h>
#include"dataType.h"
#include"debug.h"
#include"word.h"
#include"md5.h"
#include"color.h"


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
        printf("=============================ACCOUNT ID=====================================\n");
        printf("Please input your "ColorCyan"account id"ColorReset":\n(You can input \"back\" to back to previous step.)\n");
        printf("============================================================================\n");
        char inputID[1024];
        fgets(inputID,1024,stdin);
        trimString(inputID);
        if(strcmp(inputID,"back") == 0){
            return False;
        }
        accountFile = findAccountFile(inputID);
        if(accountFile == NULL){
            setTextColor(ColorYellow);
            printf("The account dose not exist.\n");
            closeFile(accountFile);
            system("pause");
            setTextColor(ColorReset);
        }else{
            int chance = 3;
            printf("\n=============================PASSWORD=======================================\n");
            printf("Please input your " ColorCyan "password" ColorReset ".(You have %d chances.)\n", chance);
            printf("(You can input \"back\" to back to previous step.)\n");
            printf("============================================================================\n");
            while(chance > 0){
                char password[1024];
                char passwordInput[1024];
                fgets(passwordInput,1024,stdin);
                trimString(passwordInput);
                if(isDebugMode())printf("input=%s,len=%d\n",passwordInput,strlen(passwordInput));
                if(isDebugMode())printf("strcmp=%d\n",strcmp(passwordInput,"back"));
                if(strcmp(passwordInput,"back")==0){
                    closeFile(accountFile);
                    accountFile = NULL;
                    return False;
                }
                fgets(password,1024,accountFile);
                
                char hash[17] = {'\0'};
                getDigestString(hash,passwordInput);

                if(isDebugMode())printf("input = %s,len=%d\n",passwordInput,(int)strlen(passwordInput));
                if(isDebugMode())printf("input hash = %s,len=%d\n",hash,(int)strlen(hash));
                if(isDebugMode())printf("password = %s,len=%d\n",password,(int)strlen(password));

                if(strcmp(hash,password) == 0){
                    closeFile(accountFile);
                    changeAccount(inputID,hash);
                    return True;
                }else{
                    chance--;
                    setTextColor(ColorRed);
                    printf("Wrong password!\n");
                    system("pause");
                    resetTextColor();
                    continue;
                }
            }
            setTextColor(ColorYellow);
            printf("You input worng password too many times, please login again.\n");
            system("pause");
            resetTextColor();
        }
    }
    return False;
}
void signUp(){
    boolean canContinue = False;
    while(!canContinue){
        system("CLS");
        printf("======================SET ACCOUNT ID===================================\n");
        printf("Please input your " ColorCyan "account id" ColorReset ".\n\n");
        printf("1.Your id have to " ColorBlue "less than 32 character" ColorReset ".\n");
        printf("2.Your id have to " ColorBlue "begin with english alphabet" ColorReset ".\n");
        printf("3.Your id contains " ColorBlue "only number or english alphabet" ColorReset ".\n");
        printf("(You can input \"back\" to back to previous step.)\n");
        printf("=======================================================================\n");
        char id[1024];
        fgets(id,1024,stdin);
        trimString(id);
        int lenID = strlen(id);
        if(isDebugMode())printf("id=%s,len=%d\n", id,lenID);
        if(strcmp(id,"back")==0)return;
        if(checkID(id) == False){
            setTextColor(ColorRed);
            printf("Invalid format!\n");
            system("pause");
            setTextColor(ColorReset);
            continue;
        }else{
            FILE* accountFile = findAccountFile(id);
            if(accountFile != NULL){
                setTextColor(ColorYellow);
                printf("The Account has existed!\n");
                closeFile(accountFile);
                system("pause");
                setTextColor(ColorReset);
                continue;
            }else closeFile(accountFile);
        }
        system("CLS");
        printf("======================SET PASSWORD=============================\n");
        printf("Please input your " ColorCyan "password" ColorReset ".\n\n");
        printf("1.Your password have to " ColorBlue "less than 32 character" ColorReset ".\n");
        printf("2.Your password contains " ColorBlue "only number or english alphabet" ColorReset ".\n");
        printf("(You can input \"back\" to reinput your id.)\n");
        printf("=================================================================\n");
        char password[1024];
        fgets(password,1024,stdin);
        trimString(password);
        int lenPassword = strlen(password);
        if(isDebugMode())printf("password=%s,len=%d\n",password,lenPassword);
        if(strcmp(password,"back")==0)continue;
        if(checkPassword(password) == False){
            setTextColor(ColorRed);
            printf("Invalid format!\n");
            system("pause");
            setTextColor(ColorReset);
            continue;
        }
        FILE* accountFile = creatAccountFile(id);
        if(accountFile == NULL){
            errorMsg("File Created failed.",__FILE__,__LINE__);
        }
        //密碼雜湊
        char hash[17] = {'\0'};
        getDigestString(hash,password);

        fprintf(accountFile,"%s",hash);
        closeFile(accountFile);
        printf("Your account created.\nPlease login again.\n");
        canContinue = True;
        system("pause");
        
    }
    
}
boolean checkRecorder(const char* accountName){
    FILE* recorder = findRecorderFile(currentAccount.name);
    boolean b = recorder == NULL ? False : True;
    closeFile(recorder);
    return b;
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