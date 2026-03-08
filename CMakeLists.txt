cmake_minimum_required(VERSION 3.15)
project(SHATTERED_PIXEL_DUNGEON)

set(CMAKE_CXX_STANDARD 17)

# add raylib
add_subdirectory(external/raylib)

# game source
add_executable(SHATTERED_PIXEL_DUNGEON src/main.cpp)

# link raylib
target_link_libraries(SHATTERED_PIXEL_DUNGEON raylib)
