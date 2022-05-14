#ifndef DATE_H
    #define DATE_H
    struct Date;
    typedef struct Date{
        short year;
        short month;
        short day;
    }Date;
    Date* newDate(int year, int month, int day);
    
    //本來我打算把Date的成員封裝起來 但是後來發生一些麻煩 所以我還是把這些成員寫在h檔
    //下面這些get functino我就懶得刪掉了
    int getDateYear(Date* date);
    int getDateMonth(Date* date);
    int getDateDay(Date* date);
    
#endif