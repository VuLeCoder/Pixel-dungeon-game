#include "asset_manager.h"

#include <sstream>
#include <fstream>
#include <limits>

// private:
std::unordered_map<std::string, Texture2D> AssetManager::textures;
std::unordered_map<std::string, std::vector<std::vector<int>>> AssetManager::dataMap;
std::unordered_map<std::string, Animation> AssetManager::dataAnim;


void AssetManager::LoadAllTexture() {
    struct TextureEntry {
        std::string_view key;
        std::string_view path;
    };

    TextureEntry entries[] = {
        {START_SCENE, "assets/scenes/start_scene.png"},
        {HERO_SCENE, "assets/scenes/hero_select_scene.png"},
        {START_BUTTON, "assets/scenes/start_button.png"},
        {TILE, "assets/level/tiles.png"}
    };

    for (auto& e : entries) {
        textures[std::string(e.key)] = LoadTexture(e.path.data());
    }
}


std::vector<std::vector<int>> AssetManager::LoadCSV_Map(const char* fileName) {
    std::vector<std::vector<int>> result;

    char* text = LoadFileText(fileName);
    std::stringstream ss(text);
    std::string line;

    while (std::getline(ss, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<int> row;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(std::stoi(cell));
        }

        result.push_back(row);
    }

    UnloadFileText(text);
    return result;
}

void AssetManager::LoadAllLevelMap() {
    struct MapEntry {
        std::string_view key;
        std::string_view path;
    };

    MapEntry entries[] = {
        {"level1_Terrain", "assets/level/level1_Terrain.csv"},
        {"level1_Door",    "assets/level/level1_Door.csv"},
        {"level1_Trap",    "assets/level/level1_Trap.csv"}
    };

    for (auto& e : entries) {
        dataMap[std::string(e.key)] = LoadCSV_Map(e.path.data());
    }
}

Animation AssetManager::LoadAnimation(const std::string& fileName) {
    Animation anim;
    std::ifstream file(fileName);

    int count; file >> count;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string texturePath;
    std::getline(file, texturePath);

    textures[texturePath] = LoadTexture(texturePath.c_str());
    Texture2D tex = textures[texturePath];

    std::string line;
    float x, y, w, h, dt;
    for(int i=0; i<count; ++i) {
        line = "";
        while(line.empty() && std::getline(file, line));

        file >> x >> y >> w >> h;
        FrameImage f(tex, {x, y, w, h});
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        file >> dt;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        anim.add(f, dt);
    }

    return anim;
}

void AssetManager::LoadAllAnimation() {
     struct AnimEntry {
        std::string_view entity;
        std::string_view state;
        std::string_view file;
    };

    AnimEntry entries[] = {
        {WARRIOR, IDLE,         "assets/entity/creature/hero/warrior/idle_animation.txt"},
        {WARRIOR, WALK,         "assets/entity/creature/hero/warrior/walk_animation.txt"},
        {WARRIOR, ATK,          "assets/entity/creature/hero/warrior/attack_animation.txt"},
        {WARRIOR, USE,          "assets/entity/creature/hero/warrior/use_animation.txt"},
        {WARRIOR, USE_SCROLL,   "assets/entity/creature/hero/warrior/use_scroll_animation.txt"},
        {WARRIOR, DEATH,        "assets/entity/creature/hero/death_animation.txt"}
    };

    for (auto& e : entries) {
        std::string key = std::string(e.entity) + '_' + std::string(e.state);
        dataAnim[key] = LoadAnimation(e.file.data());
    }
}

//public:
void AssetManager::Load() {
    LoadAllTexture();
    LoadAllLevelMap();
    LoadAllAnimation();
}

Texture2D& AssetManager::GetTexture(std::string_view name) {
    return textures[std::string(name)];
}

std::vector<std::vector<int>>& AssetManager::GetMap(std::string_view name) {
    return dataMap[std::string(name)];
}

Animation& AssetManager::GetAnimation(std::string_view name) {
    return dataAnim[std::string(name)];
}

void AssetManager::Unload() {
    for(auto &t : textures) {
        UnloadTexture(t.second);
    }
}
