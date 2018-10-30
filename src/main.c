//
// Created by cflaptop on 09/10/18.
//

#include "main.h"

int main(int argc,char** argv){
    for (int i=0;i<argc;i++)
    {
        printf(argv[i]);
        puts("");
    }
    //TODO handle options

    int stringBlockSize = 100;

    //TODO run self tests if user said to.
//    md5Test();

    //Use all threads on the cpu apart from the one thread for the string generation
    int workerThreadCount =getThreadCount()-1;
    int arrSize = stringBlockSize * workerThreadCount;

    //Array to store pointers to string which will be hashed
    char** strArr = calloc(sizeof(char*),arrSize);
    printf("%s%d%s%d%s\n","Creating an array of ",arrSize," as you have ",(workerThreadCount+1), " threads on your CPU");


    bool hashFound = false;

    struct stringGenArgs* options= malloc(sizeof(struct stringGenArgs));
    options->arr=strArr;
    options->stringBlockSize=stringBlockSize;
    options->workerThreadCount=workerThreadCount;
    options->hashFound=&hashFound;

    pthread_t stringGenThread;
    pthread_create(&stringGenThread,NULL,stringGen,options);

    sleep(2);
    hashFound=true;
    printf("%s%s\n","strArr[10]=",strArr[10]);


    return 0;
}




