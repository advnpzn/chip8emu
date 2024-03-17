cmake_minimum_required(VERSION 3.28)
project(chip8emu)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8emu src/main.cpp
        src/chip8.h
        src/chip8.cpp)
