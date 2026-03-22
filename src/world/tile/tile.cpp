#include "tile.h"

const std::string Tile::TILE_NAME = "tiles";

bool Tile::isPassable() const {
    if(door && !door->isPassable())
        return false;

    return terrain.isPassable();
}

bool Tile::isBlockVision() const {
    if(door && door->isBlockVision())
        return true;

    return terrain.isBlockVision();
}

bool Tile::isDanger() const {
    if(door) return false;
    if(trap) return true;
    return terrain.isDanger();
}

void Tile::onEnter(Entity* entity, World& world) {
    if(trap && trap->isArmed()) {
        trap->trigger(entity, world);
        return;
    }

    terrain.onEnter(entity, world);
}

void Tile::update() {
    if(door) {
        if(door->isHidden()) {
            tilePos = tileImagePosition(ID_WALL);
            return;
        }

        int id = doorTileId(door->getState());
        tilePos = tileImagePosition(id);
        return;
    }

    if(trap) {
        if(!trap->isRevealed()) {
            tilePos = tileImagePosition(ID_FLOOR);
            return;
        }

        if(trap->isArmed()) {
            int id = trapTileId(trap->getTrapType());
            tilePos = tileImagePosition(id);
        } else {
            tilePos = tileImagePosition(ID_TRAP_DISABLE);
        }
        return;
    }

    if(terrain.getType() == TerrainType::CRUSHED_GRASS) {
        tilePos = tileImagePosition(ID_CRUSHED_GRASS);
    }
}

void Tile::render(int x, int y) {
    Texture2D tileset = AssetManager::GetTexture(TILE_NAME);

    Rectangle source = {
        tilePos.x, tilePos.y,
        TILE_SIZE, TILE_SIZE
    };

    Vector2 position = {
        (float)x * TILE_SIZE,
        (float)y * TILE_SIZE
    };

    DrawTextureRec(tileset, source, position, WHITE);
}
