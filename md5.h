#include<stdint.h>
#include<stdlib.h>

#ifndef MD5_H
    #define MD5_H

    /**
     * 把string 變成一個16字元的字串放到hash
     * 使用範例
     * char *string = "never gonna give you up";
     * char hash[17] = {'\0'};
     * getDigestString(hash,string);
     * printf("digest = %s\n",hash);
     */
    void getDigestString(char* hash,char*string);
#endif