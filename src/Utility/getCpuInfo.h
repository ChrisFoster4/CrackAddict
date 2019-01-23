//
// Created by cflaptop on 28/10/18.
//

#ifndef MD5_GETCPUINFO_H
#define MD5_GETCPUINFO_H
#include <stdio.h>

#if __linux__
#include <sys/sysinfo.h>
#endif

#if __freebsd__
//TODO include
#endif

int getThreadCount(void);
#endif				//MD5_GETCPUINFO_H
