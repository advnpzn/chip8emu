//
// Created by advnpzn on 17-03-2024.
//

#ifndef CHIP8_H
#define CHIP8_H

#endif //CHIP8_H

#include <cstdint>
#include <string>
#include <chrono>
#include <random>

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

class Chip8 {
public:
    Chip8();

    uint8_t registers[16]{}; // 0x10
    uint8_t memory[4096]{}; // 0x1000
    uint16_t index{};
    uint16_t pc{0x200}; // Program Counter
    uint16_t stack[16]{}; // Stack
    uint8_t sp{}; // Stack Pointer
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{}; // 16 keys
    uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT]{}; // 64 width x 32 height
    uint16_t opcode{};

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

    void LoadROM(const std::string &filename);

private:

    void OP_00E0(); // Clear the display
    void OP_00EE(); // Return from a subroutine (or) function call
    void OP_1nnn(); // Jump to location (or) address NNN
    void OP_2nnn(); // Call subroutine at location (or) address NNN
    void OP_3xkk();

    void OP_4xkk();

    void OP_5xy0();

    void OP_6xkk();

    void OP_7xkk();

    void OP_8xy0();

    void OP_8xy1();

    void OP_8xy2();

    void OP_8xy3();

    void OP_8xy4();

    void OP_8xy5();

    void OP_8xy6();

    void OP_8xy7();

    void OP_8xyE();

    void OP_9xy0();

    void OP_Annn();

    void OP_Bnnn();

    void OP_Cxkk();

    void OP_Dxyn();

    void OP_Ex9E();

    void OP_ExA1();

    void OP_Fx07();

    void OP_Fx0A();

    void OP_Fx15();

    void OP_Fx18();

    void OP_Fx1E();

    void OP_Fx29();

    void OP_Fx33();

    void OP_Fx55();

    void OP_Fx65();
};
