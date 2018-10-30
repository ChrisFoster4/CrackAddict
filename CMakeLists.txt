cmake_minimum_required(VERSION 3.00)
PROJECT(md5 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -lm -lpthread ")

add_executable(
        MD5
        src/main.c src/main.h
        src/Utility/getCpuInfo.c src/Utility/getCpuInfo.h
        src/stringGen.c src/stringGen.h
        src/md5.c src/md5.h
        )

