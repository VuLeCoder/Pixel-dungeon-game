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

public:
    static constexpr std::string_view START_SCENE = "start_scene";
    static constexpr std::string_view HERO_SCENE = "hero_select_scene";
    static constexpr std::string_view START_BUTTON = "start_button";
    static constexpr std::string_view TILE = "tiles";

    static constexpr std::string_view LEVEL = "level";
    static constexpr std::string_view TERRAIN = "Terrain";
    static constexpr std::string_view DOOR = "Door";
    static constexpr std::string_view TRAP = "Trap";

    static constexpr std::string_view IDLE = "idle";
    static constexpr std::string_view WALK = "walk";
    static constexpr std::string_view ATK = "attack";
    static constexpr std::string_view DEATH = "death";
    static constexpr std::string_view USE = "use";
    static constexpr std::string_view USE_SCROLL = "use_scroll";

    static constexpr std::string_view WARRIOR = "warrior";
    static constexpr std::string_view MAGE = "mage";

    static constexpr std::string_view RAT = "rat";
    static constexpr std::string_view GNOLL = "gnoll";
};