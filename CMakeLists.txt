cmake_minimum_required(VERSION 4.3)
project(TPSIT C)

set(CMAKE_C_STANDARD 11)

add_executable(TPSIT main.c
        EsBaseFork/es1.c)
