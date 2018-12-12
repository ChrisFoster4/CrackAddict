//
// Created by cflaptop on 28/10/18.
//

#include "getCpuInfo.h"

<<<<<<< HEAD
#if __linux__
int getThreadCount(void)
{
=======
#include <stdio.h>
#include <sys/sysinfo.h>

//TODO FreeBSD version
int getThreadCount(){

>>>>>>> 1ec9ba67ab657a16dd544317a728118c083ba281
    int threadCount = get_nprocs();

    printf("This system has %d processors configured and "
           "%d processors available.\n",
           get_nprocs_conf(), get_nprocs());

 return threadCount;
}
<<<<<<< HEAD
#endif

#if __freebsd__
//TODO FreeBSD version
#endif


=======
>>>>>>> 1ec9ba67ab657a16dd544317a728118c083ba281
