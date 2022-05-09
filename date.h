#ifndef DATE_H
    #define DATE_H
    struct Date;
    typedef struct Date{
        short year;
        short month;
        short day;
    }Date;
    Date* newDate(int year, int month, int day);
    int getDateYear(Date* date);
    int getDateMonth(Date* date);
    int getDateDay(Date* date);
    
#endif