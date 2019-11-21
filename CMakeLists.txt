cmake_minimum_required(VERSION 3.00)
PROJECT(MD5Cracker)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -pedantic -lm -pthread ")

add_executable(
	MD5Cracker
        src/main.c src/main.h
        src/Utility/getCpuInfo.c src/Utility/getCpuInfo.h
        src/WorkerThread/workerThread.c src/WorkerThread/workerThread.h
        src/StringGeneration/stringGen.c src/StringGeneration/stringGen.h
        src/md5/md5.c src/md5/md5.h
        src/Dictionary/FileParsing.c src/Dictionary/FileParsing.h
       	src/md5/breakMd5Hash.c src/md5/breakMd5Hash.h
	src/OptionsHandling/OptionsHandling.c src/OptionsHandling/OptionsHandling.h
	)
