#pragma once

#include "chip8/bus.hpp"
#include "chip8/constants.hpp"

#include <array>
#include <cstdint>

class Cpu {
public:
    Cpu();
    ~Cpu() = default;

    // copy and move not needed, since we are gonna be using one stack allocated cpu object anyways
    Cpu(const Cpu&) = delete;
    Cpu& operator=(const Cpu&) = delete;
    Cpu(Cpu&&) = delete;
    Cpu& operator=(Cpu&&) = delete;

    void step(Bus& bus);

private:
    uint16_t pc;                          // program counter
    uint16_t I;                           // index register
    std::array<uint8_t, NUM_REGISTERS> V; // CHIP-8 general purpose registers (V0 to VF)

    // timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    // stack - could have used cpp stack container, but i'm learning, so it's fun this way...
    std::array<uint16_t, STACK_SIZE> stack;
    uint8_t sp; // stack pointer
};