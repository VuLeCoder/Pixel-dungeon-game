#pragma once
#include "raylib.h"
#include "./effect/animation.h"

#include <unordered_map>
#include <vector>
#include <string>

class AssetManager {
private:
    static std::unordered_map<std::string, Texture2D> textures;
    static std::unordered_map<std::string, std::vector<std::vector<int>>> dataMap;
    static std::unordered_map<std::string, Animation> dataAnim;

    static std::vector<std::vector<int>> LoadCSV_Map(const char* fileName);
    static Animation LoadAnimation(const std::string& fileName);

    static void LoadAllTexture();
    static void LoadAllLevelMap();
    static void LoadAllAnimation();

public:
    static void Load();
    static void Unload();

    static Texture2D& GetTexture(std::string_view name);
    static std::vector<std::vector<int>>& GetMap(std::string_view name);
    static Animation& GetAnimation(std::string_view name);
};