#ifndef BARGRAPH_H
    #define BARGRAPH_H
    #include "pbPlots.h"
    #include "supportLib.h"
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include "account.h"

    #define CATEGORY_COUNT_NO_WAGE 6
    
    double *getExpenseRatio(float *expesneRatioData);
    _Bool drawExpenseRatioBarPlot(int categoryCount, double *expenseRatioPercentage, char* filePostfix);
    


#endif