#pragma once
#include "raylib.h"
#include <unordered_map>
#include <vector>
#include <string>

class AssetManager {
private:
    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<std::string, std::vector<std::vector<int>>> dataMap;

public:
    static void Load();
    static void Unload();

    static Texture2D GetTexture(std::string name);
    static std::vector<std::vector<int>>& GetMap(std::string name);
};