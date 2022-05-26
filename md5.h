#include<stdint.h>
#include<stdlib.h>

#ifndef MD5_H
    #define MD5_H
    typedef struct MD5Digest MD5Digest;
    MD5Digest* md5(char *string);
    void getDigestString(char* string,MD5Digest* digest);
    /**
     * 使用範例
     * char *string = "fuck you";
     * MD5Digest* digest = md5((uint8_t*)string,strlen(string));
     * char output[17] = {'\0'};
     * getDigestString(output,digest);
     * printf("digest = %s\n",output);
     */
#endif