#include "asset_manager.h"

std::unordered_map<std::string, Texture2D> AssetManager::textures;

void AssetManager::Load() {
    textures["start_scene"] = LoadTexture("assets/start_scene.png");
    textures["hero_select_scene"] = LoadTexture("assets/hero_select_scene.png");
    textures["start_button"] = LoadTexture("assets/start_button.png");
}

Texture2D AssetManager::GetTexture(std::string name) {
    return textures[name];
}

void AssetManager::Unload() {
    for(auto &t : textures) {
        UnloadTexture(t.second);
    }
}