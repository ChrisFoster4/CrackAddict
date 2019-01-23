//
// Created by cflaptop on 29/10/18.
//

#ifndef MD5_WORKERTHREAD_H
#define MD5_WORKERTHREAD_H

#include <stdio.h>
#include <stdbool.h>
#include "../md5/md5.h"

typedef struct workerThreadArgs {
	int *id;
	size_t stringBlockSize;
	char **strArr;
	bool *hashFound;
	char *hashToFind;
	char* returnLocation;
} workerThreadArgs;

void work(struct workerThreadArgs *args);
#endif
