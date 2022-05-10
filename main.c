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

void init(){
    printf("initializing...\n");
    fileIO_init();
    account_init();

    system("CLS");
}
int main(){
    init();
    loginOrSingUp();
    return 0;
}