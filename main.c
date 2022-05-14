#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"linkedList.h"
#include"dataType.h"
#include"debug.h"
#include"date.h"
#include"tree.h"
#include"fileIO.h"
#include"account.h"
#include"menu.h"
#include"spend.h"

void init(){
    printf("initializing...\n");
    fileIO_init();
    account_init();
    system("CLS");
}
static void print(DataType type, void* value){
    Spend* spend = (Spend*)value;
    printf("%d %d %d %d %d %s\n",spend->date->year,spend->date->month,spend->date->day,spend->category,spend->cost,spend->note);
}
int main(){
    init();
    while(True){
        loginOrSingUp();
        onMenu();
    }
    return 0;
}