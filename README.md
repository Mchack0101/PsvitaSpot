# PsvitaSpot

Modern PS Vita music streaming application skeleton using VitaGL with clean, production-ready architecture.

## Features

- Clean, modular code architecture following SOLID principles
- Separated concerns (Application, Renderer, Input)
- Easy to extend and maintain
- VitaGL rendering support with proper initialization
- Comprehensive controller input handling (pressed, held, released states)
- Analog stick support (left and right)
- Ready for adding Spotify API integration and UI features
- Consistent build configuration (CMake and Makefile)

## Project Structure
PsvitaSpot/
├── include/
│   ├── Application.h       # Main application lifecycle and coordination
│   ├── Renderer.h          # VitaGL rendering wrapper and display management
│   ├── InputHandler.h      # Controller input management with state tracking
│   └── Constants.h         # Configuration constants and display settings
├── src/
│   ├── main.cpp            # Entry point
│   ├── Application.cpp     # Application implementation
│   ├── Renderer.cpp        # Renderer implementation with VitaGL
│   └── InputHandler.cpp    # Input handler implementation
├── CMakeLists.txt          # CMake build configuration
├── Makefile                # Alternative Makefile build system
└── README.md               # This file


## Requirements

- VitaSDK installed and configured
- CMake 3.12 or higher (for CMake builds)
- arm-vita-eabi-g++ toolchain
- Make (for Makefile builds)

## Building

### Using CMake (Recommended)

bash
mkdir build
cd build
cmake ..
make

## Controls

Button	|Action

START	|Exit application

L/R |Analog	Available for future features

Architecture
The application follows a clean architecture pattern with clear separation of concerns:

## Application

Manages the main application lifecycle
Coordinates between Renderer, InputHandler, and future components
Handles the main game loop (Update → Render)
Manages component initialization and shutdown

## Renderer


Wraps VitaGL functionality
Handles display initialization and configuration
Provides clear rendering interface (Clear, Present)
Manages display properties (width, height)

## InputHandler


Manages PS Vita controller input
Tracks button state changes (pressed, held, released)
Provides analog stick values (left and right)
Supports multiple input states per frame

## Constants

Centralized configuration values
Display settings (960x544 resolution, 1024x1024 VRAM)
Application metadata (title, version)
Target FPS settings

## Adding Features

This architecture makes it easy to add new features:
Create a new header in include/ for your feature
Implement in src/ following the existing patterns
Integrate with Application.cpp in the Update or Render methods
Update CMakeLists.txt and Makefile if adding new source files

## Build Configuration


Title ID: PSPOT0001
Resolution: 960x544 (standard PS Vita resolution)
VRAM Allocation: 1024x1024
Standard: C++17

## Troubleshooting


Build fails: Ensure VITASDK is properly installed and $VITASDK environment variable is set
Missing libraries: Verify all VitaSDK libraries are installed
CMake not found: Install CMake with apt-get install cmake

## Future Enhancements

Spotify API integration
ImGui user interface
Music playback functionality
Network functionality
Audio streaming

## License

Music streaming app for PS Vita
