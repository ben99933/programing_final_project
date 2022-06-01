#include "bargraph.h"

double *getExpenseRatio(float *expenseRatioData){
    double *expenseRatio = malloc(sizeof(double) * CATEGORY_COUNT_NO_WAGE);
    for (int i = 0 ; i < CATEGORY_COUNT_NO_WAGE ; i++){
        float expenseRoundToOnePlace = round(expenseRatioData[i]*10);
        expenseRoundToOnePlace /= 10;
        expenseRatio[i] = expenseRoundToOnePlace;
    }
    return expenseRatio;
}



_Bool drawExpenseRatioBarPlot(int categoryCount, double *expenseRatioPercentage, char* filePostfix){
    RGBABitmapImageReference *imageref = CreateRGBABitmapImageReference();
    StringReference *errorMessage = malloc(sizeof(StringReference));

    BarPlotSettings *settings;
    settings = malloc(sizeof(BarPlotSettings));
    settings = GetDefaultBarPlotSettings();

    settings->barPlotSeries = (BarPlotSeries**)malloc(sizeof(BarPlotSeries) * 1.0);
    settings->barPlotSeriesLength = 1.0;
    settings->barPlotSeries[0] = GetDefaultBarPlotSeriesSettings();
    free(settings->barPlotSeries[0]->ys);
    settings->barPlotSeries[0]->ys = expenseRatioPercentage;
    settings->barPlotSeries[0]->ysLength = categoryCount;
    
    settings->width = 1920.0;
    settings->height = 1080.0;
    settings->autoBoundaries = true;
    settings->autoPadding = false;
    settings->yPadding = 125.0;
    settings->xPadding = 150.0;
    settings->title = L"Expense Ratio";
    settings->titleLength = wcslen(settings->title);
    settings->yLabel = L"Ratio(%)";
    settings->yLabelLength = wcslen (settings->yLabel);
    settings->showGrid = true;
    settings->gridColor = GetGray(0.5);
    settings->autoColor = true;
    settings->grayscaleAutoColor = false;
    settings->autoSpacing = false;
    settings->groupSeparation = 175.0;
    settings->barSeparation = 40.0;
    settings->xLabels = (StringReference**)malloc(sizeof(StringReference) * 0.0);
    settings->xLabelsLength = 0.0;
    settings->autoLabels = false;
    settings->xLabels = malloc(sizeof(StringReference) * 6.0);
    settings->xLabels[0] = CreateStringReference(L"FOOD", 4.0);
    settings->xLabels[1] = CreateStringReference(L"CLOTHING", 8.0);
    settings->xLabels[2] = CreateStringReference(L"TRANSPORTATION", 14.0);
    settings->xLabels[3] = CreateStringReference(L"ENTERTAINMENT", 13.0);
    settings->xLabels[4] = CreateStringReference(L"UTILITY", 7.0);
    settings->xLabels[5] = CreateStringReference(L"OTHER", 5.0);
    settings->barBorder = false;
    
    _Bool success = DrawBarPlotFromSettings(imageref, settings, errorMessage);

    if(success){
        size_t length;
        double *pngdata = ConvertToPNG(&length, imageref->image);
        char *filename = malloc(sizeof(char) * (strlen("ExpenseRatio_") + (strlen(filePostfix) + 1)));
        strcpy(filename, "ExpenseRatio_");
        strcat(filename, filePostfix);
        WriteToFile(pngdata, length, filename);
        DeleteImage(imageref->image);
	}else{
        printf("program fails\n");
	    fprintf(stderr, "Graph Error: ");
	    for(int i = 0; i < errorMessage->stringLength; i++){
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n"); 
    }

    return success? 0 : 1;
}