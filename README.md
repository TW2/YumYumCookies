# YYCookies

A small wxWidgets-based desktop application scaffold for YYCookies.

## Build with CMake

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run the application

```bash
./build/YYCookies
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
