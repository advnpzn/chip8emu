//
// Created by avnpzn on 17-03-2024.
//

#include <fstream>
#include "chip8.h"

#include <cstring>

constexpr uint32_t START_ADDRESS = 0x200;
constexpr uint32_t FONTSET_START_ADDRESS = 0x50;
constexpr uint8_t FONTSET_SIZE = 80;

Chip8::Chip8(): randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

    pc = START_ADDRESS;
    const uint8_t fontset[FONTSET_SIZE] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80 // F
    };

    for (uint32_t i = 0; i < FONTSET_SIZE; ++i) {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }
}

void Chip8::LoadROM(const std::string &filename) {
    if (std::ifstream file(filename, std::ios::binary | std::ios::ate); file.is_open()) {
        const std::streampos size = file.tellg();
        auto *buffer = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for (long i = 0; i <= size; ++i) {
            memory[START_ADDRESS + i] = buffer[i];
        }
        delete[] buffer;
    }
}

void Chip8::OP_00E0() {
    memset(video, 0, sizeof(video));
}

void Chip8::OP_00EE() {
    --sp;
    pc = stack[sp];
}

void Chip8::OP_1nnn() {
    const uint16_t address = opcode & 0x0FFFu;
    pc = address;
}

void Chip8::OP_2nnn() {
    const uint16_t address = opcode & 0x0FFFu;

    stack[sp] = pc;
    ++sp;
    pc = address;
}

void Chip8::OP_3xkk() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (const uint8_t byte = opcode & 0x00FFu; registers[Vx] == byte) {
        pc += 2;
    }
}

void Chip8::OP_4xkk() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (const uint8_t byte = opcode & 0x00FFu; registers[Vx] != byte) {
        pc += 2;
    }
}

void Chip8::OP_5xy0() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (const uint8_t Vy = (opcode & 0x00F0u) >> 4u; registers[Vx] == registers[Vy]) {
        pc += 2;
    }
}

void Chip8::OP_6xkk() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t byte = opcode & 0x00FFu;

    registers[Vx] = byte;
}

void Chip8::OP_7xkk() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t byte = opcode & 0x00FFu;

    registers[Vx] += byte;
}

void Chip8::OP_8xy0() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] = registers[Vy];
}

void Chip8::OP_8xy1() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] |= registers[Vy];
}

void Chip8::OP_8xy2() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] &= registers[Vy];
}

void Chip8::OP_8xy3() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    registers[Vx] ^= registers[Vy];
}

void Chip8::OP_8xy4() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    const uint16_t sum = registers[Vx] + registers[Vy];

    if (sum > 255U) {
        registers[0xF] = 1;
    } else {
        registers[0xF] = 0;
    }

    registers[Vx] = sum & 0xFFu;
}

void Chip8::OP_8xy5() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vx] > registers[Vy]) {
        registers[0xF] = 1;
    } else {
        registers[0xF] = 0;
    }

    registers[Vx] -= registers[Vy];
}

void Chip8::OP_8xy6() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    // Save LSB in VF
    registers[0xF] = (registers[Vx] & 0x1u);

    registers[Vx] >>= 1;
}

void Chip8::OP_8xy7() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vy] > registers[Vx]) {
        registers[0xF] = 1;
    } else {
        registers[0xF] = 0;
    }

    registers[Vx] = registers[Vy] - registers[Vx];
}

void Chip8::OP_8xyE() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    // Save MSB in VF
    registers[0xF] = (registers[Vx] & 0x80u) >> 7u;

    registers[Vx] <<= 1;
}

void Chip8::OP_9xy0() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (const uint8_t Vy = (opcode & 0x00F0u) >> 4u; registers[Vx] != registers[Vy]) {
        pc += 2;
    }
}

void Chip8::OP_Annn() {
    const uint16_t address = opcode & 0x0FFFu;

    index = address;
}

void Chip8::OP_Bnnn() {
    const uint16_t address = opcode & 0x0FFFu;

    pc = registers[0] + address;
}

void Chip8::OP_Cxkk() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t byte = opcode & 0x00FFu;

    registers[Vx] = randByte(randGen) & byte;
}

void Chip8::OP_Dxyn() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    const uint8_t height = opcode & 0x000Fu;

    // Wrap if going beyond screen boundaries
    const uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
    const uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;

    registers[0xF] = 0;

    for (unsigned int row = 0; row < height; ++row) {
        const uint8_t spriteByte = memory[index + row];

        for (unsigned int col = 0; col < 8; ++col) {
            const uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t *screenPixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

            // Sprite pixel is on
            if (spritePixel) {
                // Screen pixel also on - collision
                if (*screenPixel == 0xFFFFFFFF) {
                    registers[0xF] = 1;
                }

                // Effectively XOR with the sprite pixel
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void Chip8::OP_Ex9E() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (const uint8_t key = registers[Vx]; keypad[key]) {
        pc += 2;
    }
}

void Chip8::OP_ExA1() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (const uint8_t key = registers[Vx]; !keypad[key]) {
        pc += 2;
    }
}

void Chip8::OP_Fx07() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    registers[Vx] = delayTimer;
}

void Chip8::OP_Fx0A() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    if (keypad[0]) {
        registers[Vx] = 0;
    } else if (keypad[1]) {
        registers[Vx] = 1;
    } else if (keypad[2]) {
        registers[Vx] = 2;
    } else if (keypad[3]) {
        registers[Vx] = 3;
    } else if (keypad[4]) {
        registers[Vx] = 4;
    } else if (keypad[5]) {
        registers[Vx] = 5;
    } else if (keypad[6]) {
        registers[Vx] = 6;
    } else if (keypad[7]) {
        registers[Vx] = 7;
    } else if (keypad[8]) {
        registers[Vx] = 8;
    } else if (keypad[9]) {
        registers[Vx] = 9;
    } else if (keypad[10]) {
        registers[Vx] = 10;
    } else if (keypad[11]) {
        registers[Vx] = 11;
    } else if (keypad[12]) {
        registers[Vx] = 12;
    } else if (keypad[13]) {
        registers[Vx] = 13;
    } else if (keypad[14]) {
        registers[Vx] = 14;
    } else if (keypad[15]) {
        registers[Vx] = 15;
    } else {
        pc -= 2;
    }
}

void Chip8::OP_Fx15() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    delayTimer = registers[Vx];
}

void Chip8::OP_Fx18() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    soundTimer = registers[Vx];
}

void Chip8::OP_Fx1E() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    index += registers[Vx];
}

void Chip8::OP_Fx29() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    const uint8_t digit = registers[Vx];

    index = FONTSET_START_ADDRESS + (5 * digit);
}

void Chip8::OP_Fx33() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t value = registers[Vx];

    // Ones-place
    memory[index + 2] = value % 10;
    value /= 10;

    // Tens-place
    memory[index + 1] = value % 10;
    value /= 10;

    // Hundreds-place
    memory[index] = value % 10;
}

void Chip8::OP_Fx55() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= Vx; ++i) {
        memory[index + i] = registers[i];
    }
}

void Chip8::OP_Fx65() {
    const uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    for (uint8_t i = 0; i <= Vx; ++i) {
        registers[i] = memory[index + i];
    }
}
