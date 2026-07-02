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

On Debian/Ubuntu, you can install them with:

```bash
sudo apt update
sudo apt install -y build-essential cmake libwxgtk3.2-dev
```
