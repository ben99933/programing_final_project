#include<stdio.h>
#include"dataType.h"
#ifndef ACCOUNT_H
    #define ACCOUNT_H
    typedef struct Account
    {
        char name[32+1];
        char passowrdHash[32+1];
    }Account;
    Account currentAccount;
    void account_init();
    boolean login();
    boolean checkRecorder(const char* accountName);
    void signUp();
    void logout();
    
#endif