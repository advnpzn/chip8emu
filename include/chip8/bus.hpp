#pragma once

#include <array>
#include <cstdint>

#include "chip8/constants.hpp"



struct Bus {

    std::array<uint8_t, MEMORY_SIZE> memory;
    std::array<bool, DISPLAY_WIDTH * DISPLAY_HEIGHT> display_buffer;
    std::array<bool, KEYPAD_SIZE> keypad;

};