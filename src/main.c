//
// Created by cflaptop on 09/10/18.
//

#include "main.h"

#include "SHA1/SHA1.h"


#include "OptionsHandling/OptionsHandling.h"

int main(int argc, char **argv)
{
	printf("CrackAddict\n");

	struct user_options* options = handleOptions(argc,argv);

	return 0;
}

