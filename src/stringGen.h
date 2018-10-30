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
typedef struct stringGenArgs{
    char** arr;
    int workerThreadCount;
    int stringBlockSize;
    bool* hashFound;
}stringGenOptions;

void* stringGen(struct stringGenArgs* options);


#endif //MD5_PERMUTE_H
