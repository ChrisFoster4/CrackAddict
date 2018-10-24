//
// Created by cflaptop on 09/10/18.
//
#include <stdbool.h>
#include "md5.h"


int main(){

    //MD5 hashes are 32 chars long. 1 byte for the null terminator
    //Same char array is reused for every run of md5String
    char str[33];
    md5String("foo",str);
    printf("%s%s\n","str in main=",str);
    md5String("potato",str);
    printf("%s%s\n","str in main=",str);

}
