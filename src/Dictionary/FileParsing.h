//
// Created by cflaptop on 07/01/19.
//

#ifndef MD5_FILEPARSING_H
#define MD5_FILEPARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include "../OptionsHandling/OptionsHandling.h"

char* parseDictionary(struct user_options* options,bool* hashFound);

struct wordInfo {
    char* word;
    size_t length;
};
struct wordInfo* extractWord(char* line,size_t* len);
#endif //MD5_FILEPARSING_H

