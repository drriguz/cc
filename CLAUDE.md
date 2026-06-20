# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

An incomplete 2D/isometric tile-based game engine in C++11 using SDL2 and TMX (Tiled Map Editor) maps. The project has basic rendering, a player with sprite animation, and map loading, but no gameplay mechanics, collision, audio, or UI.

## Build

Uses CMake. To build:

```bash
cmake -B build
cmake --build build
```

Run from the project root (assets are referenced via `ASSET_DIR` compile definition):

```bash
./build/cc
```

**Prerequisites:** C++11 compiler, CMake 3.10+, and these libraries:
- `libSDL2`, `libSDL2_image`, `libSDL2_ttf`, `libSDL2_mixer`
- `libtmx` (TMX map parser library)

Install on macOS: `brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer tmx pkg-config`
Install on Ubuntu: `sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libtmx-dev pkg-config`

There are no tests.

## Project Structure

```
├── CMakeLists.txt
├── src/
│   ├── main.cpp           # Entry point
│   ├── game.h/cpp         # Game class (SDL init, main loop, input)
│   ├── object.h/cpp       # Base entity with static registry
│   ├── player.h/cpp       # Player entity with sprite animation
│   ├── map.h/cpp          # TMX map loader and renderer
│   ├── sprite.h/cpp       # Frame-based animation controller
│   ├── sprite_texture.h   # Sprite-sheet texture (header-only)
│   ├── texture.h/cpp      # SDL_Texture wrapper
│   ├── camera.h           # 2D camera with translate + scale
│   ├── point.h            # 2D vector class
│   ├── timer.h/cpp        # Delta time from SDL_GetTicks
│   ├── logger.h           # Console logger (header-only)
│   └── exceptions.h       # Simple exception class
├── assets/
│   ├── res/               # Sprite sheets
│   └── maps/              # TMX map files and tilesets
└── .github/workflows/ci.yml
```

## Architecture

### Game Loop (`Game::execute()` in `src/game.cpp`)

Standard SDL2 game loop: `handleEvents()` → `update(deltaTime)` → `render()`. Vsync-enabled, no explicit frame cap.

Input is state-based: `handleEvents()` tracks held keys in `_heldKeys` set. Each frame, `updatePlayerInput()` computes player direction from WASD, `updateCameraInput()` moves camera from arrow keys.

### Entity System

`Object` (`src/object.h`) is the base class for all game entities. It uses a **static registry pattern**:
- All Objects auto-register into `static std::vector<Object*> objects` on construction
- `updateObjects(float deltaTime)` and `renderObjects(const Camera&)` operate on all registered objects
- `setDirection(Point)` sets movement direction; `(0,0)` stops movement
- Diagonal movement is supported (direction vector is normalized before applying speed)

Subclasses: `Player`, `Map`

### Rendering

SDL2 hardware-accelerated 2D renderer (`SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC`). All rendering goes through `SDL_RenderCopy`/`SDL_RenderCopyEx`.

`Camera` (`src/camera.h`, header-only) applies translation and scale transforms to all draw calls.

### Map System (`src/map.h`, `src/map.cpp`)

Loads TMX files via `libtmx` (C API). Supports both isometric and orthogonal orientations. Isometric projection: `x = (tileW/2)*(col-row)`, `y = (tileH/2)*(col+row)`. Maps and tilesets live in `assets/maps/`.

### Sprite Animation (`src/sprite.h`, `src/sprite_texture.h`)

`SpriteTexture` extends `Texture` with sprite-sheet awareness (grid-based, 4x4 layout for the player at 90x90 per tile). `Sprite` is the animation controller with time-based frame cycling (0.2s/frame). `Player` has four `Sprite` instances for cardinal directions; diagonal movement uses the dominant axis sprite.

### Class Hierarchy

```
Object (abstract base, static registry)
  ├── Map
  └── Player

Texture (SDL_Texture wrapper)
  └── SpriteTexture (sprite-sheet, static registry)

Sprite (animation controller, references SpriteTexture)
Camera (translate + scale, header-only)
Point  (2D vector, header-only)
Timer  (delta time from SDL_GetTicks)
Logger (static console output, header-only)
```

## Input

- WASD: move player (supports diagonal)
- Arrow keys: move camera
- `[` / `]`: zoom in/out (range: 0.125x to 3x)
