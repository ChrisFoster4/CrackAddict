//
// Created by cflaptop on 28/10/18.
//

#ifndef MD5_GETCPUINFO_H
#define MD5_GETCPUINFO_H

#if __linux__
#include <stdio.h>
#include <sys/sysinfo.h>

int getThreadCount(void);
#endif

#if __FreeBSD__
#include <stdio.h>
#include <sys/sysctl.h>

int getThreadCount(void);
#endif

#endif				//MD5_GETCPUINFO_H
