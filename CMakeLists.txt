cmake_minimum_required(VERSION 4.3)
project(TPSIT C)

set(CMAKE_C_STANDARD 11)

add_executable(TPSIT main.c)
add_executable(es1 EsBaseFork/es1.c)
add_executable(es2 EsBaseFork/es2.c)
add_executable(es3 EsBaseFork/es3.c)
add_executable(es4 EsBaseFork/es4.c)
