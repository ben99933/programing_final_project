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

void init(){
    fileIO_init();
    account_init();
}
int main(){
    init();
    login();
    return 0;
}