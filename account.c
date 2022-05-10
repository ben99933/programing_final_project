#include"account.h"
#include"fileIO.h"
#include<string.h>
#include"encrypt.h"
#include"dataType.h"
#include"debug.h"

static boolean isQualifiedWord(char c){
    int ascii = (int)c;
    if((int)'a' <= ascii && ascii <= (int)'z')return True;
    if((int)'A' <= ascii && ascii <= (int)'Z')return True;
    if((int)'0' <= ascii && ascii <= (int)'9')return True;
    return False;
}

static boolean checkID(char*string){
    int len = strlen(string);
    if(len > 32)return False;
    int ascii = (int)string[0];
    if(!(((int)'a' <= ascii && ascii <= (int)'z') || ((int)'A' <= ascii && ascii <= (int)'Z')))return False;
    for(int i = 0;i<len;i++){
        if(!isQualifiedWord(string[i]))return False;
    }
    return True;
}
static boolean checkPassword(char*string){
    int len = strlen(string);
    if(len > 32)return False;
    int ascii = (int)string[0];
    for(int i = 0;i<len;i++){
        if(!isQualifiedWord(string[i]))return False;
    }
    return True;
}

boolean login(){
    
    FILE* accountFile = NULL;
    while(accountFile == NULL){
        system("CLS");
        printf("Please input your account id:\n(You can input \"back\" to back to previous step.)\n");
        char input[1024];
        fgets(input,1024,stdin);
        input[strlen(input)-1] = '\0';
        if(isDebugMode())
        if(strcmp(input,"back") == 0){
            return False;
        }
        accountFile = findAccountFile(input);
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
                input[strlen(input)-1] = '\0';
                if(strcmp(passwordInput,"back")==0){
                    closeFile(accountFile);
                    accountFile = NULL;
                    continue;
                }
                fgets(password,1024,accountFile);
                if(strcmp(password,passwordInput) == 0){
                    closeFile(accountFile);
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
        char id[1024];
        fgets(id,1024,stdin);
        id[strlen(id)-1] = '\0';
        int lenID = strlen(id);
        if(isDebugMode())printf("id=%s,len=%d\n", id,lenID);
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
        password[strlen(password)-1] = '\0';
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

void account_init(){
    currentAccount.name[0] = '\0';
    currentAccount.passowrdHash[0] = '\0';
}