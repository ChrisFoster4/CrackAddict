//
// Created by cflaptop on 27/10/18.
//


#ifndef MD5_PERMUTE_H
#define MD5_PERMUTE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct stringGenArgs {
    char** arr;
    unsigned int workerThreadCount;
    int stringBlockSize;
    bool* hashFound;
} stringGenArgs;

void stringGen(struct stringGenArgs* options);

#endif //MD5_PERMUTE_H
