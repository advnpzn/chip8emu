add_library(chip8emu_renderer_sdl3 STATIC
    ${CMAKE_SOURCE_DIR}/renderer/sdl3/renderer.cpp
)

target_include_directories(chip8emu_renderer_sdl3 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(chip8emu_renderer_sdl3 PRIVATE SDL3::SDL3)