#include "asset_manager.h"
#include <sstream>

std::unordered_map<std::string, Texture2D> AssetManager::textures;
std::unordered_map<std::string, std::vector<std::vector<int>>> AssetManager::dataMap;

static std::vector<std::vector<int>> LoadCSV(const char* fileName) {
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


void AssetManager::Load() {
    textures["start_scene"] = LoadTexture("assets/start_scene.png");
    textures["hero_select_scene"] = LoadTexture("assets/hero_select_scene.png");
    textures["start_button"] = LoadTexture("assets/start_button.png");

    textures["tiles"] = LoadTexture("assets/tiles.png");

    dataMap["level1_Terrain"] = LoadCSV("assets/level/level1_Terrain.csv");
    dataMap["level1_Door"] = LoadCSV("assets/level/level1_Door.csv");
    dataMap["level1_Trap"] = LoadCSV("assets/level/level1_Trap.csv");
}

Texture2D AssetManager::GetTexture(std::string name) {
    return textures[name];
}

std::vector<std::vector<int>>& AssetManager::GetMap(std::string name) {
    return dataMap[name];
}

void AssetManager::Unload() {
    for(auto &t : textures) {
        UnloadTexture(t.second);
    }
}