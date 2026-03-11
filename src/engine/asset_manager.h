#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>

class AssetManager {
private:
    static std::unordered_map<std::string, Texture2D> textures;

public:
    static void Load();
    static Texture2D GetTexture(std::string name);
    static void Unload();
};