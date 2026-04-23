#include "level.h"
#include "tile_rule.h"
#include "../../engine/asset_manager.h"
#include "../entity/creature/monster.h"
#include "../entity/item/item.h"
#include "../entity/item/item_info.h"
#include "./../../utils/helper.h"

#include <iostream>
#include <string>
#include <algorithm>

//helper
void drawBlack(int x, int y) {
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
}

void drawDark(int x, int y) {
    Color dark = {0, 0, 0, 180};
    DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, dark);
}

//private:
MapData Level::loadMapData(int depth) {
    std::string base = "level" + std::to_string(depth);

    return {
        AssetManager::GetMap(base + '_' + std::string(AssetManager::TERRAIN)),
        AssetManager::GetMap(base + '_' + std::string(AssetManager::DOOR)),
        AssetManager::GetMap(base + '_' + std::string(AssetManager::TRAP))
    };
}

Tile Level::buildTile(int x, int y, const MapData& data) {
    Tile tile;
    int terrain = data.terrain[y][x];

    int trap = data.trap[y][x];
    if(trap != NONE) {
        tile.setTrapTile(terrain, trap == TRAP_HIDDEN);
        return tile;
    }

    int door = data.door[y][x];
    if(door != NONE) {
        tile.setDoorTile(
            door == DOOR_LOCKED,
            door == DOOR_HIDDEN
        );
        return tile;
    }

    tile.setTerrainType(terrain);
    return tile;
}

//public:
Level::Level(World* world) : world(world) {}

void Level::generateMap(int depth) {
    MapData data = loadMapData(depth);

    tiles = std::vector<std::vector<Tile>>(MAP_SIZE, std::vector<Tile>(MAP_SIZE));
    for(int y=0; y<MAP_SIZE; ++y) {
        for(int x=0; x<MAP_SIZE; ++x) {
            tiles[y][x] = buildTile(x, y, data);

            if(tiles[y][x].isStairUp()) {
                stairUpPos = {(float)x * TILE_SIZE, (float)y * TILE_SIZE};
            }

            if(tiles[y][x].isStairDown()) {
                stairDownPos = {(float)x * TILE_SIZE, (float)y * TILE_SIZE};
            }
        }
    }
}

void Level::update(float dt) {
    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {
            tiles[y][x].update();
        }
    }

    for(Item* i : items) {
        i->update(dt);
    }
}

void Level::render() {
    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {
            tiles[y][x].render(x, y);
        }
    }

    for(Item* i : items) {
        i->render();
    }

    for(Monster* m : enemies) {
        m->render();
    }

    for(int x=0; x<MAP_SIZE; ++x) {
        for(int y=0; y<MAP_SIZE; ++y) {
            if(!tiles[y][x].isDiscovered()) {
                drawBlack(x, y);
            } else if(!getWorld()->getPlayer()->visible(x, y)) {
                tiles[y][x].render(x, y);
                drawDark(x, y);
            }
        }
    }
}

bool Level::isBlockVision(int x, int y) const {
    return tiles[y][x].isBlockVision();
}

void Level::openDoor(int x, int y) {
    tiles[y][x].openDoor();
}

bool Level::isDoor(int x, int y) const {
    return tiles[y][x].isDoor();
}

bool Level::isPassable(int x, int y) const {
    return tiles[y][x].isPassable();
}

bool Level::isDanger(int x, int y) const {
    return tiles[y][x].isDanger();
}

void Level::discover(int x, int y) {
    tiles[y][x].discoverTile();
}

void Level::onStep(Entity* e, int x, int y) {
    tiles[y][x].onEnter(e, getWorld());
}

void Level::onLeft(int x, int y) {
    tiles[y][x].onLeft();
}

Vector2 Level::getRandomFreeTile() {
    std::vector<Vector2> freeTiles;
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            if (!isPassable(x, y)) continue;
            if (isDanger(x, y)) continue;
            if (getEntityAtTile(x, y) != nullptr) continue;

            freeTiles.push_back({(float)x, (float)y});
        }
    }

    if (freeTiles.empty()) {
        return {-1, -1};
    }

    int index = GetRandomValue(0, freeTiles.size() - 1);
    freeTiles[index].x *= TILE_SIZE;
    freeTiles[index].y *= TILE_SIZE;
    return {freeTiles[index].x, freeTiles[index].y};
}

Entity* Level::getEntityAtTile(int x, int y) {
    auto check = [&](Entity* e) -> Entity* {
        if(!e) return nullptr;

        Vector2 p = e->getPosition();
        int ex = (int)p.x / TILE_SIZE;
        int ey = (int)p.y / TILE_SIZE;
        return (ex == x && ey == y) ? e : nullptr;
    };

    Player* p = getWorld()->getPlayer();
    if(p)
        if(auto r = check(p))
            return r;

    for(Entity* e : enemies)
        if(auto r = check(e)) return r;
    
    return nullptr;
}

Item* Level::getItemAtTile(int x, int y) {
    auto check = [&](Item* e) -> Item* {
        Vector2 p = e->getPosition();
        int ex = (int)p.x / TILE_SIZE;
        int ey = (int)p.y / TILE_SIZE;
        return (ex == x && ey == y) ? e : nullptr;
    };

    for(Item* i : items)
        if(auto r = check(i)) return r;

    return nullptr;
}

void Level::addItemAtPos(Item* item, Vector2 pos) {
    item->setPos(pos.x, pos.y);
    items.push_back(item);
}

void Level::addMonsterAtPos(Monster* monster, Vector2 pos) {

}

void Level::spawnMonsterNear(Vector2 pos) {
    // Vector2 pos1 = getRandomFreeTile();
    // if (pos1.x < 0 || pos1.y < 0) {
    //     std::cout << "No free tile to spawn monster!\n";
    //     return;
    // }

    // Monster* m = new Monster(getStairUpPos().x, getStairUpPos().y + 16, getWorld(), Direction::LEFT, GNOLL);
    // enemies.push_back(m);

    Item* item = new Item(getStairUpPos().x, getStairUpPos().y + 16, getWorld(), fabricArmor);
    items.push_back(item);
}

void Level::removeDeadEntities() {
    auto it = std::remove_if(enemies.begin(), enemies.end(),
        [](Monster* e) {
            if (!e->isAlive()) {
                delete e;
                return true;
            }
            return false;
        });

    enemies.erase(it, enemies.end());
}

void Level::removeItemLevel(Item* item) {
    for(size_t i = 0; i < items.size(); ++i) {
        if (items[i] == item) {
            std::swap(items[i], items.back());
            items.pop_back();
            return;
        }
    }
}

void Level::wakeUpAllMonsters(Vector2 pos, int alarmRange) {
    for(Monster* m : enemies) {
        m->alarm(pos, alarmRange);
    }
}

void Level::spawnRandomMonsters(int count) {
    int maxAttempts = 100; 

    // Vòng lặp tìm 1 vị trí ĐẸP
    for (int i = 0; i < count; ++i) {
        Vector2 pos = {-1, -1};
        bool isValid = false;
        int attempts = 0;

        while (!isValid && attempts < maxAttempts) {
            pos = getRandomFreeTile();
            attempts++;

            if (pos.x < 0 || pos.y < 0) break; 

            // Quy tắc 1: Chống "nhót ngay cửa" - Cấm spawn cách cầu thang (người chơi) dưới 5 ô
            if (distance(pos, stairUpPos) < 5) {
                continue; // Vị trí này nguy hiểm cho người chơi, bỏ qua tìm ô khác!
            }

            // Quy tắc 2: Chống "Party 1 phòng" - Cấm spawn cách quái khác dưới 3 ô
            bool tooCloseToOthers = false;
            for (Monster* m : enemies) {
                if (distance(pos, m->getPosition()) < 3) {
                    tooCloseToOthers = true;
                    break;
                }
            }

            if (tooCloseToOthers) {
                continue; // Đụng hàng quái khác, bỏ qua tìm ô khác!
            }

            // Nếu qua được 2 ải trên thì vị trí này là hoàn hảo
            isValid = true;
        }

        // Chốt đơn vị trí
        if (isValid) {
            // int num = GetRandomValue(1, 100);
            MonsterInfo info = GNOLL;
            // if(num <= 60) info = RAT;
            // else if(num <= 90) info = GNOLL;
            // else info = CRAB;

            Monster* m = new Monster(pos.x, pos.y, getWorld(), Direction::LEFT, info);
            enemies.push_back(m);
        } else {
            std::cout << "Map da kin hoac khong the tim diem an toan de spawn them quai!" << std::endl;
            break;
        }
    }
}

void Level::spawnRandomItems(int count) {
    // ĐÃ XÓA HOÀN TOÀN decltype. Dùng trực tiếp ItemType!
    std::vector<ItemType> weapon_lootTable = { sword, shortSword };
    std::vector<ItemType> armor_lootTable = { chainArmor, leatherArmor, fabricArmor };
    std::vector<ItemType> ring_lootTable = { ringOfDefense, ringOfVision };
    
    // 1. Chuẩn bị "Giỏ đồ"
    std::vector<ItemType> itemsToSpawn;

    // QUAN TRỌNG: Đưa Chìa khóa vào đầu tiên (index = 0) để dễ áp dụng luật riêng!
    itemsToSpawn.push_back(key);

    itemsToSpawn.push_back(gold); 
    itemsToSpawn.push_back(weapon_lootTable[GetRandomValue(0, 1)]);
    itemsToSpawn.push_back(armor_lootTable[GetRandomValue(0, 2)]);
    itemsToSpawn.push_back(ring_lootTable[GetRandomValue(0, 1)]);
    itemsToSpawn.push_back(bread); 
    itemsToSpawn.push_back((GetRandomValue(0, 1) == 0) ? scrollOfAttack : scrollOfTeleport); 
    itemsToSpawn.push_back((GetRandomValue(0, 1) == 0) ? healingPotion : potionOfStrength);  

    // 2. Xử lý "tiền boa" (Nếu tham số count lớn hơn 😎
    int tableSize = (int)itemsToSpawn.size();
    int totalSpawns = (count > tableSize) ? count : tableSize;
    
    for (int i = tableSize; i < totalSpawns; ++i) {
        itemsToSpawn.push_back((GetRandomValue(0, 1) == 0) ? bread : gold);
    }

    // Tăng số lần thử lên 200 vì map giờ rải đồ khó tính hơn
    int maxAttempts = 200; 
    
    // 3. Đem toàn bộ giỏ đồ đi rải ngẫu nhiên
    for (size_t i = 0; i < itemsToSpawn.size(); ++i) {
        Vector2 pos = {-1, -1};
        bool isValid = false;
        int attempts = 0;

        // Xác định xem món đồ hiện tại có phải là Chìa Khóa không
        bool isKey = (i == 0); 

        while (!isValid && attempts < maxAttempts) {
            pos = getRandomFreeTile();
            attempts++;

            if (pos.x < 0 || pos.y < 0) break; // Map hết ô trống

            // RULE 1: Không được rớt ở phòng người chơi xuất hiện (Cách stairUpPos ít nhất 6 ô)
            int distToPlayer = distance(pos, stairUpPos);
            if (distToPlayer < 6) continue;

            // RULE 2: Chìa khóa KHÔNG ĐƯỢC sinh ra ở cuối map để tránh lọt vào phòng khóa
            if (isKey && distToPlayer > 15) continue; 

            // RULE 3: Đảm bảo mỗi phòng 1 món (Giãn cách các món đồ ít nhất 8 ô)
            bool tooClose = false;
            for (Item* existingItem : items) {
                if (distance(pos, existingItem->getPosition()) < 8) {
                    tooClose = true;
                    break;
                }
            }
            if (tooClose) continue;

            // Vượt qua 3 ải kiểm duyệt thì chốt vị trí này!
            isValid = true; 
        }
        
        if (isValid) {
            Item* item = new Item(pos.x, pos.y, getWorld(), itemsToSpawn[i]);
            items.push_back(item);
        } else {
            std::cout << "Map chat qua, khong the tim goc dep de spawn item thu " << i << std::endl;
        }
    }
}
