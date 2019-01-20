//
// Created by cflaptop on 20/01/19.
//

#ifndef MD5_BREAKMD5HASH_H
#define MD5_BREAKMD5HASH_H

typedef struct breakHashArgs{
    int stringBlockSize;
}breakHashArgs;

char* breakMd5Hash(char* hashToCrack,struct breakHashArgs* args);

#endif //MD5_BREAKMD5HASH_H
