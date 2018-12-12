#include "stringGen.h"


void stringGen(struct stringGenArgs* args)
{
    char** blockStart;
    char charset[26] = {
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p','q',
            'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    int charsetLen = sizeof(charset) / sizeof(char);

    int maxStrLen = 5;
    int rc = 0;
    char* str;
    int* intArr;
    intArr= calloc(sizeof(int),maxStrLen);
    if (intArr==NULL){
        printf("Failed to allocate memory in stringGen\n");
        exit(1);
    }
    while(*(args->hashFound) == false)
    {
        //TODO get values from user via args
        //Only characters within the charset are hashed

        for (char i=0; i < (args->workerThreadCount); i++) {

            //Calculate the address of the block of memory containing strings for thread i
            blockStart = &args->arr[i*args->stringBlockSize];

            //If the first string in a block contains a value then the block is populated
            if (blockStart[0] != NULL) continue;


            // Worker threads check the 1st element of the array to resume work so the [0] element must be populated last
            int genCount;
            for (genCount = (args->stringBlockSize-1); genCount >= 0; genCount--)
            {
                rc = 0;
                str = (char *) calloc(sizeof(char), (maxStrLen + 1));
                if (str==NULL){
                    printf("Failed to allocate memory in stringGen\n");
                    exit(1);
                }
                while (rc < maxStrLen) {
                    str[rc] = charset[intArr[rc]];
                    rc++;
                }

                //Move the address of str into the correct place in the array.
                blockStart[genCount] = str;
                if (strlen(blockStart[genCount])==0){
                    printf("%s%d\n","stringGen generated NULL with i=",i);
                    blockStart[genCount]="ERROR";
                    exit(1);
                }

                rc = 0;
                while (rc < maxStrLen) {
                    if ((intArr[rc]) < charsetLen - 1) {
                        (intArr[rc])++;
                        break;
                    } else {
                        intArr[rc] = 0;
                    }
                    rc++;
                }
            }
        }
    }
    free(intArr);
}
