//
// Created by cflaptop on 09/10/18.
//

#include "main.h"

#include "SHA1/SHA1.h"



int main(int argc, char **argv)
{
	printf("CrackAddict\n");

	char *hashToFind;
	if (!(hashToFind = malloc(sizeof(char) * 33))) {
		printf("Malloc failed. hashToFind\n");
		exit(1);
	}

	strcpy(hashToFind, "acbd18db4cc2f85cedef654fccc4a4d8");
	printf("%s%s\n", "Looking for ", hashToFind);


	struct breakHashArgs* breakArgs = malloc(sizeof(breakHashArgs));
	breakArgs->stringBlockSize=100;

	breakMd5Hash(hashToFind,breakArgs);

	return 0;
}

