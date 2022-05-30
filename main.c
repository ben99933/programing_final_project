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
#include"spendList.h"
#include"md5.h"


//一些東西的初始化
void init(){
    printf("initializing...\n");
    fileIO_init();
    account_init();
    system("CLS");
}

int main(){
    
    init();
    while(True){
        loginOrSingUp();
        onMenu();
    }
    return 0;
}