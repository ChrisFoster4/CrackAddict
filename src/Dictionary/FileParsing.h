//
// Created by cflaptop on 07/01/19.
//

#ifndef MD5_FILEPARSING_H
#define MD5_FILEPARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

void parseDictionary(char *filePath, char *hashToFind, bool *hashFound);

typedef struct wordInfo {
    char* word;
    int length;
};
struct wordInfo* extractWord(char* line,int* len);
#endif //MD5_FILEPARSING_H

