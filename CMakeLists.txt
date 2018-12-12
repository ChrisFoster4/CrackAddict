cmake_minimum_required(VERSION 3.00)
PROJECT(md5 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -pedantic -lm -lpthread ")

add_executable(
        MD5
        src/main.c src/main.h
        src/Utility/getCpuInfo.c src/Utility/getCpuInfo.h
        src/workerThread.c src/workerThread.h
        src/StringGeneration/stringGen.c src/StringGeneration/stringGen.h
        src/md5/md5.c src/md5/md5.h
        )
