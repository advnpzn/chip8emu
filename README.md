# chip8emu

Yet another CHIP-8 emulator.

## Prerequisites

### Fedora (40+)

```bash
sudo dnf install gcc git-core make cmake \
    alsa-lib-devel fribidi-devel pulseaudio-libs-devel pipewire-devel \
    libX11-devel libXext-devel libXrandr-devel libXcursor-devel libXfixes-devel \
    libXi-devel libXScrnSaver-devel libXtst-devel dbus-devel ibus-devel \
    systemd-devel mesa-libGL-devel libxkbcommon-devel mesa-libGLES-devel \
    mesa-libEGL-devel vulkan-devel wayland-devel wayland-protocols-devel \
    libdrm-devel mesa-libgbm-devel libusb1-devel libdecor-devel \
    pipewire-jack-audio-connection-kit-devel libthai-devel \
    liburing-devel zlib-ng-compat-static
```

### Ubuntu 22.04+

```bash
sudo apt-get install build-essential git make \
    pkg-config cmake ninja-build libasound2-dev libpulse-dev \
    libaudio-dev libfribidi-dev libjack-dev libx11-dev libxext-dev \
    libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
    libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
    libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev \
    libusb-1.0-0-dev libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev
```

> SDL3 is fetched automatically via CMake FetchContent — no manual SDL install needed.

## Building

```bash
git clone https://github.com/youruser/chip8emu.git
cd chip8emu
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

For a debug build:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j$(nproc)
```

## Running

```bash
./build/chip8emu path/to/rom.ch8
```

ROM files can be found at [chip8Archive](https://johnearnest.github.io/chip8Archive/) or [dmatlack/chip8](https://github.com/dmatlack/chip8/tree/master/roms).

## Renderer Backends

The default renderer is SDL3. To switch backends, pass the renderer option at configure time:

```bash
cmake -B build -DCHIP8_RENDERER=terminal
```

Available backends: `sdl3`, `terminal`.