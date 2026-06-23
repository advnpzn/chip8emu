#pragma once

#include "chip8/bus.hpp"
#include "chip8/cpu.hpp"
#include "chip8/renderer.hpp"

#include <filesystem>
#include <memory>

class Chip8 {
public:
    Chip8(std::unique_ptr<IRenderer> renderer);
    ~Chip8() = default;

    Chip8(const Chip8&) = delete;
    Chip8& operator=(const Chip8&) = delete;
    Chip8(Chip8&&) = delete;
    Chip8& operator=(Chip8&&) = delete;

    void load_rom(const std::filesystem::path& path);
    void run();

private:
    Bus bus;
    Cpu cpu;
    std::unique_ptr<IRenderer> renderer;
};