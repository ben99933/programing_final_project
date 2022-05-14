#ifndef DATATYPE_H
    #define DATATYPE_H
    #define True 1
    #define False 0
    typedef int boolean;

    /**
     * 關於資料型態的列舉
     * 主要用於一些generic function來判斷這個 void* value 本來是哪一種資料類型
     */
    enum DataType{
        Char, String, Int, Long, Float, Double, Boolean,DateType,SpendType,AccountType
    };
    typedef enum DataType DataType;

    /**
     * 用來暫時存放int的陣列
     * 因為有一些function有使用上的限制 (樹在走訪的時候只會用到該節點的值)
     * 所以如果在這些funciton中使用到intBuffer的話 就可以保留某一些我們想要的int
     * 例如在走訪的時候紀錄最大值 然後其他function可以去取得該最大值
     */
    extern int intBuffer[16];
    
    //清空暫存器
    void clearIntBuffer();
    
    //比對兩個東西的大小(不只適用於數字)
    int compareTo(DataType type,void* object1, void* object2);
    //比對兩個東西是否為相同的值 但不一定要相同的記憶體位置(不只適用於數字)
    boolean isEqualValue(DataType type,void* object1, void* object2);
    //把object2的內容複製到object1
    void copy(DataType type,void* object1,void* object2);
    

    char* newChar(char c);
    int* newInt(int i);
    long long* newLong(long long l);
    float* newFloat(float f);
    double* newDouble(double d);
    boolean* newBool(boolean b);

#endif