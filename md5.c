#include"md5.h"
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
#include"word.h"


//把第32~n個bit放到開頭 但順序沒有顛倒
#define ROTATE_LEFT(x,n) ((x << n) | ( (x&0xFFFFFFFF) >> (32-n) ) )


typedef uint8_t byte;//8bit的bit field
typedef uint32_t byte4;

//md5摘要
typedef struct MD5Digest{
    byte4 h[4];
}MD5Digest;

static MD5Digest* newMD5Digest(){
    MD5Digest* digest = malloc(sizeof(MD5Digest));
    digest->h[0] = 0x67452301;
    digest->h[1] = 0xefcdab89;
    digest->h[2] = 0x98badcfe;
    digest->h[3] = 0x10325476;
    return digest;
}

static const char salt[65] = "nevergonnagiveyouupnevergonnaletyoudownnevergonnarunaroundanddes\0";

/**
 * 在雜湊之前先加點"鹽"
 * 如此一來即便他人從hash還原出來的東東也不會是真正的密碼
 */
static void addSalt(byte* string, int len){
    for(int i = 0;i<len;i++){
        byte c = string[i] ^ salt[i%64];
    }
}

 
/**
 * 步驟 1：填充 一個"1"bit 後面全是"0"
 *  加上一些附加位元（Padding Bits），使得訊息長度除以512餘數為448(448 mod 512)。
 *  如果訊息的長度剛好滿足448 mod 512時，仍必須加入 512 bits 的附加位元。所附加位元的資料除第一個位元為1，其餘皆為0。
 * 步驟 2：紀錄長度
 *  加上 64 bits 長度欄位，其內容表示原訊息的長度，以位元為單位。
 *  如果長度超過 264 個位元，則只取最低 64 位元的資料；亦即 mod 264。
 * 步驟 3：以每 512 bits 為單位，將訊息分割為L個區塊 {P0, P1, .., Pq, …, PL-1}。
 * 步驟 4：將第一區塊（P0）與起始向量（Initial Vector, IV，128 bits）輸入到 MD5 演算法中，
 *  輸出為 CV1（128 bits）；CV1 則作為下一個區塊P1的輸入向量，依此類推。
 * 步驟 5：最後區塊（PL-1）與前一個 CVL-1 經由 MD5 演算後的輸出值，即為該訊息的訊息摘要digest
 */
static MD5Digest* md5(char *string) {
    int len = strlen(string);
    size_t initial_len = strlen(string);
    byte initial_msg[len];
    for(int i = 0;i<len;i++){
        initial_msg[i] = (byte)string[i];
    }
    addSalt(initial_msg,initial_len);//加鹽
    
    // Message (to prepare)
    byte *msg = NULL;

    //第index回合要從第幾個位置去做ROTATE_LEFT
    byte4 r[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };

    // abs[sin(i)] * 4294967296的整數部分 i是弧度 我不知道為啥要這樣 MD5就這樣規定的=_=
    // i = 0~63
    byte4 k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };
    
    MD5Digest* digest = newMD5Digest();
 
    int newLen = ((((initial_len + 8) / 64) + 1) * 64) - 8; //補滿(64的倍數再減8)
 
    msg = calloc(newLen + 64, 1); //(newLen + 64)個"0"bits
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit
 
    byte4 bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + newLen, &bits_len, 4);//在第newLen*8個bit的下一個bit的位置 用4byte紀錄bits_len的值
 

    //以512bit(64byte)為單位把訊息切割成P1 P2... 依次做計算
    int offset;
    for(offset=0; offset<newLen; offset += (512/8)) {
 
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        byte4 *w = (byte4 *) (msg + offset);
        // Initialize hash value for this chunk:
        byte4 a = digest->h[0];
        byte4 b = digest->h[1];
        byte4 c = digest->h[2];
        byte4 d = digest->h[3];
 
        byte4 i;
        for(i = 0; i<64; i++) {
            byte4 f, g;
 
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            //a b c d => d b' b c
            byte4 temp = d;
            d = c;
            c = b;
            b = b + ROTATE_LEFT((a + f + k[i] + w[g]), r[i]);
            a = temp;
        }
 
        //把結果放到digest裡面 然後再跑迴圈
        //第N次的輸出將作為第N+1次的輸入
        digest->h[0] += a;
        digest->h[1] += b;
        digest->h[2] += c;
        digest->h[3] += d;
    }
    
    free(msg);
    return digest;
}

/**
 * 把input變成digest放進hash
 */
 void getDigestString(char* hash,char*input){
    char string[513] = {'\0'};
    int len = strlen(input);
    if(len >= 512)len = 512;
    for(int i = 0;i<len;i++){
        string[i] = input[i];
    }
    MD5Digest* digest = md5(string);
    for(int i = 0;i<16;i++){
        byte4 b1 = digest->h[i/4];
        short times = 3-(i%4);//bit陣列中從"右邊"開始第幾個
        byte4 b2 = b1 >> (times*8);
        b2  = b2 & (0x000f);//musk
        hash[i] = toHexChar(b2);
    }
    hash[16] = '\0';
    free(digest);
}

