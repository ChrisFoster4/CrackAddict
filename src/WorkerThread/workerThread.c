//
// Created by cflaptop on 29/10/18.
//

#include "workerThread.h"


void work(struct workerThreadArgs *args)
{
	printf("%s%d\n", "Worker thread started with id:", *(args->id));

	if (*(args->hashToFind) == '\0') {
		printf("No hash to find passed to worker thread");
		exit(1);
	}

	char **startOfBlock =
	    &args->strArr[(*args->id) * (args->stringBlockSize)];

	while (startOfBlock[0] == NULL) {
		printf("%s%d\n", "Waiting for block to populate. Thread:",
		       *(args->id));
	}
	printf("%s%d\n", "Block populated. Thread:", *args->id);

	while (startOfBlock[0] == NULL) {
		printf("%s%d\n", "startOfBlock is null\n in thread:",
		       *(args->id));
	}

	//MD5 hashes are 32 chars long. 1 byte for the null terminator
	//Same char array is reused for every run of md5String
	char str[33];

	while (*args->hashFound == false) {
		printf("%s%d%s\n", "Thread", *args->id, " is waiting...");

		//TODO avoid busy waiting
		while (startOfBlock[0] == NULL);

		if (startOfBlock[99] == NULL) {
			printf("%s%d\n", "preLoop fail with threadID:",
			       *(args->id));
			exit(1);
		}

		printf("%s%d%s\n", "Thread", *args->id,
		       " received more data");
		for (int i = (int)args->stringBlockSize - 1; i >= 0; i--) {
			if (startOfBlock[i] == NULL) {
				printf("%s%d%s%d\n",
				       "startOfBlock is null in thread:",
				       *(args->id), " with i:", i);
				printf("%s%s\n", "startOfBlock[i-1]:",
				       startOfBlock[i - 1]);
				exit(1);
			}
			if (*startOfBlock[i] == '\0') {
				printf("startOfBlock ==\\0 exiting\n");
				exit(1);
			}

			printf("%s%s\n", "Hashing", startOfBlock[i]);
			md5String(startOfBlock[i], str);

			if (strcmp(args->hashToFind, str) == 0) {
				*args->hashFound = true;
				sleep(3);
				printf("%s%s\n", "FOUND. ",
				       startOfBlock[i]);
				printf("%s%s\n", "Hash was:",
				       args->hashToFind);
				args->returnLocation=startOfBlock[i];
				break;
			}
			//Freeing the string pointed to by the pointer at startOfBlock[j]
			free(startOfBlock[i]);
			startOfBlock[i] = NULL;
		}
	}
}
