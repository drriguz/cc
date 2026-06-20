cmake_minimum_required(VERSION 3.10)
project(cc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set asset directory as compile definition
add_definitions(-DASSET_DIR="${CMAKE_SOURCE_DIR}/assets")

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Find tmxparser
find_package(tmx REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/object.cpp
    src/player.cpp
    src/map.cpp
    src/sprite.cpp
    src/texture.cpp
    src/timer.cpp
)

# Header files (for IDE integration)
set(HEADERS
    src/game.h
    src/object.h
    src/player.h
    src/map.h
    src/sprite.h
    src/sprite_texture.h
    src/texture.h
    src/camera.h
    src/point.h
    src/timer.h
    src/logger.h
    src/exceptions.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    tmx
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
)
