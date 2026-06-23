#pragma once

#include "chip8/constants.hpp"

#include <array>
#include <cstdint>

struct Bus {

    std::array<uint8_t, MEMORY_SIZE> memory;
    std::array<bool, DISPLAY_WIDTH * DISPLAY_HEIGHT> display_buffer;
    std::array<bool, KEYPAD_SIZE> keypad;
};