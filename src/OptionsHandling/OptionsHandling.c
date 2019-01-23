//
// Created by cflaptop on 20/01/19.
//

#include "OptionsHandling.h"

void print_help(void){
        printf("help message\n");
}

struct user_options* handleOptions(int argc, char **argv)
{
        struct user_options* options = malloc(sizeof(user_options));
        printf("Parsing command line arguments\n");


        for (int i=1;i<argc;i++){

                if (strcmp("--help",argv[i]) == 0){
                        print_help();
                        exit(0);
                }

                if (argc==2){
                        printf("%s%s\n","One argument passed. Assuming this is the hash to crack: ",argv[1]);
                        options->hashToCrack=argv[1];
                        break;
                }

                if (strcmp("-h",argv[i]) == 0){
                        printf("%s%s\n","CrackAddict will attempt to crack: ",argv[i+1]);
                        options->hashToCrack = argv[i+1];
                }

                if (strcmp("-a",argv[i]) == 0) {
                        printf("%s%s\n","Setting hash algorithm to:",argv[i+1]);
                        options->hashAlgorithm=argv[i+1];
                }

                if ( (strcmp("--size-string",argv[i]) == 0) || (strcmp("-s",argv[i]) == 0 ) ) {
                        uintmax_t num = strtoumax(argv[i+1], NULL, 10);
                        if (num == UINTMAX_MAX && errno == ERANGE) {
                                fprintf(stderr,"%s%s\n", "Invalid stringSizeBlock entered:", argv[i + 1]);
                                exit(1);
                        }else {
                                printf("%s%lu\n","stringSizeBlock set to :",num);
                                options->stringBlockSize=num;
                        }
                }

                if (strcmp("-t",argv[i]) == 0) {
                        uintmax_t num = strtoumax(argv[i+1], NULL, 10);
                        if (num == UINTMAX_MAX && errno == ERANGE) {
                                fprintf(stderr,"%s%s\n", "Invalid thread count entered:", argv[i + 1]);
                                exit(1);
                        }else {
                                if (num<2){
                                        fprintf(stderr,"Program needs at least 2 threads to run. Exiting now...\n");
                                        exit(1);
                                }
                                printf("%s%lu%s\n","Program will run using ",num," threads");
                                options->threadsToUse=num;
                        }
                }

                if (strcmp("-d",argv[i]) == 0){
                        printf("%s%s\n","Dictionary path set as",argv[i+1]);
                        options->dictionaryPath = argv[i+1];
                }
        }

        //Informing the user of result of parsing the arguments
        if (options->hashToCrack == NULL){
                fprintf(stderr,"No hash provided. Exiting now...\n");
                exit(1);
        }
        if (options->hashAlgorithm == NULL){
                printf("No hash algorithm provided. Assuming MD5\n");
                options->hashAlgorithm="MD5";
        }
        if (options->stringBlockSize == (size_t) NULL){
                printf("No string size block provided. Defaulting to 100\n");
                options->stringBlockSize=100;
        }
        if (options->threadsToUse ==(size_t) NULL){
                printf("No amount of threads to use specified. Defaulting to all threads on your CPU.\n");
        }
        if (options->dictionaryPath == NULL){
                printf("No dictionary provided.\n");
        }

        return options;
}
