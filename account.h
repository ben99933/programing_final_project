#include<stdio.h>
#ifndef ACCOUNT_H
    #define ACCOUNT_H
    typedef struct Account
    {
        char name[64+1];
        char passowrdHash[32+1];
    }Account;
    Account currentAccount;
    void account_init();
    void login();
    void signUp();
    
#endif