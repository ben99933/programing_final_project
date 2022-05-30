#ifndef COLOR_H
    #define COLOR_H

    /**
     * 如果你要直接調用這些Color在printf裡面的話
     * 利用 "string" <color> "string2"的特性
     * printf("This is " RED "red" RESET " and this is " BLU "blue" RESET "\n");
     * 
     */
    #define ColorRed "\x1B[31m"
    #define ColorGreen "\x1B[32m"
    #define ColorYelow "\x1B[33m"
    #define ColorBlue "\x1B[34m"
    //洋紅色
    #define ColorMagenta "\x1B[35m"
    //青色
    #define ColorCyan   "\x1B[36m"
    #define ColorWhite   "\x1B[37m"
    #define ColorReset "\x1B[0m"

    

    /**
     * 把接下來printf的字都變成該顏色
     * 要自己call reserTextColor調回來
     * 
     * 使用範例:
     * setTextColor(ColorRed);
     * resetTextColor();
     */
    void setTextColor(const char* colorFormat);
    
    /**
     * 把顏色改回來
     * 跟setTextColor(ColorReset);
     */
    void resetTextColor();
#endif