//
// Created by cflaptop on 20/01/19.
//

#ifndef MD5_OPTIONSHANDLING_H
#define MD5_OPTIONSHANDLING_H

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <stdio.h>

typedef struct user_options {
    char* hashToCrack;
    char* hashAlgorithm;
    size_t sizeSizeBlock;
    size_t threadsToUse;
    char* dictionaryPath;
} user_options;


struct user_options* handleOptions(int argc, char **argv);
#endif //MD5_OPTIONSHANDLING_H
