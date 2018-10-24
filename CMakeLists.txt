cmake_minimum_required(VERSION 3.00)
PROJECT(md5 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -lm ")

add_executable( MD5 src/main.c  src/md5.c src/md5.h )

