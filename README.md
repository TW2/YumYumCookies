# YYCookies

A small wxWidgets-based desktop application scaffold for YYCookies.

## Build with CMake

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run the application

Linux:

```bash
./build/YYCookies
```

Windows target:

```bash
./build/YYCookies-windows.exe
```

macOS target:

```bash
./build/YYCookies-macos
```

## Run via the provided CMake target

```bash
cmake --build build --target run-YYCookies
```

## Requirements

- CMake
- A C++ compiler
- wxWidgets development libraries
- FFmpeg development headers and libraries (optional, if you want FFmpeg support)

### Example FFmpeg install on Debian/Ubuntu

```bash
sudo apt update
sudo apt install -y libavcodec-dev libavformat-dev libavutil-dev pkg-config
```

### Example FFmpeg install on Windows

Install FFmpeg and set `FFMPEG_DIR` or `FFMPEG_ROOT` to the FFmpeg installation path before configuring CMake.

### Example FFmpeg install on macOS

```bash
brew install ffmpeg
```


- CMake
- A C++ compiler
- wxWidgets development libraries

On Debian/Ubuntu, you can install them with:

```bash
sudo apt update
sudo apt install -y build-essential cmake libwxgtk3.2-dev
```
