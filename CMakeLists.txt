cmake_minimum_required(VERSION 4.3)
project(TPSIT C)

set(CMAKE_OSX_SYSROOT
        "/Library/Developer/CommandLineTools/SDKs/MacOSX26.5.sdk"
)

set(CMAKE_C_STANDARD 11)

add_executable(TPSIT main.c)

# fork()
add_executable(es1 EsBaseFork/es1.c)
add_executable(es2 EsBaseFork/es2.c)
add_executable(es3 EsBaseFork/es3.c)
add_executable(es4 EsBaseFork/es4.c)

#pipe()
add_executable(pipe1 EsPipe/pipe1.c)
add_executable(pipe2 EsPipe/pipe2.c)
add_executable(pipe3 EsPipe/pipe3.c)

#named pipe()
add_executable(server1 NamedPipe/Es1/server1.c)
add_executable(client1 NamedPipe/Es1/client1.c)
add_executable(server2 NamedPipe/Es2/server2.c)
add_executable(client2 NamedPipe/Es2/client2.c)
add_executable(chatA NamedPipe/Es3/chatA.c)
add_executable(chatB NamedPipe/Es3/chatB.c)

