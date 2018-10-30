#include "stringGen.h"


void* stringGen(struct stringGenArgs* options)
{
    printf("stringGen called\n");
    printf("%s%d\n","hashFound pre loop =",*(options->hashFound));
    int stringBlockSize=options->stringBlockSize;
    char** arr=options->arr;

    char** blockStart;
    while(*(options->hashFound) == false)
    {
        for (unsigned int i=0;i<options->workerThreadCount;i++) {
            //Calculate the address of the current stringSizeBlock
            blockStart = arr + (i * stringBlockSize);

            //If the start of a block contains a value then the block is populated
            if (blockStart[i] != '\0') {
//                printf("%s%d%s\n", "String block", i, "is populated");
                continue;
            }
//            printf("%s%d%s\n", "string block", i, " is empty. Populating now...");

            char charset[4] = {'a', 'b', 'c', 'd'}; //TODO get values from user
            int charsetLen = sizeof(charset) / sizeof(char);

            int maxStrLen = 5;
            int rc = 0;
            char *str;
            int *intArr = malloc(sizeof(int) * maxStrLen);

            for (int genCount = 0; genCount <= stringBlockSize; genCount++) {
                rc = 0;
                str = (char *) calloc(sizeof(char), (maxStrLen + 1));
                while (rc < maxStrLen) {
                    str[rc] = charset[intArr[rc]];
                    rc++;
                }

                //Move the address of str into the correct place in the array.
                blockStart[genCount] = str;
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
}
