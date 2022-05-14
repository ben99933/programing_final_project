#include"menu.h"
#include"dataType.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"account.h"
#include"debug.h"
#include"word.h"
#include"spend.h"
#include"recorder.h"


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
    
    while(True){
        system("CLS");
        printf("================================Record================================\n");
        printf("Please your consumption record.\n");
        printf("(You can input \"back\" to exit previous step.)\n");
        printf("Category id: [0]food [1]traffic [2]entertainment [3]shopping\n\n");
        printf("Format : <year> <month> <day> <category id> <cost amount> <notes>\n");
        printf("======================================================================\n");
        char input[1024] = {'\0'};
        short year = 0;
        short month = 0;
        short day = 0;
        Category category = 0;
        int cost = 0;
        fgets(input,1024,stdin);
        
        trimString(input);
        if(strcmp(input,"back") == 0)return;
        char* split;
        split = strtok(input," ");
        if(split != NULL && isNumberString(split))year = toIntValue(split);
        else{
            printf("Invalid input.\n");
            system("pause");
            continue;
        }

        split = strtok(NULL," ");
        if(split != NULL && isNumberString(split))month = toIntValue(split);
        else{
            printf("Invalid input.\n");
            system("pause");
            continue;
        }

        split = strtok(NULL," ");
        if(split != NULL && isNumberString(split))day = toIntValue(split);
        else{
            printf("Invalid input.\n");
            system("pause");
            continue;
        }

        split = strtok(NULL," ");
        if(split != NULL && isNumberString(split))category = toCategory(toIntValue(split));
        else{
            printf("Invalid input.\n");
            system("pause");
            continue;
        }

        split = strtok(NULL," ");
        if(split != NULL && isNumberString(split))cost = toIntValue(split);
        else{
            printf("Invalid input.\n");
            system("pause");
            continue;
        }

        split = strtok(NULL," ");
        if(split == NULL)recordSpend(year,month,day,category,cost,"none",currentAccount.name);
        else recordSpend(year,month,day,category,cost,split,currentAccount.name);
    }
    

}
static void totalSpendCost(DataType type,void* value){
    if(type != SpendType)return;
    Spend* spend = (Spend*)value;
    intBuffer += spend->cost;
}
//在Tree或list走訪的時候要用到的
static void traverse_printYearMonth(DataType type,void* value){
    if(type != Int)return;
    int name = *(int*)value;
    int year = name/100;
    int month = name % 100;
    if(year <= 0 || month <= 0)return;
    printf("%d\t%3d\n",year,month);
}
static void traverse_printSpendDetail(DataType type,void* value){
    if(type!=SpendType)return;
    Spend* spend = (Spend*)value;
    Date* date = spend->date;
    //"Year\tMonth\tDay\tCategory\tCost\tNote"
    char categoryString[1024] = {'\0'};
    toCategoryString(categoryString,spend->category);
    printf("%d\t%d\t%d\t%s\t%d\t%s",date->year,date->month,date->day,categoryString,spend->cost,spend->note);
}

//印出所有可用的月份
static void printAllAvailableRecords(){
    system("CLS");
    Tree* tree = getAllRecordName(currentAccount.name);
    printf("========================All Available Records=========================\n");
    printf("Year\tMonth\n");
    tree_inOrder(tree,traverse_printYearMonth);
    tree_destory(tree);
    printf("======================================================================\n");
    system("pause");
}

/**
 * 印出這個月的各項消費之概要
 * 未完待續
 */
static void printMonthSummary(int year,int month, boolean hasBudget, int budget){
    LinkedList* list = getSpendList(currentAccount.name,year,month);
    system("CLS");
    printf("================================Summary===============================\n");
    printf("Total Expenses : %d\n");
    printf("----------------------------------------------------------------------\n");
    printf("======================================================================\n");
    system("pause");
    list_destory(list);
    free(list);
}
static void printfMonthSpendDetail(int year,int month){
    LinkedList* list = getSpendList(currentAccount.name,year,month);
    system("CLS");
    printf("================================Detail================================\n");
    printf("Year\tMonth\tDay\tCategory\tCost\tNote");
    linkedList_traverse(list,traverse_printSpendDetail);
    printf("======================================================================\n");
    system("pause");
}

/**詢問要選哪一個月
 * 返回一個6位數數字
 * 前四位數為年份 十位數和個位數為月份
 * EX : 202205
 * 如果回傳0表示退出
 */
static int chooseSpend(){
    while(True){
        printf("Which month do you want to choose?\n");
        printf("You can input \"back\" to back to previous step.\n");
        printf("Format : <year> <month>\n");

        char input[1024];
        fgets(input,1024,stdin);
        trimString(input);

        if(strcmp(input,"back") == 0)return 0;
        char* split = strtok(input, " ");
        int year = 0;
        int month = 0;
        if(isNumberString(split) == True)year = toIntValue(split);
        else{
            printf("Invalid input!.\n");
            continue;
        }
        split = strtok(NULL, " ");
        if(isNumberString(split) == True)month = toIntValue(split);
        else{
            printf("Invalid input!.\n");
            continue;
        }
        return year*100 + month;
    }
    return 0;
}

static void removeSpend(){
    printAllAvailableRecords();
    int month = chooseSpend();
    if(month == 0)return;
    if(isDebugMode())printf("Spend=%d\n",month);
    printfMonthSpendDetail(month/100,month%100);
}

void onMenu(){
    while(True){
        system("CLS");
        printf("Wellcome, %s.\n",currentAccount.name);
        printf("What do you want to do?\n");
        printf("Plase input the coordinating number.\n");
        printf("[0] Adding consumption record.\n");
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
            system("pause");
            continue;
        }
        if(strlen(inputString) == 0)continue;
        int action = toIntValue(inputString);
        if(action == 0){
            addRecord();
        }else if(action == 1){
            removeSpend();
        }else if(action == 2){

        }else if(action == 3){

        }else if(action == 4){
            
        }else if(action == 5){
            exit(0);
        }else if(action == 6){
            logout();
            return;
        }else{
            printf("Invalid input!\n");
            system("pause");
            continue;
        }
    }
}