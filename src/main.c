//
// Created by cflaptop on 09/10/18.
//

#include "main.h"

int main(int argc,char** argv){
    printf("CrackAddict\n");

    //TODO handle args

    char* hashToFind;
    if (!(hashToFind = malloc(sizeof(char)*33))){
        printf("Malloc failed. hashToFind\n");
        exit(1);
    }

    strcpy(hashToFind,"acbd18db4cc2f85cedef654fccc4a4d8");
    printf("%s%s\n","Looking for ",hashToFind);


    bool hashFound=false;

    parseDictionary("src/Dictionary/md5Dict.txt", hashToFind,&hashFound);


    int stringBlockSize = 100;


    md5String("olaaa",hashToFind);
    printf("%s%s\n","Looking for ",hashToFind);

    //Use all threads on the cpu apart from the one thread for the string generation
    unsigned int workerThreadCount =(unsigned int) (getThreadCount())-1;
    unsigned int arrSize = stringBlockSize * workerThreadCount;


    //Array to store pointers to string which will be hashed
    char** strArr = calloc(sizeof(char*),arrSize);
    memset(strArr,NULL,(sizeof(char*)*arrSize));
    printf("%s%u%s%u%s\n","Creating an array of ",arrSize," as you have ",(workerThreadCount+1), " thread(s) on your CPU");


    //Spawning thread to populate the array of strings to hash
    printf("Spawning string generation thread...\n");
    struct stringGenArgs* stringGenThreadArgs= NULL;
    if (!(stringGenThreadArgs = malloc(sizeof(struct stringGenArgs)))){
        printf("Malloc failed. stringGenThreadArgs\n");
        exit(1);
    }

    stringGenThreadArgs->arr=strArr;
    stringGenThreadArgs->stringBlockSize=stringBlockSize;
    stringGenThreadArgs->workerThreadCount=workerThreadCount;
    stringGenThreadArgs->hashFound=&hashFound;

    pthread_t stringGenThread;
    pthread_create(&stringGenThread,NULL,stringGen,stringGenThreadArgs);
    printf("String generation thread spawned.\n");


    //Creating all worker threads (CPU thread count -1)
    pthread_t workerThreads[workerThreadCount];
    struct workerThreadArgs* ptr[workerThreadCount];

    printf("%s%u%s\n","Creating ",workerThreadCount," worker threads.");
    int threadID =0;
    for (int i=0;i<workerThreadCount;i++)
    {
        if (!(ptr[i]=malloc(sizeof(struct workerThreadArgs)))){
            printf("Failed to allocated space for workerThreadArgs\n");
            exit(1);
        }
        ptr[i]->strArr=strArr;
        ptr[i]->stringBlockSize=stringBlockSize;
//        printf("%s%d\n","i=",i);
        int* x = malloc(sizeof(int));
        *x=i;
        ptr[i]->id=x;
        if (*(&i)>8){
            printf("i>8 in main\n");
            exit(1);
        }
        ptr[i]->hashToFind=hashToFind;
        ptr[i]->hashFound=&hashFound;
        printf("%s%d\n","Creating thead with id:",*x);

        pthread_create(&workerThreads[i],NULL,work,ptr[i]);
    }


    printf("%u%s\n",workerThreadCount," worker threads created");

    //Waiting for all worker threads to finish
    //Worker threads will finish once hashFound is to true
    for (unsigned int i=0;i<workerThreadCount;++i)
    {
        printf("Waiting for worker threads\n");
        pthread_join(workerThreads[i],NULL);
    }

    //Doesn't frees the space for the pointers not what they point to
    free(strArr);

    return 0;
}




