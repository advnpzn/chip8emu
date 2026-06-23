#pragma once

#include "chip8/constants.hpp"

#include <array>

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void draw(const std::array<bool, DISPLAY_WIDTH * DISPLAY_HEIGHT>& display_buffer) = 0;
    virtual std::array<bool, KEYPAD_SIZE> poll_events() = 0;
    virtual bool should_quit() = 0;
    virtual void set_audio_state(bool playing) = 0;
};