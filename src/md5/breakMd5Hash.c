//
// Created by cflaptop on 20/01/19.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../StringGeneration/stringGen.h"
#include "../WorkerThread/workerThread.h"
#include "../Utility/getCpuInfo.h"

#include "breakMd5Hash.h"

char* breakMd5Hash(char* hashToCrack,struct user_options* args){
        printf("%s%s\n", "Looking for ", hashToCrack);
        bool hashFound = false;

        //Use all threads on the cpu apart from the one thread for the string generation
        unsigned int workerThreadCount =
                (unsigned int) (getThreadCount()) - 1;
	
        //Special case for CPUs with one thread. In this case 1 string generation thread and one cracking thread
        if (workerThreadCount==0) workerThreadCount =1;

        unsigned int arrSize = args->stringBlockSize * workerThreadCount;

        //Array to store pointers to string which will be hashed
        char **strArr = calloc(sizeof(char *), arrSize);
        memset(strArr,(size_t) NULL, (sizeof(char *) * arrSize));
        printf("%s%u%s%u%s\n", "Creating an array of ", arrSize,
               " as you have ", (workerThreadCount + 1),
               " thread(s) on your CPU");


        //Spawning thread to populate the array of strings to hash
        printf("Spawning string generation thread...\n");
        struct stringGenArgs *stringGenThreadArgs = NULL;
        if (!(stringGenThreadArgs = malloc(sizeof(struct stringGenArgs)))) {
                printf("Malloc failed. stringGenThreadArgs\n");
                exit(1);
        }

        stringGenThreadArgs->arr = strArr;
        stringGenThreadArgs->stringBlockSize = args->stringBlockSize;
        stringGenThreadArgs->workerThreadCount = workerThreadCount;
        stringGenThreadArgs->hashFound = &hashFound;

        pthread_t stringGenThread;
        pthread_create(&stringGenThread, NULL, stringGen,
                       stringGenThreadArgs);
        printf("String generation thread spawned.\n");

        //Creating all worker threads (CPU thread count -1)
        pthread_t workerThreads[workerThreadCount];
        struct workerThreadArgs *ptr[workerThreadCount];

        printf("%s%u%s\n", "Creating ", workerThreadCount,
               " worker threads.");
        //Pointer for the word once it has been cracked. Can't return from worker threads
        char* crackedWord=NULL;

        for (unsigned int i = 0; i < workerThreadCount; i++) {
                ptr[i] = malloc(sizeof(struct workerThreadArgs));
                if (ptr[i]==NULL){
                        printf ("Failed to allocated space for workerThreadArgs\n");
                        exit(1);
                }
                ptr[i]->returnLocation=crackedWord;
                ptr[i]->strArr = strArr;
                ptr[i]->stringBlockSize = args->stringBlockSize;

                int *x = malloc(sizeof(int));
                *x = i;
                ptr[i]->id = x;

                ptr[i]->hashToFind = hashToCrack;
                ptr[i]->hashFound = &hashFound;
                printf("%s%d\n", "Creating thread with id:", *x);

                pthread_create(&workerThreads[i], NULL, work, ptr[i]);
        }

        printf("%u%s\n", workerThreadCount, " worker threads created");

        //Waiting for all worker threads to finish
        //Worker threads will finish once hashFound is to true
        for (unsigned int i = 0; i < workerThreadCount; ++i) {
                printf("Waiting for worker threads\n");
                pthread_join(workerThreads[i], NULL);
        }

        //Doesn't frees the space for the pointers not what they point to
        free(strArr);
        return crackedWord;
}

