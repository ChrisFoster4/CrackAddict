//
// Created by cflaptop on 07/01/19.
//

#include "FileParsing.h"


//Parse the dictionary line by line searching for the wanted hash on each line
void parseDictionary(char *filePath, char *hashToFind, bool *hashFound){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filePath, "r");
    if (fp == NULL){
        printf("%s%s\n","Failed to open file: ",filePath);
        exit(EXIT_FAILURE);

    }
    printf("%s%s\n","Reading ",filePath);

    size_t currentLine = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        struct wordInfo* word = extractWord(line,&len);

        if (word==NULL)continue; //Line failed to parse continue to the next line

        //-1 for the \n at the end of the line
        //+1 for the ':'
        size_t lineLength = strlen(line);
        size_t hashLen = (lineLength-1)-(word->length+1);

        char* hash=malloc(sizeof(char) * hashLen);
        memcpy(hash,&line[(word->length+1)],hashLen);

        if ((strcmp(hash,hashToFind))==0){
            printf("%s%lu\n","Hash Found at line ",currentLine);
            printf("%s%s\n","Word is: ",word->word);
            (*hashFound)=true;
            exit(0);

        }
        currentLine++;
    }
    fclose(fp);

    exit(EXIT_SUCCESS);
}


//Parse line up till :
//foo:acbd18db4cc2f85cedef654fccc4a4d8
//Should return foo
struct wordInfo* extractWord(char* line,int* len){

    struct wordInfo* thisWord = malloc(sizeof(struct wordInfo));

    for (int i=0;i<(*len);i++) {
        if (line[i] == ':') {
            thisWord->word=malloc(sizeof(char)*i);

            memcpy(thisWord->word,line,sizeof(char)*i);
            thisWord->length=i;
            return thisWord;
        }
    }
    printf("%s%s%s\n","Failed to parse word from line:\n\"",line,"\" moving on to next line\n");
    return NULL;
}