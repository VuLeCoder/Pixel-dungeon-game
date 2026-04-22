cmake_minimum_required(VERSION 3.15)
project(PIXEL_DUNGEON)

set(CMAKE_CXX_STANDARD 17)

# add raylib
add_subdirectory(external/raylib)

# asset
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# game source
add_executable(PIXEL_DUNGEON
    src/main.cpp
    src/utils/helper.cpp

    src/engine/scene_manager.cpp
    src/engine/asset_manager.cpp
    src/engine/effect/frame_image.cpp
    src/engine/effect/animation.cpp

    src/scenes/start_scene.cpp
    src/scenes/hero_select_scene.cpp
    src/scenes/game_scene.cpp
    src/scenes/idle_scene.cpp

    src/ui/ui.cpp
    src/ui/player_panel.cpp
    src/ui/inventory_panel.cpp

    src/world/world.cpp
    src/world/level/level.cpp
    src/world/tile/tile.cpp
    src/world/tile/tile_index.cpp
    src/world/tile/terrain/terrain.cpp
    src/world/tile/door/door.cpp
    src/world/tile/trap/trap.cpp

    src/world/entity/creature/creature.cpp
    src/world/entity/creature/player.cpp
    src/world/entity/creature/monster.cpp
    src/world/entity/item/item.cpp

    src/world/camera/camera.cpp

    src/world/system/turn_system/turn_system.cpp
    src/world/system/FOV/fov_system.cpp
    src/world/system/AI/path_finder.cpp
    src/world/system/AI/monster_ai.cpp
    src/world/system/inventory/inventory_system.cpp
)
# link raylib
target_link_libraries(PIXEL_DUNGEON raylib)
