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
    static constexpr std::string_view IDLE_SCENE = "idle_scene";
    static constexpr std::string_view TILE = "tiles";
    static constexpr std::string_view STATUS_PANE = "status_pane";
    static constexpr std::string_view HP_BAR = "hp_bar";

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
    
    static constexpr std::string_view WEAPON_NONE       = "weapon_none";
    static constexpr std::string_view ARMOR_NONE        = "armor_none";
    static constexpr std::string_view RING_NONE         = "ring_none";
    static constexpr std::string_view SHORT_SWORD       = "short_sword";
    static constexpr std::string_view SWORD             = "sword";
    static constexpr std::string_view FABRIC_ARMOR      = "fabric_armor";
    static constexpr std::string_view LEATHER_ARMOR     = "leather_armor";
    static constexpr std::string_view CHAIN_ARMOR       = "chain_armor";
    static constexpr std::string_view RING_VISION       = "ring_vision";
    static constexpr std::string_view RING_DEFENSE      = "ring_defense";
    static constexpr std::string_view BREAD             = "bread";
    static constexpr std::string_view POTION_STRENGTH   = "potion_strength";
    static constexpr std::string_view POTION_HEALING    = "potion_healing";
    static constexpr std::string_view SCROLL_TELEPORT   = "scroll_teleport";
    static constexpr std::string_view SCROLL_ATTACK     = "scroll_attack";
    static constexpr std::string_view GOLD_ITEM         = "gold";
    static constexpr std::string_view KEY               = "key";
};
