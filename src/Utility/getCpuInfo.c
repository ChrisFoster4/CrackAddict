//
// Created by cflaptop on 28/10/18.
//

#include "getCpuInfo.h"

#if __linux__
#include <stdio.h>
#include <sys/sysinfo.h>

int getThreadCount(void)
{
	int threadCount = get_nprocs();

	printf("This system has %d processors configured and "
	       "%d processors available.\n",
	       get_nprocs_conf(), get_nprocs());

	return threadCount;
}
#endif

#if __FreeBSD__

int getThreadCount(void){
        int mid[4];
        int coreCount;

        size_t len = sizeof(coreCount);

        mid[0]=CTL_HW;
        mid[1]=HW_NCPU;

        sysctl(mid,2,&coreCount,&len,NULL,0);
        if (coreCount < 1){
        	mid[1]=HW_NCPU;
		sysctl(mid,2,&coreCount,&len,NULL,0);
        	if (coreCount < 1) coreCount=1;
        }
        printf("%s%d%s\n","This system has",coreCount,"  processors avaliable\n");
        return coreCount;
}
#endif
