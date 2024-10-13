# Terminal Fields

Terminal Fields is a 2D game developed using C++ and SFML. Mostly done as a fun project and to dip my toes in C++ :) It runs on Windows Vista and later, and Linux as well, although I don't provide linux binaries yet so you'll have to compile the project yourself for that.

The game loop is currently not finished.

## Getting Started

You can find the latest release in the releases tab, but if you want to, you can compile the code yourself:

### Compiling with CMake under Windows

To compile Terminal Fields, you will need to have CMake and MinGW installed on your system. Follow these steps:

1. **Clone the repository**
```bash
git clone https://github.com/kayrapamukcu/Terminal-Fields.git
cd Terminal-Fields
```
2. **Create a build directory**
```bash
mkdir build
```
3. **Build the project**
```bash
cmake -B build -G "MinGW Makefiles"
cmake --build build
```
The executable should be in `build/bin` now.
You'll also need to copy the assets folder to `build/bin`, otherwise the game will boot to a white screen.

## Music Used
TODO (still figuring out what to use)

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details. 