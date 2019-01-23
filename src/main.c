//
// Created by cflaptop on 09/10/18.
//

#include "main.h"

#include "SHA1/SHA1.h"


#include "OptionsHandling/OptionsHandling.h"

int main(int argc, char **argv)
{
	printf("CrackAddict\n");

	bool hashFound=false;
	struct user_options* options = handleOptions(argc,argv);

	char* word = NULL;
	if (options->dictionaryPath != NULL){
		word = parseDictionary(options,&hashFound);
	}
	if (word==NULL){
	        printf("%s%s\n","Attempting to brute force :",options->hashToCrack);
		word = breakMd5Hash(options->hashToCrack,options);
	}

	printf(options->hashToCrack,"is ",word);

	return 0;
}

