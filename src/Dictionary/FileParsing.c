//
// Created by cflaptop on 07/01/19.
//

#include "FileParsing.h"


//Parse the dictionary line by line searching for the wanted hash on each line
char* parseDictionary(struct user_options* options,bool* hashFound)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(options->dictionaryPath, "r");
	if (fp == NULL) {
		printf("%s%s\n", "Failed to open file: ", options->dictionaryPath);
		exit(EXIT_FAILURE);

	}
	printf("%s%s\n", "Reading ", options->dictionaryPath);

	size_t currentLine = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		struct wordInfo* word = extractWord(line, &len);

		if (word == NULL)
			continue;	//Line failed to parse continue to the next line

		//-1 for the \n at the end of the line
		//+1 for the ':'
		size_t lineLength = strlen(line);
		size_t hashLen = (lineLength - 1) - (word->length + 1);

		char *hash = malloc(sizeof(char) * hashLen);
		memcpy(hash, &line[(word->length + 1)], hashLen);

		if ((strcmp(hash, options->hashToCrack)) == 0) {
			printf("%s%lu\n", "Hash Found at line ",
			       currentLine);
			printf("%s%s\n", "Word is: ", word->word);
			(*hashFound) = true;
			return word->word;
		}
		currentLine++;
	}
	fclose(fp);
	printf("Hash not found in dictionary\n");

	return NULL;
}


//Parse line up till :
//foo:acbd18db4cc2f85cedef654fccc4a4d8
//Should return foo
struct wordInfo *extractWord(char *line, size_t *len)
{

	struct wordInfo *thisWord = malloc(sizeof(struct wordInfo));

	for (unsigned int i = 0; i < (*len); i++) {
		if (line[i] == ':') {
			thisWord->word = malloc(sizeof(char) * i);

			memcpy(thisWord->word, line, sizeof(char) * i);
			thisWord->length = i;
			return thisWord;
		}
	}
	printf("%s%s%s\n", "Failed to parse word from line:\n\"", line,
	       "\" moving on to next line\n");
	return NULL;
}
