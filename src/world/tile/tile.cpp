#include "tile.h"
#include "../../engine/asset_manager.h"

// Private:
const std::string Tile::TILE_NAME = "tiles";

Vector2 Tile::tileImagePosition(int tileId) {
    if(tileId == -1) {
        return {0, 0}; //FLOOR
    }

    int x = tileId % 8;
    int y = tileId / 8;
    return {
        static_cast<float>(x * TILE_SIZE), 
        static_cast<float>(y * TILE_SIZE)
    };
}

TerrainType Tile::determineTileType(int tileId) {
    if(tileId < 0 || tileId >= std::size(tileTypeMap)) {
        return TerrainType::CHASM;
    }
    return tileTypeMap[tileId];
}

Trap* Tile::createTrap(int tileId) {
    switch(tileId) {
        case ID_TRAP_ALARM:     return new AlarmTrap();
        case ID_TRAP_EXPLODE:   return new ExplosionTrap();
        case ID_TRAP_SPAWN:     return new SpawnTrap();
        case ID_TRAP_SPIKE:     return new SpikeTrap();
        case ID_TRAP_TELEPORT:  return new TeleportTrap();
        default: return nullptr;
    }
}


// Public:
Tile::Tile() {
    tilePos = tileImagePosition(ID_FLOOR);
    terrain.setTerrainType(TerrainType::FLOOR);
}

bool Tile::isStairUp() {
    return terrain.getType() == TerrainType::STAIR_UP;
}

bool Tile::isStairDown() {
    return terrain.getType() == TerrainType::STAIR_DOWN;
}

void Tile::setTerrainType(int tileId) {
    tilePos = tileImagePosition(tileId);
    terrain.setTerrainType(determineTileType(tileId));
}

void Tile::setDoorTile(bool isLocked, bool isHidden) {
    door = new Door(isLocked, isHidden);
}

void Tile::setTrapTile(int trapId, bool isHidden) {
    trap = createTrap(trapId);
    if(!trap) return;

    if(!isHidden) {
        trap->reveal();
    }
}

void Tile::discoverTile() {
    discovered = true;
}

bool Tile::isDiscovered() const {
    return discovered;
}

bool Tile::isPassable() const {
    if(door) return door->isPassable();
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

void Tile::onEnter(Entity* entity, World* world) {
    if(door && !door->isHidden()) {
        door->open();
    }

    if(door && door->isLocked()) {
        if(!entity) return;
        if(!entity->isPlayer()) return;
        
        Player* p = static_cast<Player*>(entity);
        if(p->hasKey()) door->unlock();
    }

    if(trap && trap->isArmed()) {
        trap->trigger(entity, world);
        return;
    }

    terrain.onEnter(entity, world);
}

void Tile::onLeft() {
    if(door) {
        door->close();
    }
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
