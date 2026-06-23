cmake_minimum_required(VERSION 3.25)

project(chip8emu VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.10
)
FetchContent_MakeAvailable(SDL3)


add_executable(chip8emu
    src/main.cpp
    src/bus.cpp
    src/cpu.cpp
)

target_include_directories(chip8emu PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/renderer/sdl3)

target_link_libraries(chip8emu PRIVATE chip8emu_renderer_sdl3)