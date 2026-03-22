cmake_minimum_required(VERSION 3.15)
project(SHATTERED_PIXEL_DUNGEON)

set(CMAKE_CXX_STANDARD 17)

# add raylib
add_subdirectory(external/raylib)

# asset
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# game source
add_executable(SHATTERED_PIXEL_DUNGEON
    src/main.cpp

    src/engine/scene_manager.cpp
    src/engine/asset_manager.cpp

    src/scenes/start_scene.cpp
    src/scenes/hero_select_scene.cpp
    src/scenes/game_scene.cpp

    src/world/world.cpp
    src/world/level/level.cpp
    src/world/tile/tile.cpp
    src/world/tile/tile_index.cpp
    src/world/tile/terrain/terrain.cpp
    src/world/tile/door/door.cpp
)
# link raylib
target_link_libraries(SHATTERED_PIXEL_DUNGEON raylib)
