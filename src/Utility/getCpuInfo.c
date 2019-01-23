//
// Created by cflaptop on 28/10/18.
//

#include "getCpuInfo.h"

#if __linux__
#include <stdio.h>
#include <sys/sysinfo.h>

//TODO FreeBSD version
int getThreadCount(void)
{
	int threadCount = get_nprocs();

	printf("This system has %d processors configured and "
	       "%d processors available.\n",
	       get_nprocs_conf(), get_nprocs());

	return threadCount;
}
#endif

#if __freebsd__
//TODO FreeBSD version
#endif
