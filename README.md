# PsvitaSpot

Modern PS Vita skeleton application using VitaGL with clean architecture.

## Features

- Clean, modular code architecture
- Separated concerns (Application, Renderer, Input)
- Easy to extend and maintain
- VitaGL rendering support
- Controller input handling
- Ready for adding Spotify/ImGui features

## Project Structure

```
PsvitaSpot/
├── include/
│   ├── Application.h      # Main application lifecycle
│   ├── Renderer.h         # VitaGL rendering wrapper
│   ├── InputHandler.h     # Controller input management
│   └── Constants.h        # Configuration constants
├── src/
│   ├── main.cpp           # Entry point
│   ├── Application.cpp    # Application implementation
│   ├── Renderer.cpp       # Renderer implementation
│   └── InputHandler.cpp   # Input handler implementation
└── CMakeLists.txt         # Build configuration
```

## Building

The project uses CMake and requires VitaSDK:

```bash
mkdir build
cd build
cmake ..
make
```

The built VPK will be available in the build directory.

## Controls

- START: Exit application

## Architecture

The application follows a clean architecture pattern:

- **Application**: Manages the main application lifecycle and coordinates between components
- **Renderer**: Handles VitaGL initialization and rendering operations
- **InputHandler**: Manages controller input with support for pressed, held, and released states
- **Constants**: Centralized configuration values

This structure makes it easy to add new features without modifying existing code.
