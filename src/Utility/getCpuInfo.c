//
// Created by cflaptop on 28/10/18.
//

#include "getCpuInfo.h"

#include <stdio.h>
#include <sys/sysinfo.h>

//TODO FreeBSD version
int getThreadCount(){

    int threadCount = get_nprocs();

    printf("This system has %d processors configured and "
           "%d processors available.\n",
           get_nprocs_conf(), get_nprocs());

 return threadCount;
}
