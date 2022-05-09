#ifndef DATATYPE_H
    #define DATATYPE_H
    #define True 1
    #define False 0
    typedef int boolean;
    
    enum DataType{
        Char, String, Int, Long, Float, Double, Boolean,DateType
    };
    typedef enum DataType DataType;
    
    int compareTo(DataType type,void* object1, void* object2);
    boolean isEqualValue(DataType type,void* object1, void* object2);
    
    char* newChar(char c);
    int* newInt(int i);
    long long* newLong(long long l);
    float* newFloat(float f);
    double* newDouble(double d);
    boolean* newBool(boolean b);

#endif