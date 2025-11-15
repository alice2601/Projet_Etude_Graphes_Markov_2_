cmake_minimum_required(VERSION 3.30)
project(untitled10 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled10 main.c fonction.c
        cmake-build-debug/utils.c
        cmake-build-debug/utils.h
        cmake-build-debug/hasse.c
        cmake-build-debug/hasse.h
        cmake-build-debug/stack.c
        cmake-build-debug/stack.h
        cmake-build-debug/tarjan.c
        cmake-build-debug/tarjan.h
        cmake-build-debug/mermaid_partie2.c
        cmake-build-debug/mermaid_partie2.h
)
