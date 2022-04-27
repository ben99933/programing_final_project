

#ifndef DATATYPE_H
    #define DATATYPE_H
    #define True 1
    #define False 0
    typedef int boolean;
    enum DataType{
        Char, String, Int, Long, Float, Double, Boolean
    };
    typedef enum DataType DataType;
    int compareTo(DataType type,void* object1, void* object2);
    boolean isEqualValue(DataType type,void* object1, void* object2);
#endif