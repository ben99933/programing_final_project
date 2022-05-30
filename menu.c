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
 * 詢問你要登入或註冊帳號
 * 然後呼叫 account.c 的 login()或signup()
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



//=============================在Tree或list走訪的時候要用到的================================
/**計算該月份的總花費和總共幾筆資料
 * 不會返回值 而是存在intBuffer中
 */ 
deprecated static void traverse_totalSpendCost(DataType type,void* value){
    if(type != SpendType)return;
    Spend* spend = (Spend*)value;
    intBuffer[0] += 1;//共有幾筆紀錄
    intBuffer[1] += spend->cost;//總花費
}
//印出 <year> <month> 只是他是在list或tree在進行遍歷的時候被自動呼叫 
deprecated static void traverse_printYearMonth(DataType type,void* value){
    if(type != Int)return;
    int name = *(int*)value;
    int year = name/100;
    int month = name % 100;
    if(year <= 0 || month <= 0)return;
    printf("%d\t%3d\n",year,month);
}
/**
 * 印出該筆花費的詳細資料 僅在list或tree在進行遍歷的時候被自動呼叫
 */ 
deprecated static void traverse_printSpendDetail(DataType type,void* value){
    if(type!=SpendType)return;
    Spend* spend = (Spend*)value;
    Date* d = &spend->date;
    Date* date = newDate(d->year,d->month,d->day);
    //"Year\tMonth\tDay\tCategory\tCost\tNote"

    printf("%d\t%d\t%d\t%-12s\t%d\t%s\n",date->year,date->month,date->day,toCategoryString(spend->category),spend->cost,spend->note);
    free(date);
}
//=============================================================================================

//====================================一些action會用到的func==================================

//印出所有可用的月份
static void printAllAvailableRecords(){
    system("CLS");
    Tree* tree = getAllRecordName(currentAccount.name);
    printf("========================All Available Records=========================\n");
    printf("Year\tMonth\n");
    tree_inOrder(tree,traverse_printYearMonth);
    tree_destory(tree);
    printf("======================================================================\n");
}

/**
 * 印出這個月的各項消費之概要
 * 未完待續
 */
static void printMonthSummary(int year,int month, boolean hasBudget, int budget){
    LLNode* list = getSpendList(currentAccount.name,year,month);
    clearIntBuffer();
    int amount = 0;
    int total = 0;
    //未完待續
}

/**
 * 印出該月份的詳細花費
 * 如果沒有辦法印出 則返回FALSE
 */
static boolean printfMonthSpendDetail(int year,int month){
    LLNode* listHead = getSpendList(currentAccount.name,year,month);
    debugMsg("test",__FILE__,__LINE__);
    system("CLS");
    if(listHead==NULL){
        printf("Data not found.\n");
        system("pause");
        return False;
    }
    LLNode* focus = listHead;
    printf("================================Detail================================\n");
    printf("Year\tMonth\tDay\tCategory  \tCost\tNote\n");
    while(focus){
        Spend spend = focus->spend;
        Date date = spend.date;
        //"Year\tMonth\tDay\tCategory\tCost\tNote"
        printf("%d\t%d\t%d\t%-12s\t%d\t%s\n",date.year,date.month,date.day,toCategoryString(spend.category),spend.cost,spend.note);
        focus = focus->next;
    }
    printf("======================================================================\n");
    destorySpendList(listHead);
    return True;
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
        if(split == NULL || !isNumberString(split)){
            printf("Invalid input.\n");
            system("pause");
            continue;;
        }else year = toIntValue(split);

        split = strtok(NULL, " ");
        if(split == NULL || !isNumberString(split)){
            printf("Invalid input.\n");
            system("pause");
            continue;
        }else month = toIntValue(split);

        return year*100 + month;
    }
    return 0;
}

//=============================================================================================


//====================================action=======================================
/**新增消費紀錄
 * 用迴圈讓使用者可以輸入多筆
 * 會呼叫recorder.c 的 recordSpend()
 */
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
        if(isDebugMode())printf("string=%s\n",input);
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
        if(checkDate(year,month,day) == False){
            printf("Invalid input.\n");
            system("pause");
            continue;
        }

        if(split == NULL)recordSpend(year,month,day,category,cost,"none",currentAccount.name);
        else recordSpend(year,month,day,category,cost,split,currentAccount.name);
    }
    

}

/**刪除消費紀錄 
 * 先印出可用的月份 printAllAvailableRecords()
 * 然後問你要選哪一個月份 chooseSpend()
 * 接著把所有詳細記錄印出來 printfMonthSpendDetail()
 * 接著輸入要刪除的哪一筆(迴圈) 會呼叫recorder.c 的 removeSpend()
 */
static void removeRecord(){
    printAllAvailableRecords();
    int month = chooseSpend();
    if(month == 0)return;
    if(isDebugMode())printf("Spend=%d\n",month);
    while(True){
        
        if(printfMonthSpendDetail(month/100,month%100) == False)return;
        printf("Which record do you want to delete?\n");
        printf("(You can input \"back\" to exit previous step.)\n");
        printf("Category id: [0]food [1]traffic [2]entertainment [3]shopping\n\n");
        printf("Format : <year> <month> <day> <category id> <cost amount>\n");
        char input[1024] = {'\0'};
        fgets(input,1024,stdin);
        trimString(input);
        if(strcmp(input,"back") == 0)break;

        short year = 0;
        short month = 0;
        short day = 0;
        Category category = 0;
        int cost = 0;

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
        if(split == NULL)removeSpend(year,month,day,category,cost,"none",currentAccount.name);
        else removeSpend(year,month,day,category,cost,split,currentAccount.name);
    }
    
}

//==========================================================================



/**主選單
 * 問使用者要進行哪一個動作 然後呼叫相對應的action
 */
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
            removeRecord();
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