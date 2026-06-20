# cc

A 2D/isometric tile-based game engine written in C++11 using SDL2.

## Features

- SDL2 hardware-accelerated rendering
- TMX map loading (Tiled Map Editor format)
- Isometric and orthogonal map support
- Animated sprite system
- Camera with pan and zoom
- State-based input handling

## Controls

| Input | Action |
|---|---|
| W/A/S/D | Move player (including diagonals) |
| Arrow keys | Pan camera |
| `[` / `]` | Zoom in/out |

## Build

### Prerequisites

- C++11 compiler
- CMake 3.10+

**macOS:**
```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer tmx pkg-config
```

**Ubuntu:**
```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev pkg-config cmake libxml2-dev zlib1g-dev
# Build tmx from source
git clone https://github.com/baylej/tmx.git /tmp/tmx
cd /tmp/tmx && mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make && sudo make install
```

### Compile

```bash
cmake -B build
cmake --build build
```

### Run

```bash
./build/cc
```

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

## License

Apache 2.0
