#include "md5.h"
//Algo from https://en.wikipedia.org/wiki/MD5#Pseudocode

#define LEFT_ROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))


char* md5String(char *toHash, char *returnAddress) {
    int initial_toHashLen = strlen(toHash);
    char* initial_toHash = malloc(sizeof(char)*(strlen(toHash)));
    strcpy(initial_toHash,toHash);

    assert(!strcmp(toHash,initial_toHash));

    uint32_t s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
                       7, 12, 17, 22, 5,  9, 14, 20,  5,  9, 14, 20,
                       5,  9, 14, 20,  5,  9, 14, 20 ,4, 11, 16, 23,
                       4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
                       6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
                       6, 10, 15, 21 };

    uint32_t K[64] =
            { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee
                    , 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501
                    , 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be
                    , 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821
                    , 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa
                    , 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8
                    , 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed
                    , 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a
                    , 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c
                    , 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70
                    , 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05
                    , 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665
                    , 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039
                    , 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1
                    , 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1
                    , 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
            };


    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    //Calculating how many '0's need to be added to get the message up to the correct length
    uint32_t initBitLen = (initial_toHashLen*8+1);
    uint32_t fullBlocks = (initBitLen)/512; //Storing as int to floor if initBitLen isn't 512 sized
    uint32_t wantedSize = (fullBlocks*512)+448;
    uint32_t newLength = wantedSize-(fullBlocks*512);

    assert(newLength%512==448);
    newLength /= 8;
    //TODO this calculation could be included in the above calculations


    toHash = calloc(newLength + 64, 1); //Allocating area of memory as 0's. This saves appending zeroes as we overlay toHash onto the 0'd area of memory
    /*
    TODO
    append 0's not underlay them.
    Calloc is doing more work than is needed as the part of the array for toHash is initialised twice.
    Could use memset to set area to all 0's then append it
    */

    memcpy(toHash, initial_toHash, initial_toHashLen);
    toHash[initial_toHashLen] = 128;//Append a single bit which is 1 to the string

    uint32_t initialBitLength = initial_toHashLen * 8;
    memcpy(toHash + newLength, &initialBitLength, sizeof(uint32_t)); //Copy the length of the original hash in bits to the end of the hash


    uint32_t offset = 0;
    for (offset = 0; offset < newLength; offset += (512 / 8)) {

        uint32_t* current512Block = (uint32_t* ) (toHash + offset);

        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;

        for (int i=0;i<64;i++){
            uint32_t F,g;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3*i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7*i) % 16;
            }


            //TODO remove D?
            int temp = D;
            D = C;
            C = B;
            B = B + LEFT_ROTATE((A + F + K[i] + current512Block[g]), s[i]);
            A = temp;
        }
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }


    uint8_t* a0ptr = (uint8_t*)&a0;
    uint8_t* b0ptr = (uint8_t*)&b0;
    uint8_t* c0ptr = (uint8_t*)&c0;
    uint8_t* d0ptr = (uint8_t*)&d0;

    snprintf(returnAddress,33,
             "%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x" //Formatting to print 32 chars. Each %2.2x prints two chars
            ,a0ptr[0],a0ptr[1],a0ptr[2],a0ptr[3]
            ,b0ptr[0],b0ptr[1],b0ptr[2],b0ptr[3]
            ,c0ptr[0],c0ptr[1],c0ptr[2],c0ptr[3]
            ,d0ptr[0],d0ptr[1],d0ptr[2],d0ptr[3]
    );


    if (returnAddress[0] != '\0'){
        return returnAddress;
    } else {
        printf("FATAL ERROR. MD5 tried to return NULL value.Exiting...");
        exit(1);
    }
}






